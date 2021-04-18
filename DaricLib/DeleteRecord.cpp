#include "DeleteRecord.h"
#include "MySqlTableModel2.h"
#include "TableView.h"

#include <QObject>


DeleteRecord::DeleteRecord(MySqlTableModel2* tableModel, TableView* tableView) :
    m_tableModel(tableModel),
    m_tableView(tableView)
{
    QObject::connect(m_tableView, &TableView::signalDeleteRecord,
                     m_tableModel, &MySqlTableModel2::slotRemoveRecord);

}
