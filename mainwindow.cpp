#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <iostream>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonValidatePath_clicked()
{
    QString lien = ui->lineEditRemoteUrl->text();
    QStringList liste = lien.split("/");
    path = ui->lineEditPath->text();
    QStringList listeNameProject = liste.at(4).split(".");
    if(QDir(path).isEmpty())
    {
        system(QString("cd " + path + " && echo \"# " + listeNameProject.at(0) + "\" >> README.md").toStdString().c_str());
    }
    QString commandeQString = "cd " + path + " && git init";
    system(commandeQString.toStdString().c_str());
    QDir directorie(path);
    ui->comboBoxFilesInDirectory->addItems(directorie.entryList(QDir::Files, QDir::Name));

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


void MainWindow::on_pushButtonGitStatus_clicked()
{
    QString commandeQString = "cd " + path + " && git status";
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

