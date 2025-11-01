#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ///////////////////////////////////////////////////////////////////////////
    // Connect button state with its text, repositoryPathLabel and interface //
    ///////////////////////////////////////////////////////////////////////////
    connect(ui->RepoButton, &QPushButton::toggled, this, [=](bool checked)
    {
        ui->RepoButton->setText(checked == 0 ? "SHOW" : "UNDO");
        ui->repositoryPathLabel->setEnabled(checked == 0 ? true : false);
        ui->InterfaceFrame->setEnabled(checked == 1 ? true : false);
    } );
}

MainWindow::~MainWindow()
{
    delete ui;
}
