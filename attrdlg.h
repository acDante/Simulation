#ifndef ATTRDLG_H
#define ATTRDLG_H

#include <QDialog>

namespace Ui {
class AttrDlg;
}

class AttrDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AttrDlg(QWidget *parent = 0);
    ~AttrDlg();

private slots:
    void on_Reset_clicked();

    void on_Submit_clicked();

private:
    Ui::AttrDlg *ui;
};

#endif // ATTRDLG_H
