#include "attrdlg.h"
#include "mainwindow.h"
#include "ui_attrdlg.h"

AttrDlg::AttrDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttrDlg)
{
    ui->setupUi(this);
    ui->Deadline->setText(tr("10"));
    ui->InitialPeople->setText(tr("50"));
    ui->WaitingTime->setText(tr("1.2"));
    ui->speed->setText(tr("2.5"));
    ui->cap->setText(tr("15"));
    ui->OptConsptn->setText(tr("2.8"));
    ui->DoorConsptn->setText(tr("0.75"));
    ui->InitialPeople->setFocus();
}

AttrDlg::~AttrDlg()
{
    delete ui;
}

void AttrDlg::on_Reset_clicked()
{
    ui->Deadline->setText(tr("10"));
    ui->InitialPeople->setText(tr("50"));
    ui->WaitingTime->setText(tr("1.2"));
    ui->speed->setText(tr("2.5"));
    ui->cap->setText(tr("15"));
    ui->OptConsptn->setText(tr("2.8"));
    ui->DoorConsptn->setText(tr("0.75"));
    ui->InitialPeople->setFocus();
}

void AttrDlg::on_Submit_clicked()
{

    //MainWindow.elevator


}
