#ifndef USERACTIVITYCONTROLLER_H
#define USERACTIVITYCONTROLLER_H


class TableView;
class TableWidget;
class PushButtonRecordEdit;
class QComboBox;

class UserActivityController
{
public:
    UserActivityController(
            TableView* dataTable,
            TableWidget* editTable,
            PushButtonRecordEdit* pushButton,
            QComboBox* comboboxSelectTable);


private:


    TableView* m_dataTable;
    TableWidget* m_editTable;
    PushButtonRecordEdit* m_pushButton;
    QComboBox* m_comboboxSelectTable;
};

#endif // USERACTIVITYCONTROLLER_H
