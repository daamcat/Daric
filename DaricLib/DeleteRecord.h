#ifndef DELETERECORD_H
#define DELETERECORD_H

class DatabaseManager;
class TableView;


class DeleteRecord
{
public:
    DeleteRecord(DatabaseManager* databaseManager, TableView* tableView);

private:
    DatabaseManager* m_databaseManager = nullptr;
    TableView* m_tableView = nullptr;
};

#endif // DELETERECORD_H
