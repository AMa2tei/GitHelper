#ifndef GITCONFIG_H
#define GITCONFIG_H

#include <QDialog>

namespace Ui {
class GitConfig;
}

class GitConfig : public QDialog
{
    Q_OBJECT

public:
    explicit GitConfig(QWidget *parent = nullptr);
    ~GitConfig();

private slots:
    void on_pushButtonSelectTextEditor_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::GitConfig *ui;
};

#endif // GITCONFIG_H
