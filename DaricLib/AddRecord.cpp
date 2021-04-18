#include "AddRecord.h"

#include "TableView.h"
#include "TableWidget.h"
#include "PushButtonRecordEdit.h"
#include "MySqlTableModel2.h"

#include <QSqlRecord>
#include <QModelIndexList>


AddRecord::AddRecord(MySqlTableModel2* sqlTableModel,
                       TableView* tableView,
                       TableWidget* tableWidget,
                       PushButtonRecordEdit* pushbutton) :
    m_sqlTableModel(sqlTableModel),
    m_tableView(tableView),
    m_tableWidget(tableWidget),
    m_pushButton(pushbutton)
{
    QObject::connect(m_pushButton, &PushButtonRecordEdit::signalConfirmInsert,
            this, &AddRecord::slotAddRecordInModel);


}


void AddRecord::slotAddRecordInModel()
{
    QMap<int,QString> values = m_tableWidget->getRowValues();
    QModelIndexList selectedRows = m_tableView->selectionModel()->selectedRows();

    // We currently assume that only one row can be selected.
    switch (selectedRows.size())
    {
    case 0:
        m_sqlTableModel->addRecord(-1,values); // -1: Add record to the end of model.
        m_tableWidget->clearContents();
        break;
    case 1:
        QMap<int,QString> values = m_tableWidget->getRowValues();
        int rowNumber = selectedRows.front().row();
        m_sqlTableModel->addRecord(rowNumber,values);
        m_tableWidget->clearContents();
        break;
    }
}
