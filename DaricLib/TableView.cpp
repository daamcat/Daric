#include "TableView.h"

#include <QMenu>
#include <QAction>

TableView::TableView(QWidget* parent) : QTableView (parent)
{
    m_menu = new QMenu(this);

    m_actionEdit = new QAction(tr("Edit"));
    m_actionDelete = new QAction(tr("Delete"));
    m_actionMoveUp = new QAction(tr("Move up"));
    m_actionMoveDown = new QAction(tr("Move down"));

    m_menu->addAction(m_actionEdit);
    m_menu->addAction(m_actionDelete);
    connect(m_actionDelete,&QAction::triggered,this,&TableView::slotDeleteRecordTriggered);
    connect(m_actionEdit,&QAction::triggered,this,&TableView::slotEditRecordTriggered);

    setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
    connect(this,&TableView::customContextMenuRequested, this, &TableView::slotContextMenuRequested);



}


//void TableView::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
//{

//}

void TableView::slotDeleteRecordTriggered()
{
    QModelIndexList selectedRows = selectionModel()->selectedRows();
    // We assume that only one row can be selected...
    switch (selectedRows.size())
    {
    case 1:
        int rowNumber = selectedRows.front().row();
        emit signalDeleteRecord(rowNumber);
        break;
    }
}
void TableView::slotEditRecordTriggered()
{
    QModelIndexList selectedRows = selectionModel()->selectedRows();
    // We assume that only one row can be selected...
    switch (selectedRows.size())
    {
    case 1:
        int rowNumber = selectedRows.front().row();
        emit signalEditRecord(rowNumber);
        break;
    }
}

void TableView::slotContextMenuRequested(QPoint point)
{
    m_menu->popup(this->viewport()->mapToGlobal(point));
}
