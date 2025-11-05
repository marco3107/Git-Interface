#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ////////////////////////////////
    // Create object of GitClass  //
    ////////////////////////////////
    gitObject = new GitClass(this);

    /////////////////////////////////
    // Start timer for auto-update //
    /////////////////////////////////
    gitObject->startAutoUpdate(2000);

    ///////////////////////////////////////////////////////////////////////////
    // Connect button state with its text, repositoryPathLabel and interface //
    ///////////////////////////////////////////////////////////////////////////
    connect(ui->RepoButton, &QPushButton::toggled, this, [=](bool checked)
    {
        ui->errorLabel->clear();

        ////////////////////////////////////////////////////////////////
        //             Button initial state: not checked              //
        // Set "SHOW" if button is not checked/is not already pressed //
        //          Set "UNDO" if button is checked/pressed           //
        ////////////////////////////////////////////////////////////////
        ui->RepoButton->setText(checked == false ? "SHOW" : "UNDO");
        /////////////////////////////////////////////
        // Enable frame and label of git interface //
        //      if button is checked/pressed       //
        /////////////////////////////////////////////
        ui->repositoryPathLabel->setEnabled(checked == false ? true : false);
        ui->InterfaceFrame->setEnabled(checked == true ? true : false);

        ///////////////////////////////////////////////
        //         Save git directory path          //
        // If .git dir is not present, show an error //
        ///////////////////////////////////////////////
        QString path = ui->repositoryPathLabel->toPlainText();
        QDir gitDir(path + "/.git");
        ////////////////////////////////////////////////////////
        // If a git repo exists, show status and short-status //
        //   Otherwise, send an error and abort auto-update   //
        ////////////////////////////////////////////////////////
        if (gitDir.exists() == true)
        {
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
                ui->fileTreeStatus->clear();
                QStringList shortStatusLines = shortResult.split('\n', Qt::SkipEmptyParts);
                for (const QString &line : shortStatusLines)
                {
                    ///////////////////////////////////////////
                    //            Example string             //
                    // (1-staged)(2-not staged)(3-file name) //
                    //        (M)(M)(mainwindow.cpp)         //
                    ///////////////////////////////////////////
                    QString stageStatus = line.at(0);
                    QString unStageStatus = line.at(1);
                    QString fileName = line.mid(3);

                    QTreeWidgetItem *item = new QTreeWidgetItem(ui->fileTreeStatus);
                    item->setText(0, fileName.trimmed());
                    item->setText(1, unStageStatus);
                    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                    item->setCheckState(2, (stageStatus != ' ' && stageStatus != '?')
                                               ? Qt::Checked : Qt::Unchecked);

                    if (unStageStatus == 'M' || stageStatus == 'M')
                        item->setForeground(1, QBrush(Qt::darkYellow));
                    else if (unStageStatus == 'A' || stageStatus == 'A')
                        item->setForeground(1, QBrush(Qt::green));
                    else if (unStageStatus == '?' || stageStatus == '?')
                        item->setForeground(1, QBrush(Qt::blue));
                }
                gitObject->stopAutoUpdate();
                return;
            }
        }
        else {
            setErrorLabelText("ERROR: Not a git repository");
            ui->RepoButton->setChecked(false);
            gitObject->stopAutoUpdate();
            return;
        }
    } );

    //////////////////////////////////////////////////////////////
    // Connect fileStatusShortUpdated signal to lambda(funcion) //
    //////////////////////////////////////////////////////////////
    connect(gitObject, &GitClass::fileStatusShortUpdated, this, [=](const QString &shortResult)
    {
        //////////////////////////////////////////////////////
        // If button is not checked/already pressed, ignore //
        //////////////////////////////////////////////////////
        if (ui->RepoButton->isChecked() == false)
            return;

        ////////////////////////////////////////////////////////
        // If output of getShortStatus() function is an error //
        //        send an error and abort auto-update         //
        //              Otherwise, update label               //
        ////////////////////////////////////////////////////////
        if(shortResult == "ERROR")
        {
            setErrorLabelText("ERROR: git status return error");
            ui->RepoButton->setChecked(false);
            gitObject->stopAutoUpdate();
        }
        else
        {
            //ui->fileStatusLabel->setPlainText(shortResult);
            QStringList shortStatusLines = shortResult.split('\n', Qt::SkipEmptyParts);
            for (const QString &line : shortStatusLines)
            {
                QString status = line.left(1);
                QString fileName = line.mid(2);

                QTreeWidgetItem *item = new QTreeWidgetItem(ui->fileTreeStatus);
                item->setText(0, fileName.trimmed());
                item->setText(1, status);

                // colore per lo stato
                if (status == "M")
                    item->setForeground(0, QBrush(Qt::yellow));
                else if (status == "A")
                    item->setForeground(0, QBrush(Qt::green));
                else if (status == "?")
                    item->setForeground(0, QBrush(Qt::blue));
            }
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
