#ifndef DATEEDIT_H
#define DATEEDIT_H


#include <QDateEdit>

class QCalendarWidget;


class DateEdit : public QDateEdit
{
    Q_OBJECT
public:
    DateEdit(QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject* object, QEvent* event) override;

private:
    QCalendarWidget* m_calendarWidget;

private slots:
    void slotSetDate(const QDate& date);
};

#endif // DATEEDIT_H
