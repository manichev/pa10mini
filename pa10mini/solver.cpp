#include <stdexcept>
#include <iostream>
#include <fstream>
#include <locale>
#include <memory>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFile>

#include "solver.h"

//global variable;
Solver* solver;

Solver::Solver(QObject *parent)
    : QObject(parent)
{
//default values of solver parameters
    t0 = 0.0;
    tk = 240.0;
    hmn = 1e-16;
    hmx = 1e16;
    eps = 1e-3;
    nm = 3;
    rj2_before = false;
    writeFile = true;
    maxMemSize = 1024*1024*2;

    connect(&fcttaskCompiler_, &FcttaskCompiler::started, this, [this]() {
        emit statusMessage(tr("Compiling fcttask with MinGW g++..."));
    });
    connect(&fcttaskCompiler_, &FcttaskCompiler::finished, this,
            [this](bool success, const QString &report) {
                if (!success) {
                    finishSolve(false, report);
                    return;
                }
                continueSolve();
            });
}

void Solver::setSystem(DAESystem* system_)
{
    system = system_;
    if (system == nullptr)
        return;
    system->updateAllIds();
    names.clear();
    trace.clear();
    dims.clear();
    QVector<QString> dnames;
    for (auto &variable : system->variables) {
        names.append(QString::fromStdString(variable.name));
        if (variable.isDerivative)
            dnames.append(QString::fromStdString(variable.name) + "'");
    }
    names+=dnames;
}

void Solver::outtask(double z[],double px[],int n,int m,double t,double t0,double tk,double h,double *tkv,int ncon,int ip[])
{
    Q_UNUSED(h)
    Q_UNUSED(tkv)
    Q_UNUSED(ncon)
    Q_UNUSED(ip)
    Q_UNUSED(m)

    if (writeFile && !outFileName.isEmpty() && outTextStream) {
        // Записать заголовок на первом шаге
        if (fabs(t - t0) < h / 4) {
            *outTextStream << "t";

            for (int i = 0; i < trace.size(); ++i) {
                if (trace[i] > n)
                    *outTextStream << "," << QString::fromStdString(system->getVariableDerivativeName(trace[i] - n));
                else
                    *outTextStream << "," << QString::fromStdString(system->getVariableName(trace[i]));
            }

            *outTextStream << "\n";
        }

        // Запись данных
        QString line;
        line.append(" ");
        line.append(QString::number(t, 'e'));
        for (int i = 0; i < trace.size(); ++i) {
            line.append(", ");
            if (trace[i] > n)
                line.append(QString::number(px[trace[i] - n], 'e'));
            else
                line.append(QString::number(z[trace[i]], 'e'));
        }
        line.append("\n");
        *outTextStream << line;
    }
    if (t >= tout) {
        paxData[0].append(t);
        for (int i = 0; i < trace.size(); ++i) {
            if (trace[i] > n)
                paxData[i + 1] += px[trace[i] - n];
            else
                paxData[i + 1] += z[trace[i]];
        }
        tout += (tk - t0) / maxPoints;
    }

    if (t >= tp) {
        tp += (tk - t0) / 100;
        emit progressChanged((int)((t - t0) / (tk - t0) * 100));
    }
}

void global_outtask(double z[],double px[],int n,int m,double t,double t0,double tk,double h,double *tkv,int ncon,int ip[])
{
    solver->outtask(z, px, n, m, t, t0, tk, h, tkv, ncon, ip);
}

int progressChanged(int value)
{
    return value;
}

