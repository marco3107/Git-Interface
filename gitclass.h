#ifndef GITCLASS_H
#define GITCLASS_H

#include <QObject>
#include <QString>
#include <QProcess>
#include <QTimer>

class GitClass : public QObject
{
    Q_OBJECT
public:
    explicit GitClass(QObject *parent = nullptr);

    void setRepoPath(const QString &path);
    QString getStatus();
    QString getShortStatus();
    void startAutoUpdate(int intervalms);
    void stopAutoUpdate();

private:
    QString repoPath;
    QTimer *timer;

private slots:
    void updateShortStatus();

signals:
    void fileStatusShortUpdated(const QString &status);
};

#endif // GITCLASS_H
