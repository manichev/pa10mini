#include "../pa10mini/fcttaskcompiler.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcessEnvironment>
#include <QSignalSpy>
#include <QTemporaryDir>
#include <QTimer>
#include <QtTest>

class FcttaskCompilerTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void argumentsAndPathsArePassedWithoutShellParsing();
    void failedCompileRemovesPartialOutput();
    void zeroExitWithoutLibraryIsFailure();
    void missingCompilerIsReportedBeforeStart();
    void missingHeaderIsReportedBeforeStart();
    void emptyCompilerSettingIsRejectedOnWindows();
    void cannotRemovePreviousLibraryPreventsStart();
    void compilerTimeoutStopsTheOperation();
    void crashedCompilerIsReported();
    void largeDiagnosticsAreDrainedAndBounded();
    void overlappingRunIsRejectedAndRetryWorksAfterFailure();
    void linuxSearchesConfiguredPathWhenCompilerIsEmpty();

private:
    bool start(const QString &mode, QString *errorMessage = nullptr);

    QTemporaryDir temporaryDirectory_;
    QString workingDirectory_;
    QString sourcePath_;
    QString outputPath_;
    QString compilerPath_;
};

void FcttaskCompilerTest::init()
{
    QVERIFY(temporaryDirectory_.isValid());

    workingDirectory_ = QDir(temporaryDirectory_.path()).filePath(QString::fromUtf8("work & каталог"));
    QVERIFY(QDir().mkpath(workingDirectory_));

    const QString taskDirectory = QDir(workingDirectory_).filePath("manzhuk/fcttask");
    QVERIFY(QDir().mkpath(taskDirectory));
    sourcePath_ = QDir(taskDirectory).filePath("fcttask.cpp");
    QFile source(sourcePath_);
    QVERIFY(source.open(QIODevice::WriteOnly));
    source.write("void fcttask() {}\n");
    source.close();
    QFile header(QDir(taskDirectory).filePath("fcttask.h"));
    QVERIFY(header.open(QIODevice::WriteOnly));
    header.write("// test header\n");
    header.close();

#if defined(Q_OS_WIN)
    const QString outputName = "fcttask.dll";
    const QString fixtureName = "fcttask_process_fixture.exe";
#else
    const QString outputName = "fcttask.so";
    const QString fixtureName = "fcttask_process_fixture";
#endif
    outputPath_ = QDir(taskDirectory).filePath(outputName);
    compilerPath_ = QDir(temporaryDirectory_.path())
        .filePath(QString::fromUtf8("tool chain & тест") + QDir::separator() + fixtureName);
    QVERIFY(QDir().mkpath(QFileInfo(compilerPath_).absolutePath()));
    QFile::remove(compilerPath_);
    QVERIFY(QFile::copy(QDir(QCoreApplication::applicationDirPath()).filePath(fixtureName), compilerPath_));
    QVERIFY(QFile::setPermissions(compilerPath_, QFileInfo(compilerPath_).permissions()));
}

bool FcttaskCompilerTest::start(const QString &mode, QString *errorMessage)
{
    const int timeoutMs = mode == QLatin1String("timeout") ? 150 : 5000;
    FcttaskCompiler compiler(nullptr, timeoutMs);
    QSignalSpy finishedSpy(&compiler, SIGNAL(finished(bool,QString)));
    if (!finishedSpy.isValid()) {
        if (errorMessage)
            *errorMessage = QStringLiteral("Could not observe compiler completion.");
        return false;
    }

    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    environment.insert("FCTTASK_TEST_MODE", mode);
    environment.insert("PATH", QStringLiteral("original tool path")
                                   + QDir::listSeparator() + environment.value("PATH"));

    const bool started = compiler.start(compilerPath_, workingDirectory_, sourcePath_, outputPath_,
                                        errorMessage, environment);
    if (!started)
        return false;

    if (finishedSpy.count() == 0)
        if (!finishedSpy.wait(10000)) {
            if (errorMessage)
                *errorMessage = QStringLiteral("Compiler did not finish before the test timeout.");
            return false;
        }
    if (finishedSpy.count() != 1) {
        if (errorMessage)
            *errorMessage = QStringLiteral("Compiler emitted an unexpected number of completion signals.");
        return false;
    }
    if (errorMessage)
        *errorMessage = finishedSpy.at(0).at(1).toString();
    return finishedSpy.at(0).at(0).toBool();
}

