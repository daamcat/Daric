#include "DeleteRecord.h"
#include "databasemanager.h"
#include "TableView.h"

#include <QObject>


DeleteRecord::DeleteRecord(DatabaseManager* databaseManager, TableView* tableView) :
    m_databaseManager(databaseManager),
    m_tableView(tableView)
{
    QObject::connect(m_tableView, &TableView::signalDeleteRecord,
                     m_databaseManager, &DatabaseManager::slotRemoveRecord);

}
