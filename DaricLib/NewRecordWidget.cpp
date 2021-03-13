#include "NewRecordWidget.h"
#include "ui_NewRecordWidget.h"

NewRecordWidget::NewRecordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewRecordWidget)
{
    ui->setupUi(this);
}

NewRecordWidget::~NewRecordWidget()
{
    delete ui;
}
