#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setRepoPath(const QString &path);
    void setErrorLabelText(const QString &text);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString repoPath;
};
#endif // MAINWINDOW_H
