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
    if(QDir(ui->lineEditPath->text()).isEmpty())
    {
        system(QString("cd " + ui->lineEditPath->text() + " && echo \"# Title\" >> README.md").toStdString().c_str());
    }
    QString commandeQString = "cd " + ui->lineEditPath->text() + " && git init";
    system(commandeQString.toStdString().c_str());
    QDir directorie(ui->lineEditPath->text());
    ui->comboBoxFilesInDirectory->addItems(directorie.entryList(QDir::NoFilter, QDir::Name));
}

void MainWindow::on_pushButtonAddComit_clicked()
{
    QString commandeQString;
    if(ui->lineEditCommitMessage->text().isEmpty()) {
        commandeQString = "cd " + ui->lineEditPath->text() + " && git init && git commit -am \"Updated " + ui->comboBoxFilesInDirectory->itemText(ui->comboBoxFilesInDirectory->currentIndex()) + "\"" +
                " && git branch -M main && git push -u origin main";
    }
    else {
        commandeQString = "cd " + ui->lineEditPath->text() + " && git init && git commit -am \"" + ui->lineEditCommitMessage->text() + "\"" +
                " && git branch -M main && git push -u origin main";
    }
    system(commandeQString.toStdString().c_str());
}

void MainWindow::on_pushButtonGitPush_clicked()
{
    QString commandeQString = "cd " + ui->lineEditPath->text() + " && git push -u origin main";
    system(commandeQString.toStdString().c_str());
}


void MainWindow::on_pushButtonRemoteAdd_clicked()
{
    QString commandeQString = "cd " + ui->lineEditPath->text() + " && git remote add origin " + ui->lineEditRemoteUrl->text();
    system(commandeQString.toStdString().c_str());
}


void MainWindow::on_pushButtonGitStatus_clicked()
{
    QString commandeQString = "cd " + ui->lineEditPath->text() + " && git status";
    system(commandeQString.toStdString().c_str());
}

