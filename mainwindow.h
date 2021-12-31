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

//public slots:

private slots:
    void on_pushButtonValidatePath_clicked();

    void on_pushButtonAddComit_clicked();

    void on_pushButtonGitPush_clicked();

    void on_lineEditCommitMessage_textChanged(const QString &arg1);

    void on_pushButtonGitBranch_clicked();

    void on_pushButtonGitPull_clicked();

    void on_pushButtonGitFetch_clicked();

    void on_pushButtonGitReset_clicked();

    void on_pushButtonGitResetHard_clicked();

    void on_pushButtonGitRemote_clicked();

    void on_pushButtonGitCheckout_clicked();

    void on_pushButtonGitCheckoutTrack_clicked();

    void on_actionConfigure_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QString lien;
    QStringList liste;
    QString path;
};
#endif // MAINWINDOW_H
