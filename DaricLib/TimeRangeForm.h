#ifndef TIMERANGEFORM_H
#define TIMERANGEFORM_H

#include <QWidget>
#include <QDate>

namespace Ui {
class TimeRangeForm;
}

class TimeRangeForm : public QWidget
{
    Q_OBJECT

public:
    explicit TimeRangeForm(QWidget *parent = nullptr);
    ~TimeRangeForm();

signals:
    void signalTimeRangeChanged(QDate dateFrom, QDate dateTo);

private:
    void timeRangeChanged();

    Ui::TimeRangeForm *ui;
};

#endif // TIMERANGEFORM_H
