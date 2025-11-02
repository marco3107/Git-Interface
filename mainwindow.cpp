#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gitObject = new GitClass(this);

    gitObject->startAutoUpdate(2000);

    ///////////////////////////////////////////////////////////////////////////
    // Connect button state with its text, repositoryPathLabel and interface //
    ///////////////////////////////////////////////////////////////////////////
    connect(ui->RepoButton, &QPushButton::toggled, this, [=](bool checked)
    {
        ui->errorLabel->clear();

        ui->RepoButton->setText(checked == false ? "SHOW" : "UNDO");
        ui->repositoryPathLabel->setEnabled(checked == false ? true : false);
        ui->InterfaceFrame->setEnabled(checked == true ? true : false);

        ///////////////////////////////////////////////
        //         Save git directory path.          //
        // If .git dir is not present, show an error //
        ///////////////////////////////////////////////
        QString path = ui->repositoryPathLabel->toPlainText();
        QDir gitDir(path + "/.git");
        if (gitDir.exists())
        {
            ////////////////////////////////////
            // After button is pressed, show  //
            // git status command on logLabel //
            ////////////////////////////////////
            gitObject->setRepoPath(path);
            QString result = gitObject->getStatus();
            QString shortResult = gitObject->getShortStatus();
            if(result == "ERROR" || shortResult == "ERROR")
            {
                setErrorLabelText("ERROR: git status return error");
                ui->RepoButton->setChecked(false);
            }
            else
            {
                ui->logLabel->setPlainText(result);
                ui->fileStatusLabel->setPlainText(shortResult);
            }
        }
        else {
            setErrorLabelText("ERROR: Not a git repository");
            ui->RepoButton->setChecked(false);

            gitObject->stopAutoUpdate();
            return;
        }
    } );

    connect(gitObject, &GitClass::fileStatusShortUpdated, this, [=](const QString &result)
    {
        if (ui->RepoButton->isChecked() == false)  // se il pulsante non è premuto, ignora
            return;

        if(result == "ERROR")
        {
            setErrorLabelText("ERROR: git status return error");
            ui->RepoButton->setChecked(false);
            gitObject->stopAutoUpdate();
        }
        else
        {
            ui->fileStatusLabel->setPlainText(result);
        }
    });
}

void MainWindow::setErrorLabelText(const QString &text)
{
    ui->errorLabel->setPlainText(text);
}

MainWindow::~MainWindow()
{
    delete ui;
}
