#include "fcttaskcompiler.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>

#include <algorithm>

#if defined(Q_OS_WIN)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace {
const int MaxCapturedOutputBytes = 1024 * 1024;
}

FcttaskCompiler::FcttaskCompiler(QObject *parent, int timeoutMs)
    : QObject(parent), process_(this), timeoutTimer_(this), timeoutMs_(timeoutMs)
{
    timeoutTimer_.setSingleShot(true);

#if defined(Q_OS_WIN) && QT_VERSION >= QT_VERSION_CHECK(5, 7, 0)
    process_.setCreateProcessArgumentsModifier([](QProcess::CreateProcessArguments *arguments) {
        arguments->flags |= CREATE_NO_WINDOW;
    });
#endif

    connect(&process_, &QProcess::started, this, [this]() {
        timeoutTimer_.start(timeoutMs_);
        emit started();
    });
    connect(&process_, &QProcess::readyReadStandardOutput, this, &FcttaskCompiler::collectOutput);
    connect(&process_, &QProcess::readyReadStandardError, this, &FcttaskCompiler::collectOutput);
    connect(&process_, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        if (error == QProcess::FailedToStart)
            finish(false, process_.errorString());
    });
    connect(&process_,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this,
            [this](int exitCode, QProcess::ExitStatus exitStatus) {
                collectOutput();
                timeoutTimer_.stop();

                if (timedOut_) {
                    finish(false, tr("Compilation exceeded the %1 second time limit.")
                                      .arg(timeoutMs_ / 1000));
                } else if (exitStatus != QProcess::NormalExit) {
                    finish(false, tr("The compiler terminated unexpectedly (exit code %1, status %2).")
                                      .arg(exitCode).arg(static_cast<int>(exitStatus)));
                } else if (exitCode != 0) {
                    finish(false, tr("The compiler exited with code %1.").arg(exitCode));
                } else {
                    const QFileInfo outputInfo(outputPath_);
                    if (!outputInfo.exists() || !outputInfo.isFile() || outputInfo.size() <= 0) {
                        finish(false, tr("The compiler succeeded but did not create a non-empty library."));
                    } else {
                        finish(true);
                    }
                }
            });
    connect(&timeoutTimer_, &QTimer::timeout, this, [this]() {
        timedOut_ = true;
        if (process_.state() != QProcess::NotRunning)
            process_.kill();
    });
}

FcttaskCompiler::~FcttaskCompiler()
{
    timeoutTimer_.stop();
    running_ = false;
    if (process_.state() != QProcess::NotRunning) {
        process_.kill();
        QFile::remove(outputPath_);
    }
}

bool FcttaskCompiler::isRunning() const
{
    return running_;
}

