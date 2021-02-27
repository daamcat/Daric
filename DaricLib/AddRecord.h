#ifndef ADDRECORD_H
#define ADDRECORD_H

class DatabaseManager;
class TableView;
class TableWidget;
class PushButtonRecordEdit;

#include <QObject>

class AddRecord : public QObject
{
    Q_OBJECT
public:
    AddRecord(DatabaseManager* databaseManager,
               TableView* tableView,
               TableWidget* tableWidget,
               PushButtonRecordEdit* pushButton);

private slots:
    void slotAddRecordInModel();

private:
    DatabaseManager* m_databaseManager = nullptr;
    TableView* m_tableView = nullptr;
    TableWidget* m_tableWidget = nullptr;
    PushButtonRecordEdit* m_pushButton = nullptr;


};

#endif // ADDRECORD_H
