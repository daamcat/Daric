#ifndef EDITRECORD_H
#define EDITRECORD_H

class MySqlTableModel2;
class TableView;
class TableWidget;
class PushButtonRecordEdit;

#include <QObject>

class EditRecord : public QObject
{
    Q_OBJECT
public:
    EditRecord(MySqlTableModel2* tableModel,
               TableView* tableView,
               TableWidget* tableWidget,
               PushButtonRecordEdit* pushButton);

private slots:
    void slotEditRecordTriggered(int row);
    void slotEditRecordInModel();

private:
    MySqlTableModel2* m_tableModel = nullptr;
    TableView* m_tableView = nullptr;
    TableWidget* m_tableWidget = nullptr;
    PushButtonRecordEdit* m_pushButton = nullptr;

};

#endif // EDITRECORD_H
