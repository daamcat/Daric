#include "CostEntryForm.h"
#include "ui_CostEntryForm.h"

#include <QDebug>

CostEntryForm::CostEntryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CostEntryForm)
{
    ui->setupUi(this);
}

CostEntryForm::~CostEntryForm()
{
    delete ui;
}

void CostEntryForm::mousePressEvent(QMouseEvent* event)
{
    qDebug()<<"Mouse button is pressed on NewRecordWidget!";
}

