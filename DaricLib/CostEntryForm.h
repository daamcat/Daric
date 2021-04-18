#ifndef COSTENTRYFORM_H
#define COSTENTRYFORM_H

#include <QWidget>

namespace Ui {
class CostEntryForm;
}

class CostEntryForm : public QWidget
{
    Q_OBJECT

public:
    explicit CostEntryForm(QWidget *parent = nullptr);
    ~CostEntryForm();

private:
    Ui::CostEntryForm *ui;

protected:
    void mousePressEvent(QMouseEvent* event) override;

};

#endif // COSTENTRYFORM_H
