#ifndef ADDRECORD_H
#define ADDRECORD_H

class MySqlTableModel2;
class TableView;
class TableWidget;
class PushButtonRecordEdit;

#include <QObject>

class AddRecord : public QObject
{
    Q_OBJECT
public:
    AddRecord(MySqlTableModel2* sqlTableModel,
               TableView* tableView,
               TableWidget* tableWidget,
               PushButtonRecordEdit* pushButton);

private slots:
    void slotAddRecordInModel();

private:
    MySqlTableModel2* m_sqlTableModel = nullptr;
    TableView* m_tableView = nullptr;
    TableWidget* m_tableWidget = nullptr;
    PushButtonRecordEdit* m_pushButton = nullptr;


};

#endif // ADDRECORD_H
