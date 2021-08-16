#include "TimeRangeForm.h"
#include "ui_TimeRangeForm.h"

#include "DateEdit.h"

TimeRangeForm::TimeRangeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeRangeForm)
{
    ui->setupUi(this);
    connect(ui->dateEditFrom, &DateEdit::signalDateChanged, this, &TimeRangeForm::timeRangeChanged);
    connect(ui->dateEditTo, &DateEdit::signalDateChanged, this, &TimeRangeForm::timeRangeChanged);
}

TimeRangeForm::~TimeRangeForm()
{
    delete ui;
}
void TimeRangeForm::timeRangeChanged()
{
    QDate dateFrom = ui->dateEditFrom->date();
    QDate dateTo = ui->dateEditTo->date();
    emit signalTimeRangeChanged(dateFrom, dateTo);
}