void Solver::create_fcttask(const QString &pathToCompiler)
{
    const QString taskDirectory = QDir(workingDirectory_).absoluteFilePath("manzhuk/fcttask");
    const QFileInfo taskDirectoryInfo(taskDirectory);
    if (!taskDirectoryInfo.exists() || !taskDirectoryInfo.isDir())
        throw std::runtime_error(tr("fcttask directory does not exist: %1").arg(taskDirectory).toUtf8().constData());

    std::ostringstream generatedSource;
    generatedSource.imbue(std::locale::classic());
    generatedSource << "#include \"fcttask.h\"\n";
    generatedSource << "#include <cmath>\n\n";
    generatedSource << "void fcttask(double z[], double px[], double f[], double rj1[], double rj2[], int n, int m, double t, double h, int ncon, int *nbad, int ip[])\n";
    generatedSource << "{\n";

    int i = 1;
    for (auto eqIt = system->equals.begin(); eqIt != system->equals.end(); ++eqIt, ++i) {
        generatedSource << "\tf[" << i << "] = ";
        (*eqIt)->simplify();
        (*eqIt)->print_c_ostream(generatedSource);
        generatedSource << ";\n";

        for (int j = 1; j <= m; ++j) {
            std::unique_ptr<Expression> derivative((*eqIt)->derivative(-j));
            if (!derivative->isConst(0.0)) {
                generatedSource << "\trj1[" << i << "*n+" << j << "] = ";
                derivative->print_c_ostream(generatedSource);
                generatedSource << ";\n";
            }
        }

        if (rj2_before) {
            for (int j = 1; j <= n; ++j) {
                std::unique_ptr<Expression> derivative((*eqIt)->derivative(j));
                if (!derivative->isConst(0.0)) {
                    generatedSource << "\trj2[" << i << "*n+" << j << "] = ";
                    derivative->print_c_ostream(generatedSource);
                    generatedSource << ";\n";
                }
            }
        }
    }
    generatedSource << "}\n";

    const QString sourcePath = QDir(taskDirectory).absoluteFilePath("fcttask.cpp");
    QFile sourceFile(sourcePath);
    if (!sourceFile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::runtime_error(tr("Cannot write generated fcttask source %1: %2")
                                     .arg(sourcePath, sourceFile.errorString()).toUtf8().constData());

    const QByteArray sourceBytes = QByteArray::fromStdString(generatedSource.str());
    if (sourceFile.write(sourceBytes) != sourceBytes.size())
        throw std::runtime_error(tr("Cannot write generated fcttask source %1: %2")
                                     .arg(sourcePath, sourceFile.errorString()).toUtf8().constData());
    if (!sourceFile.flush())
        throw std::runtime_error(tr("Cannot finish writing generated fcttask source %1: %2")
                                     .arg(sourcePath, sourceFile.errorString()).toUtf8().constData());
    sourceFile.close();

#if defined(Q_OS_WIN)
    const QString outputPath = QDir(taskDirectory).absoluteFilePath("fcttask.dll");
#else
    const QString outputPath = QDir(taskDirectory).absoluteFilePath("fcttask.so");
#endif

    QString errorMessage;
    if (!fcttaskCompiler_.start(pathToCompiler, workingDirectory_, sourcePath,
                                outputPath, &errorMessage)) {
        throw std::runtime_error(errorMessage.toUtf8().constData());
    }
}

void Solver::solve(const QString &pathToCompiler)
{
    if (busy_)
        return;

    busy_ = true;
    workingDirectory_ = QDir::currentPath();
    if (outFileName.isEmpty())
        outFileName = QDir(workingDirectory_).absoluteFilePath("output/fcttask.csv");
    else if (QFileInfo(outFileName).isRelative())
        outFileName = QDir(workingDirectory_).absoluteFilePath(outFileName);

    try {
        if (system == nullptr)
            throw std::invalid_argument("DAE system is not set");

        n = system->countEquals();
        m = system->countDerivatives();
        const int variableCount = system->countVariables();
        if (variableCount != n) {
            throw std::invalid_argument(
                "Invalid DAE system: number of variables (" + std::to_string(variableCount)
                + ") must match number of equations (" + std::to_string(n) + ")");
        }

        emit statusMessage(tr("Preparing fcttask source..."));
        create_fcttask(pathToCompiler);
    } catch (const std::exception &error) {
        finishSolve(false, QString::fromUtf8(error.what()));
    } catch (...) {
        finishSolve(false, tr("Unexpected error while preparing fcttask."));
    }
}

void Solver::continueSolve()
{
    try {
        QString libraryPath = QDir(workingDirectory_).absoluteFilePath("manzhuk/fcttask/fcttask");
#if defined(Q_OS_WIN)
        libraryPath += QStringLiteral(".dll");
#else
        libraryPath += QStringLiteral(".so");
#endif
        fcttaskLibrary_.setFileName(libraryPath);
        if (!fcttaskLibrary_.load())
            throw std::runtime_error(tr("Cannot load fcttask library %1: %2")
                                         .arg(libraryPath, fcttaskLibrary_.errorString()).toUtf8().constData());

        using FcttaskFunction = void (*)(double*, double*, double*, double*, double*,
                                         int, int, double, double, int, int*, int*);
        FcttaskFunction fcttask = reinterpret_cast<FcttaskFunction>(fcttaskLibrary_.resolve("fcttask"));
        if (fcttask == nullptr)
            throw std::runtime_error(tr("Library %1 does not export fcttask: %2")
                                         .arg(libraryPath, fcttaskLibrary_.errorString()).toUtf8().constData());

        if (writeFile) {
            const QFileInfo outputInfo(outFileName);
            QDir outputDirectory = outputInfo.dir();
            if (!outputDirectory.exists() && !outputDirectory.mkpath(QStringLiteral(".")))
                throw std::runtime_error(tr("Cannot create output directory: %1")
                                             .arg(outputDirectory.absolutePath()).toUtf8().constData());

            outFile.reset(new QFile(outFileName));
            if (!outFile->open(QIODevice::WriteOnly | QIODevice::Text))
                throw std::runtime_error(tr("Cannot open output file %1: %2")
                                             .arg(outFileName, outFile->errorString()).toUtf8().constData());
            outTextStream.reset(new QTextStream(outFile.get()));
        }

        emit statusMessage(tr("Running numerical solver..."));
        runCalculation(fcttask);
        finishSolve(true);
    } catch (const std::exception &error) {
        finishSolve(false, QString::fromUtf8(error.what()));
    } catch (...) {
        finishSolve(false, tr("Unexpected error while running the solver."));
    }
}

void Solver::runCalculation(void (*fcttask)(double*, double*, double*, double*, double*,
                                            int, int, double, double, int, int*, int*))
{
    std::unique_ptr<double[]> zStorage(new double[n + 1]);
    std::unique_ptr<double[]> pxStorage(new double[m + 1]);
    std::unique_ptr<double[]> z1Storage(new double[n + 1]);
    std::unique_ptr<double[]> px1Storage(new double[m + 1]);
    std::unique_ptr<double[]> fStorage(new double[n + 1]);
    std::unique_ptr<double[]> rj1Storage(new double[(n + 1) * (n + 1)]);
    std::unique_ptr<double[]> rj2Storage(new double[(n + 1) * (n + 1)]);
    std::unique_ptr<int[]> ipStorage(new int[20 + 2 * (n + 1) + 6 * (m + 1)]);

    double *z = zStorage.get();
    double *px = pxStorage.get();
    double *z1 = z1Storage.get();
    double *px1 = px1Storage.get();
    double *f = fStorage.get();
    double *rj1 = rj1Storage.get();
    double *rj2 = rj2Storage.get();
    int *ip = ipStorage.get();
    double t = 0.0;
    double h = 0.0;
    double tkv = 0.0;
    int ncon = 0;
    int nbad = 1;
    int ier = rj2_before ? 0 : -1;

    paxData.clear();
    paxData.resize(trace.size() + 1);
    maxPoints = qMax(1, maxMemSize / (static_cast<int>(sizeof(double)) * paxData.size()));
    tout = t0 + (tk - t0) / maxPoints;
    tp = t0 + (tk - t0) / 100;

    for (int i = 1; i <= n; ++i)
        z1[i] = z[i] = 0.0;

    for (const auto &variable : system->variables) {
        z[variable.id] = variable.initial;
        z1[variable.id] = fabs(z[variable.id]);
        std::cout << variable.name << " [" << variable.id << "] = " << variable.initial << "\n";
    }
    for (int i = 1; i <= m; ++i)
        px[i] = px1[i] = 0.0;

    manzhuk(z, px, z1, px1, f, rj1, rj2, t, t0, tk, h, hmn, hmx, eps,
            &tkv, n, m, nm, ncon, &nbad, &ier, ip, fcttask, global_outtask);
}

void Solver::finishSolve(bool success, const QString &message)
{
    if (!busy_)
        return;

    outTextStream.reset();
    if (outFile) {
        if (outFile->isOpen())
            outFile->close();
        outFile.reset();
    }
    if (fcttaskLibrary_.isLoaded())
        fcttaskLibrary_.unload();

    busy_ = false;
    emit solveFinished(success, message);
}
Solver::~Solver(void)
{
    // FcttaskCompiler stops the child process when Solver is destroyed.
}
