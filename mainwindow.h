#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include "gitclass.h"

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
    void setErrorLabelText(const QString &text);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GitClass *gitObject;
};
#endif // MAINWINDOW_H
