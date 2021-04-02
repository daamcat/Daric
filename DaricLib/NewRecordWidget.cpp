#include "NewRecordWidget.h"
#include "ui_NewRecordWidget.h"

#include <QDebug>

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

void NewRecordWidget::mousePressEvent(QMouseEvent* event)
{
    qDebug()<<"Mouse button is pressed on NewRecordWidget!";
}