bool FcttaskCompiler::start(const QString &compilerPath,
                            const QString &workingDirectory,
                            const QString &sourcePath,
                            const QString &outputPath,
                            QString *errorMessage,
                            const QProcessEnvironment &baseEnvironment)
{
    if (running_) {
        if (errorMessage)
            *errorMessage = tr("A fcttask compilation is already running.");
        return false;
    }

    const QString absoluteWorkingDirectory = QFileInfo(workingDirectory).absoluteFilePath();
    const QString absoluteSourcePath = QFileInfo(sourcePath).absoluteFilePath();
    const QString absoluteOutputPath = QFileInfo(outputPath).absoluteFilePath();
    const QFileInfo workingDirectoryInfo(absoluteWorkingDirectory);
    const QFileInfo sourceInfo(absoluteSourcePath);
    const QFileInfo headerInfo(QDir(sourceInfo.absolutePath()).filePath("fcttask.h"));
    const QString resolvedCompiler = resolveCompiler(compilerPath, baseEnvironment);
    const QFileInfo compilerInfo(resolvedCompiler);

    if (resolvedCompiler.isEmpty() || !compilerInfo.exists() || !compilerInfo.isFile()
        || !compilerInfo.isExecutable()) {
        if (errorMessage) {
            *errorMessage = compilerPath.trimmed().isEmpty()
                ? tr("The MinGW g++ compiler is not configured or could not be found in PATH.")
                : tr("The configured compiler is not an executable file: %1").arg(compilerPath);
        }
        return false;
    }
    if (!workingDirectoryInfo.exists() || !workingDirectoryInfo.isDir()) {
        if (errorMessage)
            *errorMessage = tr("Working directory does not exist: %1").arg(absoluteWorkingDirectory);
        return false;
    }
    if (!sourceInfo.exists() || !sourceInfo.isFile()) {
        if (errorMessage)
            *errorMessage = tr("Generated fcttask source does not exist: %1").arg(absoluteSourcePath);
        return false;
    }
    if (!headerInfo.exists() || !headerInfo.isFile()) {
        if (errorMessage)
            *errorMessage = tr("The fcttask header was not found: %1").arg(headerInfo.absoluteFilePath());
        return false;
    }

    if (QFileInfo::exists(absoluteOutputPath) && !QFile::remove(absoluteOutputPath)) {
        if (errorMessage)
            *errorMessage = tr("Cannot remove the previous fcttask library: %1").arg(absoluteOutputPath);
        return false;
    }

    QStringList arguments;
    arguments << "-shared";
#if defined(Q_OS_WIN)
    arguments << "-static";
#else
    arguments << "-fPIC";
#endif
    arguments << absoluteSourcePath << "-o" << absoluteOutputPath;

    QProcessEnvironment environment = baseEnvironment;
    const QString compilerDirectory = compilerInfo.absolutePath();
    QString path = environment.value("PATH");
    if (!path.isEmpty())
        path.prepend(QDir::listSeparator());
    path.prepend(compilerDirectory);
    environment.insert("PATH", path);

    compilerPath_ = compilerInfo.absoluteFilePath();
    outputPath_ = absoluteOutputPath;
    output_.clear();
    totalOutputBytes_ = 0;
    timedOut_ = false;
    running_ = true;

    process_.setWorkingDirectory(absoluteWorkingDirectory);
    process_.setProcessEnvironment(environment);
    process_.start(compilerPath_, arguments);
    return true;
}

QString FcttaskCompiler::resolveCompiler(const QString &compilerPath,
                                         const QProcessEnvironment &environment) const
{
    const QString configuredPath = compilerPath.trimmed();
    if (!configuredPath.isEmpty())
        return QFileInfo(configuredPath).absoluteFilePath();

#if defined(Q_OS_WIN)
    Q_UNUSED(environment)
    return QString();
#else
    const QStringList searchPaths = environment.value("PATH").split(QDir::listSeparator(), Qt::SkipEmptyParts);
    return QStandardPaths::findExecutable("g++", searchPaths);
#endif
}

void FcttaskCompiler::collectOutput()
{
    const QByteArray newlyAvailable = process_.readAllStandardOutput()
        + process_.readAllStandardError();
    totalOutputBytes_ += newlyAvailable.size();

    const int remainingCapacity = MaxCapturedOutputBytes - output_.size();
    if (remainingCapacity > 0)
        output_.append(newlyAvailable.constData(), std::min(remainingCapacity, newlyAvailable.size()));
}

void FcttaskCompiler::finish(bool success, const QString &reason)
{
    if (!running_)
        return;

    running_ = false;
    timeoutTimer_.stop();
    if (!success)
        QFile::remove(outputPath_);
    emit finished(success, makeReport(success, reason));
}

QString FcttaskCompiler::makeReport(bool success, const QString &reason) const
{
    QString report;
    if (success) {
        report = tr("Compilation succeeded: %1").arg(outputPath_);
    } else {
        report = tr("Failed to compile fcttask with %1.").arg(compilerPath_);
        if (!reason.isEmpty())
            report += QStringLiteral("\n") + reason;
    }

    if (!output_.isEmpty())
        report += QStringLiteral("\n") + QString::fromLocal8Bit(output_);
    if (totalOutputBytes_ > output_.size())
        report += tr("\nCompiler output truncated after %1 bytes.").arg(output_.size());
    return report;
}
