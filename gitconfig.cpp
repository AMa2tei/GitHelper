#include "gitconfig.h"
#include "ui_gitconfig.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

GitConfig::GitConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GitConfig)
{
    ui->setupUi(this);
}

GitConfig::~GitConfig()
{
    delete ui;
}


void GitConfig::on_pushButtonSelectTextEditor_clicked()
{
    QString executableName = QFileDialog::getOpenFileName(this, tr("Open executable"),
                                                            ".",
                                                            tr("Executables (*.exe)"));
    ui->lineEditPathTextEditor->setText(executableName);
}


void GitConfig::on_buttonBox_accepted()
{
    if(!ui->lineEditName->text().isEmpty()            &&
       !ui->lineEditEmail->text().isEmpty()           &&
       !ui->lineEditPathTextEditor->text().isEmpty()  &&
       !ui->lineEditDefaultBranchName->text().isEmpty()) {
        QString commandeQStringName          = "git config --global user.name \""          + ui->lineEditName->text();
        QString commandeQStringEmail         = "git config --global user.email \""          + ui->lineEditEmail->text();
        QString commandeQStringEditor        = "git config --global core.editor \""        + ui->lineEditPathTextEditor->text();
        QString commandeQStringDefaultBranch = "git config --global init.defaultBranch \"" + ui->lineEditDefaultBranchName->text();
        system(commandeQStringName.toStdString().c_str());
        system(commandeQStringEmail.toStdString().c_str());
        system(commandeQStringEditor.toStdString().c_str());
        system(commandeQStringDefaultBranch.toStdString().c_str());
        close();
    } else {
        int ret = QMessageBox::warning(this, tr("Git config"),
                                       tr("Every line should have been edited."),
                                       QMessageBox::Ok);

    }
}


void GitConfig::on_buttonBox_rejected()
{
    close();
}