void FcttaskCompilerTest::argumentsAndPathsArePassedWithoutShellParsing()
{
    bool eventLoopWasResponsive = false;
    QTimer eventLoopTimer;
    eventLoopTimer.setSingleShot(true);
    connect(&eventLoopTimer, &QTimer::timeout, this, [&eventLoopWasResponsive]() {
        eventLoopWasResponsive = true;
    });
    eventLoopTimer.start(0);

    QString errorMessage;
    QVERIFY(start(QStringLiteral("success"), &errorMessage));
    QVERIFY2(errorMessage.contains(QStringLiteral("arg=-shared")), qPrintable(errorMessage));
#if defined(Q_OS_WIN)
    QVERIFY(errorMessage.contains(QStringLiteral("arg=-static")));
#else
    QVERIFY(errorMessage.contains(QStringLiteral("arg=-fPIC")));
#endif
    QVERIFY(errorMessage.contains(QStringLiteral("work &")));
    QVERIFY(errorMessage.contains(QStringLiteral("arg=-o")));
    QVERIFY(errorMessage.contains(QFileInfo(outputPath_).absoluteFilePath()));
    QVERIFY(errorMessage.contains(QStringLiteral("cwd=") + workingDirectory_));
    const int childPathStart = errorMessage.indexOf(QStringLiteral("PATH="));
    QVERIFY(childPathStart >= 0);
    const int childPathEnd = errorMessage.indexOf(QLatin1Char('\n'), childPathStart);
    const QString childPath = errorMessage.mid(childPathStart + 5,
        (childPathEnd < 0 ? errorMessage.size() : childPathEnd) - childPathStart - 5);
    const QString compilerDirectory = QFileInfo(compilerPath_).absolutePath();
    const int compilerDirectoryIndex = childPath.indexOf(compilerDirectory, Qt::CaseInsensitive);
    const int inheritedPathIndex = childPath.indexOf(QStringLiteral("original tool path"));
    QVERIFY(compilerDirectoryIndex >= 0);
    QVERIFY(inheritedPathIndex > compilerDirectoryIndex);
    QVERIFY(eventLoopWasResponsive);
    QVERIFY(QFileInfo(outputPath_).size() > 0);
}

void FcttaskCompilerTest::failedCompileRemovesPartialOutput()
{
    QFile oldLibrary(outputPath_);
    QVERIFY(oldLibrary.open(QIODevice::WriteOnly));
    oldLibrary.write("stale library");
    oldLibrary.close();

    QString errorMessage;
    QVERIFY(!start(QStringLiteral("fail"), &errorMessage));
    QVERIFY(errorMessage.contains(QStringLiteral("code 23")));
    QVERIFY(!QFileInfo::exists(outputPath_));
}

void FcttaskCompilerTest::zeroExitWithoutLibraryIsFailure()
{
    QString errorMessage;
    QVERIFY(!start(QStringLiteral("empty-success"), &errorMessage));
    QVERIFY(errorMessage.contains(QStringLiteral("non-empty library")));
}

void FcttaskCompilerTest::missingCompilerIsReportedBeforeStart()
{
    FcttaskCompiler compiler;
    QString errorMessage;
    QVERIFY(!compiler.start(QDir(temporaryDirectory_.path()).filePath("missing compiler"),
                            workingDirectory_, sourcePath_, outputPath_, &errorMessage));
    QVERIFY(errorMessage.contains(QStringLiteral("not an executable")));
}

void FcttaskCompilerTest::missingHeaderIsReportedBeforeStart()
{
    const QString headerPath = QFileInfo(sourcePath_).dir().filePath("fcttask.h");
    QVERIFY(QFile::remove(headerPath));

    FcttaskCompiler compiler;
    QString errorMessage;
    QVERIFY(!compiler.start(compilerPath_, workingDirectory_, sourcePath_, outputPath_, &errorMessage));
    QVERIFY(errorMessage.contains(QStringLiteral("fcttask header was not found")));
}

void FcttaskCompilerTest::emptyCompilerSettingIsRejectedOnWindows()
{
#if !defined(Q_OS_WIN)
    QSKIP("Windows requires an explicitly configured MinGW compiler.");
#else
    FcttaskCompiler compiler;
    QString errorMessage;
    QVERIFY(!compiler.start(QString(), workingDirectory_, sourcePath_, outputPath_, &errorMessage));
    QVERIFY(errorMessage.contains(QStringLiteral("not configured")));
#endif
}

