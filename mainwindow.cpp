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
    //ui->groupBoxGitControl->setEnabled(true);
    //ui->pushButtonAddComit->setEnabled(true);
}

void MainWindow::on_pushButtonAddComit_clicked()
{
    QString commandeQString = "cd " + ui->lineEditPath->text() + " && git commit -am \"" + ui->lineEditCommitMessage->text() + "\"";
    system(commandeQString.toStdString().c_str());
    //ui->pushButtonRemoteAdd->setEnabled(true);
    //ui->lineEditRemoteUrl->setEnabled(true);
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
    //ui->pushButtonGitPush->setEnabled(true);
}


void MainWindow::on_pushButtonGitStatus_clicked()
{
    QString commandeQString = "cd " + ui->lineEditPath->text() + " && git status";
    system(commandeQString.toStdString().c_str());
}

