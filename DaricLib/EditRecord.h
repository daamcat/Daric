#ifndef EDITRECORD_H
#define EDITRECORD_H

class DatabaseManager;
class TableView;
class TableWidget;
class PushButtonRecordEdit;

#include <QObject>

class EditRecord : public QObject
{
    Q_OBJECT
public:
    EditRecord(DatabaseManager* databaseManager,
               TableView* tableView,
               TableWidget* tableWidget,
               PushButtonRecordEdit* pushButton);

private slots:
    void slotEditRecordTriggered(int row);
    void slotEditRecordInModel();

private:
    DatabaseManager* m_databaseManager = nullptr;
    TableView* m_tableView = nullptr;
    TableWidget* m_tableWidget = nullptr;
    PushButtonRecordEdit* m_pushButton = nullptr;

};

#endif // EDITRECORD_H
