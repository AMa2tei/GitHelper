#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <iostream>
#include <cstdarg>
#include <string>
#include <fstream>
#include <memory>
#include <cstdio>

#include <QDir>
#include <QFileDialog>
#include <QFile>

#include "gitconfig.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(
                ui->actionConfigure, &QAction::triggered,
                this, [=](){ this->on_actionConfigure_triggered();}
                );
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string exec(const char* cmd) {
    std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}

void MainWindow::on_pushButtonValidatePath_clicked()
{
    path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                            ".",
                                                            QFileDialog::ShowDirsOnly
                                                            | QFileDialog::DontUseNativeDialog);
    ui->lineEditPath->setText(path);
    if(QDir(path).isEmpty())
    {
        if(!ui->lineEditRemoteUrl->text().isEmpty()) {
            QString lien = ui->lineEditRemoteUrl->text();
            QStringList liste = lien.split("/");
            QStringList listeNameProject = liste.at(4).split(".");
            system(QString("cd " + path + " && echo \"# " + listeNameProject.at(0) + "\" >> README.md").toStdString().c_str());
        } else {
            system(QString("cd " + path + " && echo \"# Project\" >> README.md").toStdString().c_str());
        }
    }
    QString commandeQString = "cd " + path + " && git init";
    system(commandeQString.toStdString().c_str());
    QDir directorie(path);
    ui->comboBoxFilesInDirectory->clear();
    ui->comboBoxFilesInDirectory->addItems(directorie.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot, QDir::Name));

}

void MainWindow::on_pushButtonAddComit_clicked()
{
    QString commandeQString;
    if(ui->lineEditCommitMessage->text().isEmpty()) {
        commandeQString = "cd " + path + " && git commit -am \"Updated " +
                ui->comboBoxFilesInDirectory->itemText(ui->comboBoxFilesInDirectory->currentIndex()) + "\"";
    }
    else {
        commandeQString = "cd " + path + " && git commit -am \"" + ui->lineEditCommitMessage->text() + "\"";
    }
    system(commandeQString.toStdString().c_str());
}

void MainWindow::on_pushButtonGitPush_clicked()
{
    QString commandeQString = "cd " + path + " && git push -u origin main";
    system(commandeQString.toStdString().c_str());
}


void MainWindow::on_lineEditCommitMessage_textChanged(const QString &arg1)
{
    ui->lineEditCommitMessage->text().isEmpty() ? ui->comboBoxFilesInDirectory->setEnabled(true) : ui->comboBoxFilesInDirectory->setEnabled(false);
}


void MainWindow::on_pushButtonGitBranch_clicked()
{
    QString commandeQString = "cd " + path + " && git branch -M main";
    system(commandeQString.toStdString().c_str());
}


void MainWindow::on_pushButtonGitPull_clicked()
{
    QString commandeQString = "cd " + path + " && git pull";
    system(commandeQString.toStdString().c_str());
}


void MainWindow::on_pushButtonGitFetch_clicked()
{
    QString commandeQString = "cd " + path + " && git fetch -a";
    system(commandeQString.toStdString().c_str());
}


void MainWindow::on_pushButtonGitReset_clicked()
{
    QString commandeQString = "cd " + path + " && git reset .";
    system(commandeQString.toStdString().c_str());
}


void MainWindow::on_pushButtonGitResetHard_clicked()
{
    QString commandeQString = "cd " + path + " && git reset --hard .";
    system(commandeQString.toStdString().c_str());
}


void MainWindow::on_pushButtonGitRemote_clicked()
{
    QString commandeQString = "cd " + path + " && git remote add origin " + ui->lineEditRemoteUrl->text();
    system(commandeQString.toStdString().c_str());
}


void MainWindow::on_pushButtonGitCheckout_clicked()
{
    QString commandeQString = "cd " + path + " && git checkout " + ui->lineEditBrancheCheckout->text();
    system(commandeQString.toStdString().c_str());
}


void MainWindow::on_pushButtonGitCheckoutTrack_clicked()
{
    QString commandeQString = "cd " + path + " && git checkout " + ui->lineEditBrancheCheckout->text() + " --track";
    system(commandeQString.toStdString().c_str());
}


void MainWindow::on_actionConfigure_triggered()
{
    GitConfig gc;
    gc.exec();
}


void MainWindow::on_actionExit_triggered()
{
    close();
}


void MainWindow::on_pushButtonGitStatus_clicked()
{
    QString commandeQString = "cd " + path + " && git status";
    std::string str = exec(commandeQString.toStdString().c_str());
    std::ofstream output;

    QString pathToBufferText = path;
    pathToBufferText.append("/log.txt");

    output.open(pathToBufferText.toStdString(), std::ios_base::app);

    if (output.is_open())
        output << exec("echo Commande git status le %date% a %time% :") << "\n" << str << "\n\n";

    output.close();

    ui->textEditDebug->clear();
    ui->textEditDebug->append(QString::fromStdString(str));
}


void MainWindow::on_pushButtonGitDiff_clicked()
{
    QString commandeQString = "cd " + path + " && git diff";
    std::string str = exec(commandeQString.toStdString().c_str());
    std::ofstream output;

    QString pathToBufferText = path;
    pathToBufferText.append("/log.txt");

    output.open(pathToBufferText.toStdString(), std::ios_base::app);

    if (output.is_open())
        output << exec("echo Commande git diff le %date% a %time% :") << "\n" << str << "\n\n";

    output.close();

    ui->textEditDebug->clear();
    ui->textEditDebug->append(QString::fromStdString(str));
}


void MainWindow::on_pushButtonGitAdd_clicked()
{
    QString commandeQString = "cd " + path + " && git add .";
    system(commandeQString.toStdString().c_str());
}

