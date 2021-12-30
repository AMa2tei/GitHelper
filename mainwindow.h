#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonValidatePath_clicked();

    void on_pushButtonAddComit_clicked();

    void on_pushButtonGitPush_clicked();

    void on_pushButtonRemoteAdd_clicked();

    void on_pushButtonGitStatus_clicked();

    void on_lineEditCommitMessage_textChanged(const QString &arg1);

    void on_pushButtonGitBranch_clicked();

private:
    Ui::MainWindow *ui;
    QString lien;
    QStringList liste;
    QString path;
};
#endif // MAINWINDOW_H
