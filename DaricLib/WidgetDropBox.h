#ifndef WIDGETDROPBOX_H
#define WIDGETDROPBOX_H

#include <QWidget>

namespace Ui {
class WidgetDropBox;
}

class WidgetDropBox : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetDropBox(QWidget *parent = nullptr);
    ~WidgetDropBox();

private:
    Ui::WidgetDropBox *ui;
};

#endif // WIDGETDROPBOX_H
