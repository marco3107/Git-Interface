#ifndef GITCLASS_H
#define GITCLASS_H

#include <QObject>
#include <QString>
#include <QProcess>

class gitclass : public QObject   // Maiuscola per convenzione
{
    Q_OBJECT
public:
    explicit gitclass(QObject *parent = nullptr);
    QString getStatus(const QString &repoPath);  // prende il percorso della repo come argomento
};

#endif // GITCLASS_H
