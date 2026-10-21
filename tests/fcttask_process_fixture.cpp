#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QThread>

#include <cstdlib>

#if !defined(Q_OS_WIN)
#include <csignal>
#include <sys/resource.h>
#endif

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);
    Q_UNUSED(application)

    const QString mode = QString::fromLocal8Bit(qgetenv("FCTTASK_TEST_MODE"));
    QTextStream output(stdout);
    output << "cwd=" << QDir::currentPath() << '\n';
    output << "PATH=" << QString::fromLocal8Bit(qgetenv("PATH")) << '\n';
    for (int i = 1; i < argc; ++i)
        output << "arg=" << QString::fromLocal8Bit(argv[i]) << '\n';
    output.flush();

    if (mode == QLatin1String("timeout")) {
        QThread::msleep(5000);
    } else if (mode == QLatin1String("crash")) {
#if !defined(Q_OS_WIN)
        const struct rlimit noCoreDumps = {0, 0};
        setrlimit(RLIMIT_CORE, &noCoreDumps);
        std::raise(SIGSEGV);
#else
        std::abort();
#endif
    } else if (mode == QLatin1String("large-output")) {
        for (int i = 0; i < 20000; ++i)
            output << "diagnostic-output-line-0123456789abcdefghijklmnopqrstuvwxyz\n";
        output.flush();
    }

    if (mode == QLatin1String("empty-success"))
        return 0;

    QString outputPath;
    for (int i = 1; i + 1 < argc; ++i) {
        if (QString::fromLocal8Bit(argv[i]) == QLatin1String("-o")) {
            outputPath = QString::fromLocal8Bit(argv[i + 1]);
            break;
        }
    }
    if (outputPath.isEmpty())
        return 89;

    QFile library(outputPath);
    if (!library.open(QIODevice::WriteOnly))
        return 90;
    library.write("fixture-library");
    library.close();

    if (mode == QLatin1String("fail"))
        return 23;
    return 0;
}
