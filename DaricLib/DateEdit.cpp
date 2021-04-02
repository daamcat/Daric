#include "DateEdit.h"

#include <QDate>
#include <QDebug>
#include <QMouseEvent>
#include <QLineEdit>
#include <QCalendarWidget>


DateEdit::DateEdit(QWidget* parent) : QDateEdit (parent)
{
    this->setDate(QDate::currentDate());
    this->setButtonSymbols(DateEdit::NoButtons);

    // Install an eventFilter on lineEdit of this widget. The aim is to capture all events coming to this lineEdit:
    this->lineEdit()->installEventFilter(this);

    m_calendarWidget = new QCalendarWidget();
    m_calendarWidget->setWindowModality(Qt::WindowModality::ApplicationModal);
    m_calendarWidget->hide();

    connect(m_calendarWidget,&QCalendarWidget::activated,this,&DateEdit::slotSetDate);
}

bool DateEdit::eventFilter(QObject* object, QEvent *event)
{
    if (object == this->lineEdit())
    {
        if (event->type() == QMouseEvent::MouseButtonRelease)
        {
            qDebug()<<"Mouse button is pressed in DateEdit!";
            m_calendarWidget->setSelectedDate(this->date());
            m_calendarWidget->show();
            return true;
        }
    }
    return QObject::eventFilter(object,event);
}


void DateEdit::slotSetDate(const QDate& date)
{
    this->setDate(date);
}
