#include "EditRecord.h"

#include "databasemanager.h"
#include "TableView.h"
#include "TableWidget.h"
#include "PushButtonRecordEdit.h"

#include <QSqlRecord>
#include <QModelIndexList>


EditRecord::EditRecord(DatabaseManager* databaseManager,
                       TableView* tableView,
                       TableWidget* tableWidget,
                       PushButtonRecordEdit* pushbutton) :
    m_databaseManager(databaseManager),
    m_tableView(tableView),
    m_tableWidget(tableWidget),
    m_pushButton(pushbutton)
{
    QObject::connect(m_tableView, &TableView::signalEditRecord,
            this, &EditRecord::slotEditRecordTriggered);
    QObject::connect(m_pushButton, &PushButtonRecordEdit::signalConfirmEdit,
            this, &EditRecord::slotEditRecordInModel);
}

void EditRecord::slotEditRecordTriggered(int row)
{
    QMap<QString , QString> values = m_databaseManager->getRow(row);
    m_tableWidget->setRowValues(values);
}

void EditRecord::slotEditRecordInModel()
{
    QMap<int,QString> values = m_tableWidget->getRowValues();
    QModelIndexList selectedRows = m_tableView->selectionModel()->selectedRows();

    // We currently assume that only one row can be selected.
    switch (selectedRows.size())
    {
    case 1:
        // Why don't I use "QSqlRecord::replace()"???
        QMap<int,QString> values = m_tableWidget->getRowValues();
        int rowNumber = selectedRows.front().row();
        m_databaseManager->setRecord(rowNumber,values);
        m_tableWidget->clearContents();
        break;
    }
}
