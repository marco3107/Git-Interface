#include "gitclass.h"

gitclass::gitclass(QObject *parent)
    : QObject(parent)
{
}

QString gitclass::getStatus(const QString &repoPath)
{
    QProcess process;
    process.setProgram("git");
    process.setArguments({"status"});
    process.setWorkingDirectory(repoPath);

    process.start();
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QString error  = process.readAllStandardError();

    if (!error.isEmpty())
        output = "ERROR";

    return output;
}
