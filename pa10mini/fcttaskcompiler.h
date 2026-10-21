#pragma once

#include <QObject>
#include <QProcess>
#include <QProcessEnvironment>
#include <QTimer>

class FcttaskCompiler : public QObject
{
    Q_OBJECT

public:
    explicit FcttaskCompiler(QObject *parent = nullptr, int timeoutMs = 120000);
    ~FcttaskCompiler() override;

    bool isRunning() const;

    bool start(const QString &compilerPath,
               const QString &workingDirectory,
               const QString &sourcePath,
               const QString &outputPath,
               QString *errorMessage,
               const QProcessEnvironment &baseEnvironment = QProcessEnvironment::systemEnvironment());

signals:
    void started();
    void finished(bool success, const QString &report);

private:
    QString resolveCompiler(const QString &compilerPath,
                            const QProcessEnvironment &environment) const;
    void collectOutput();
    void finish(bool success, const QString &reason = QString());
    QString makeReport(bool success, const QString &reason) const;

    QProcess process_;
    QTimer timeoutTimer_;
    QString compilerPath_;
    QString outputPath_;
    QByteArray output_;
    qint64 totalOutputBytes_ = 0;
    int timeoutMs_ = 120000;
    bool running_ = false;
    bool timedOut_ = false;
};
