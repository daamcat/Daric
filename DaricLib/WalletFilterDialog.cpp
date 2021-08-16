#include "WalletFilterDialog.h"
#include "ui_WalletFilterDialog.h"

#include <QDate>

WalletFilterDialog::WalletFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WalletFilterDialog)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate().addDays(-QDate::currentDate().day()+1));
}

WalletFilterDialog::~WalletFilterDialog()
{
    delete ui;
}
