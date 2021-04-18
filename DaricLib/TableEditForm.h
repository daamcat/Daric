#ifndef TABLEEDITFORM_H
#define TABLEEDITFORM_H

#include <QWidget>
#include "PushButtonRecordEdit.h"
#include "TableWidget.h"

namespace Ui {
class TableEditForm;
}

class TableEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit TableEditForm(QWidget *parent = nullptr);
    ~TableEditForm();

    PushButtonRecordEdit* getPushButtonRecordEdit();
    TableWidget* getTableWidget();

private:
    Ui::TableEditForm *ui;
};

#endif // TABLEEDITFORM_H
