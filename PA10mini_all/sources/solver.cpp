#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <QDebug>
#include <QFileInfo>

#if _MSC_VER && !__INTEL_COMPILER
#include <io.h>
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

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
}

void Solver::setSystem(DAESystem* system_)
{
    system = system_;
    system->updateAllIds();
    Variable variable;
    names.clear();
    trace.clear();
    dims.clear();
    QVector<QString> dnames;
    foreach(variable, system->variables)
    {
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
    ofstream file;
    file.open("manzhuk/fcttask/fcttask.cpp");

    file << "#include \"fcttask.h\"\n";
    file << "#include <cmath>\n\n";
    file << "void fcttask(double z[], double px[], double f[], double rj1[], double rj2[], int n, int m, double t, double h, int ncon, int *nbad, int ip[])\n";
    file << "{\n";

    std::list<Expression*>::iterator eqIt;
    Expression* der;
    int i = 1;
    for (eqIt = system->equals.begin(); eqIt != system->equals.end(); ++eqIt) {
        file << "\tf[" << i << "] = ";
        (*eqIt)->simplify();
        (*eqIt)->print_c_ostream(file);
        file << ";\n";

        for (int j = 1; j <= m; ++j) {
            der = (*eqIt)->derivative(-j);
            if (!der->isConst(0.0)) {
                file << "\trj1[" << i << "*n+"<< + j << "] = ";
                der->print_c_ostream(file);
                file << ";\n";
            }
        }

        if (rj2_before) {
            for (int j = 1; j <= n; ++j) {
                der = (*eqIt)->derivative(j);
                if (!der->isConst(0.0)) {
                    file << "\trj2[" << i << "*n+"<< + j << "] = ";
                    der->print_c_ostream(file);
                    file << ";\n";
                }
            }
        }
        ++i;
    }
    file << "}";
    file.close();

#ifdef WIN32
    // Compiling fcttask.dll
    remove("manzhuk/fcttask/fcttask.dll");
#if _MSC_VER && !__INTEL_COMPILER
    // std::system("manzhuk\\fcttask\\build_vc.bat");
#else
    // std::system("manzhuk\\fcttask\\build.cmd");
#endif

    QFileInfo MingwDir(pathToCompiler);
    auto str1 = QString("set PATH=%PATH%;%1").arg(MingwDir.path());
    auto str2 = MingwDir.filePath();
    auto str3 = "-shared -static manzhuk/fcttask/fcttask.cpp -o manzhuk/fcttask/fcttask.dll";
    std::system(QString("%1 && %2 %3").arg(str1).arg(str2).arg(str3).toStdString().data());

    // Removing extra files
    remove("manzhuk/fcttask/fcttask.lib");
    remove("manzhuk/fcttask/fcttask.exp");
    remove("fcttask.obj");
#else
    remove("manzhuk/fcttask/fcttask.so");
    std::system("sh manzhuk/fcttask/build_linux.sh");
#endif
}


void Solver::solve(const QString &pathToCompiler)
{
    double *z=nullptr, *px=nullptr, *z1=nullptr, *px1=nullptr, *f=nullptr, *rj1=nullptr, *rj2=nullptr;
    double t, h, tkv;

    int ncon, nbad, ier, *ip = nullptr;
    if (writeFile) {
        std::system("mkdir output");
        outFile = new QFile(outFileName);
        if (!outFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
            auto str = QString("Output file %1 wasn't opened on write").arg(outFileName);
            qCritical() << str;
            emit statusMessage(str);
            // return;
        }
        outTextStream = new QTextStream(outFile);
    }

    n = system->countEquals();
    m = system->countDerivatives();
    // if (system->countVariables() > system->countEquals())
    //    throw invalid_argument("NM!");
    // allocating memory
    z = new double[n + 1];
    px = new double[m + 1];
    z1 = new double[n + 1];
    px1 = new double[m + 1];
    f = new double[n + 1];
    rj1 = new double[(n + 1) * (n + 1)];
    rj2 = new double[(n + 1) * (n + 1)];
    ip = new int[20 + 2 * (n + 1) + 6 * (m + 1)];
    paxData.clear();
    paxData.resize(trace.size()+1);

    //initializing values
    t = 0.0;
    h = 0.0;
    ncon = 0;
    nbad = 1;

    ier = rj2_before ? 0 : -1;

    maxPoints = maxMemSize / (sizeof(double) * paxData.size());
    tout = t0 + (tk - t0) / maxPoints;
    tp = t0 + (tk - t0) / 100;

    create_fcttask(pathToCompiler);

    // Applying dll
#if _MSC_VER && !__INTEL_COMPILER

#ifdef UNICODE
    CONST WCHAR * fcttaskDllPath = L"manzhuk/fcttask/fcttask.dll";
#else
    CONST CHAR * fcttaskDllPath = "manzhuk/fcttask/fcttask.dll";
#endif
    HINSTANCE dll = LoadLibrary(fcttaskDllPath);
    DWORD dwError = 0;
    if (dll == nullptr) {
        dwError = GetLastError();
        cout << "Cannot load " << fcttaskDllPath << ", WinError: " << dwError;
        return;
    } else {
        cout << fcttaskDllPath << " Successfully loaded " << std::endl;
    }

    void (* fcttask)(double*, double*, double*, double*, double*, int, int, double, double, int, int*, int*) =
        (void (*)(double*, double*, double*, double*, double*, int, int, double, double, int, int*, int*))GetProcAddress(dll, "fcttask");

#else

#ifdef WIN32
    void *handle = dlopen("manzhuk/fcttask/fcttask.dll", RTLD_LAZY);
#else
    void *handle = dlopen("manzhuk/fcttask/fcttask.so", RTLD_LAZY);
#endif

    if (!handle) {
        auto str = QString("Can't open library: %1 \n").arg(dlerror());
        cerr << str.toStdString().data();
        emit statusMessage(str);
        return;
    }

    // load the symbol
    cout << "Loading symbol fcttask...\n";
    typedef void (*fcttask_t)(double*, double*, double*, double*, double*, int, int, double, double, int, int*, int*);

    // reset errors
    dlerror();
    fcttask_t fcttask = (fcttask_t) dlsym(handle, "fcttask");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        auto str = QString("Cannot load symbol 'fcttask': %1 \n").arg(dlsym_error);
        cerr << str.toStdString().data();
        emit statusMessage(str);
        dlclose(handle);
        return;
    }

#endif

// Solving with manzhuk
    std::list<Variable>::iterator it;
    std::cout.precision(3);
    for (int i = 1; i <= n; ++i)
        z1[i] = z[i] = 0.0;

    for (it = system->variables.begin(); it != system->variables.end(); ++it) {
        z[it->id] = it->initial;
        z1[it->id] = fabs(z[it->id]);
        std::cout<<it->name<< " ["<<it->id<<"] "<<" = "<<it->initial<<"\n";
    }
    for (int i = 1; i <= m; ++i)
        px[i] = px1[i] = 0.0;

//int stdout_copy = _dup(1);
//_close(1);
//int file1 = open("out.txt", 0);

    manzhuk(z, px, z1, px1, f, rj1, rj2, t, t0, tk, h, hmn, hmx, eps, &tkv, n, m, nm, ncon, &nbad, &ier, ip, fcttask, global_outtask);

//_close(file1);
//_dup2(stdout_copy, 1);
//_close(stdout_copy);

//free dll
#if _MSC_VER && !__INTEL_COMPILER
    if (dll != nullptr)
        FreeLibrary(dll);
#else
    dlclose(handle);
#endif
//free memory

    if (z)
        delete[] z;
    if (px)
        delete[] px;
    if (z1)
        delete[] z1;
    if (px1)
        delete[] px1;
    if (f)
        delete[] f;
    if (rj1)
        delete[] rj1;
    if (rj2)
        delete[] rj2;
    if (writeFile) {
        outFile->close();
        delete outFile;
        delete outTextStream;
    }
}

Solver::~Solver(void)
{
}
