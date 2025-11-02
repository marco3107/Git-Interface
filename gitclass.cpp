#include "gitclass.h"

GitClass::GitClass(QObject *parent)
    : QObject(parent)
{
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &GitClass::updateShortStatus);
}

QString GitClass::getStatus()
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

QString GitClass::getShortStatus()
{
    QProcess process;
    process.setProgram("git");
    process.setArguments({"status", "-s"});
    process.setWorkingDirectory(repoPath);

    process.start();
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QString error  = process.readAllStandardError();

    if (!error.isEmpty())
        output = "ERROR";

    return output;
}

void GitClass::setRepoPath(const QString &path)
{
    repoPath = path;
}

void GitClass::startAutoUpdate(int intervalMs)
{
    if (!timer->isActive()) {
        timer->start(intervalMs);
    }
}

void GitClass::stopAutoUpdate()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void GitClass::updateShortStatus()
{
    if (repoPath.isEmpty())
        return;

    QString shortStatus = getShortStatus();
    emit fileStatusShortUpdated(shortStatus);
}