void FcttaskCompilerTest::cannotRemovePreviousLibraryPreventsStart()
{
    const QString outputDirectory = QDir(QFileInfo(outputPath_).absolutePath()).filePath("blocked-library");
    QVERIFY(QDir().mkpath(outputDirectory));

    FcttaskCompiler compiler;
    QString errorMessage;
    QVERIFY(!compiler.start(compilerPath_, workingDirectory_, sourcePath_, outputDirectory, &errorMessage));
    QVERIFY(errorMessage.contains(QStringLiteral("remove the previous fcttask library")));
}

void FcttaskCompilerTest::compilerTimeoutStopsTheOperation()
{
    QString errorMessage;
    QVERIFY(!start(QStringLiteral("timeout"), &errorMessage));
    QVERIFY(errorMessage.contains(QStringLiteral("time limit")));
    QVERIFY(!QFileInfo::exists(outputPath_));
}

void FcttaskCompilerTest::crashedCompilerIsReported()
{
    QString errorMessage;
    QVERIFY(!start(QStringLiteral("crash"), &errorMessage));
    QVERIFY2(errorMessage.contains(QStringLiteral("terminated unexpectedly"))
                 || errorMessage.contains(QStringLiteral("exited with code")),
             qPrintable(errorMessage));
    QVERIFY(!QFileInfo::exists(outputPath_));
}

void FcttaskCompilerTest::largeDiagnosticsAreDrainedAndBounded()
{
    QString errorMessage;
    QVERIFY(start(QStringLiteral("large-output"), &errorMessage));
    QVERIFY(errorMessage.contains(QStringLiteral("diagnostic-output-line")));
    QVERIFY(errorMessage.contains(QStringLiteral("truncated after 1048576 bytes")));
}

void FcttaskCompilerTest::overlappingRunIsRejectedAndRetryWorksAfterFailure()
{
    FcttaskCompiler compiler;
    QSignalSpy finishedSpy(&compiler, SIGNAL(finished(bool,QString)));
    QVERIFY(finishedSpy.isValid());

    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    environment.insert("FCTTASK_TEST_MODE", QStringLiteral("fail"));
    QString errorMessage;
    QVERIFY(compiler.start(compilerPath_, workingDirectory_, sourcePath_, outputPath_,
                           &errorMessage, environment));
    QVERIFY(compiler.isRunning());
    QVERIFY(!compiler.start(compilerPath_, workingDirectory_, sourcePath_, outputPath_,
                            &errorMessage, environment));
    QVERIFY(errorMessage.contains(QStringLiteral("already running")));
    QVERIFY(finishedSpy.wait(5000));
    QCOMPARE(finishedSpy.count(), 1);
    QVERIFY(!finishedSpy.at(0).at(0).toBool());
    QVERIFY(!compiler.isRunning());

    environment.insert("FCTTASK_TEST_MODE", QStringLiteral("success"));
    QVERIFY(compiler.start(compilerPath_, workingDirectory_, sourcePath_, outputPath_,
                           &errorMessage, environment));
    if (finishedSpy.count() == 1)
        QVERIFY(finishedSpy.wait(5000));
    QCOMPARE(finishedSpy.count(), 2);
    QVERIFY(finishedSpy.at(1).at(0).toBool());
}

void FcttaskCompilerTest::linuxSearchesConfiguredPathWhenCompilerIsEmpty()
{
#if defined(Q_OS_WIN)
    QSKIP("An empty compiler setting is supported only on Linux.");
#else
    const QString directory = QFileInfo(compilerPath_).absolutePath();
    const QString gxxPath = QDir(directory).filePath("g++");
    QVERIFY(QFile::copy(compilerPath_, gxxPath));
    QVERIFY(QFile::setPermissions(gxxPath, QFileInfo(compilerPath_).permissions()));

    FcttaskCompiler compiler;
    QSignalSpy finishedSpy(&compiler, SIGNAL(finished(bool,QString)));
    QVERIFY(finishedSpy.isValid());
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    environment.insert("PATH", directory + QDir::listSeparator() + QCoreApplication::applicationDirPath());
    QString errorMessage;
    QVERIFY(compiler.start(QString(), workingDirectory_, sourcePath_, outputPath_,
                           &errorMessage, environment));
    if (finishedSpy.count() == 0)
        QVERIFY(finishedSpy.wait(5000));
    QCOMPARE(finishedSpy.count(), 1);
    QVERIFY(finishedSpy.at(0).at(0).toBool());
    QVERIFY(finishedSpy.at(0).at(1).toString().contains(QStringLiteral("-fPIC")));
#endif
}

QTEST_GUILESS_MAIN(FcttaskCompilerTest)

#include "tst_fcttaskcompiler.moc"
