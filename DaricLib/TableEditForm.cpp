#include "TableEditForm.h"
#include "ui_TableEditForm.h"



TableEditForm::TableEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableEditForm)
{
    ui->setupUi(this);
}

TableEditForm::~TableEditForm()
{
    delete ui;
}


PushButtonRecordEdit* TableEditForm::getPushButtonRecordEdit()
{
    return ui->pushButton;
}
TableWidget* TableEditForm::getTableWidget()
{
    return ui->tableWidget;
}
