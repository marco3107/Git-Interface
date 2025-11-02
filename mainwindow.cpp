#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gitclass.h"

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
        ui->errorLabel->clear();

        ui->RepoButton->setText(checked == 0 ? "SHOW" : "UNDO");
        ui->repositoryPathLabel->setEnabled(checked == 0 ? true : false);
        ui->InterfaceFrame->setEnabled(checked == 1 ? true : false);

        ///////////////////////////////////////////////
        //         Save git directory path.          //
        // If .git dir is not present, show an error //
        ///////////////////////////////////////////////
        QString path = ui->repositoryPathLabel->toPlainText();
        QDir gitDir(path + "/.git");
        if (gitDir.exists()) {
            setRepoPath(path);

            ////////////////////////////////////
            // After button is pressed, show  //
            // git status command on logLabel //
            ////////////////////////////////////
            gitclass git(this);
            QString result = git.getStatus(repoPath);
            if(result == "ERROR")
            {
                setErrorLabelText("ERROR: git status return error");
                ui->RepoButton->setChecked(false);
            }
            else
                ui->logLabel->setPlainText(result);
        }
        else {
            setErrorLabelText("ERROR: Not a git repository");
            ui->RepoButton->setChecked(false);
        }
    } );
}

void MainWindow::setRepoPath(const QString &path)
{
    repoPath = path;
}

void MainWindow::setErrorLabelText(const QString &text)
{
    ui->errorLabel->insertPlainText(text);
}

MainWindow::~MainWindow()
{
    delete ui;
}
