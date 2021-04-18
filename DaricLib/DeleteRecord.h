#ifndef DELETERECORD_H
#define DELETERECORD_H

class MySqlTableModel2;
class TableView;


class DeleteRecord
{
public:
    DeleteRecord(MySqlTableModel2* tableModel, TableView* tableView);

private:
    MySqlTableModel2* m_tableModel = nullptr;
    TableView* m_tableView = nullptr;
};

#endif // DELETERECORD_H
