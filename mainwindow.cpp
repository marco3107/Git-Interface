#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ////////////////////////////////////////////////////////////////
    // Connect button state with its text and repositoryPathLabel //
    //                 Not pressed -> show label                  //
    //                   Pressed -> hide label                    //
    ////////////////////////////////////////////////////////////////
    connect(ui->RepoButton, &QPushButton::toggled, this, [=](bool checked)
    {
        ui->RepoButton->setText(checked == 0 ? "SHOW" : "UNDO");
        ui->repositoryPathLabel->setEnabled(checked == 0 ? true : false);
    } );
}

MainWindow::~MainWindow()
{
    delete ui;
}
