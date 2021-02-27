#include "TableWidget.h"
#include <QHeaderView>
#include <QFont>

TableWidget::TableWidget(QWidget* parent) : QTableWidget(parent)
{
    setRowCount(1);

    //QHeaderView* headerView = horizontalHeader();
    //headerView->setDefaultAlignment(Qt::AlignmentFlag::AlignCenter);

    //QFont font = headerView->font();
    //font.setBold(true);
    //headerView->setFont(font);
    // Editing Palette can't necessarily change background:
    setStyleSheet("QHeaderView::section { background-color:rgb(200, 200,200) }");

    connect(this,&TableWidget::cellChanged, this, &TableWidget::slotCellChanged);
//    QStringList temp;
//    temp.push_back("fdfd");
//    temp.push_back("aaa");
//    temp.push_back("hghfd");
//    setColumnCount(temp.size());
//    setHorizontalHeaderLabels(temp);


}

QMap<int,QString> TableWidget::getRowValues()
{
    return m_values;
}

void TableWidget::slotSetHeaderNames(QStringList headerNames)
{
    m_headerNames = headerNames;
    m_values.clear();
    setColumnCount(headerNames.size());
    setHorizontalHeaderLabels(headerNames);
}

void TableWidget::slotCellChanged(int row, int column)
{
    QString value = item(row,column)->data(Qt::DisplayRole).toString();
    m_values[column] = value;
}

void TableWidget::setRowValues(QMap<QString,QString> values)
{
    for (int i = 0; i<columnCount(); i++)
    {
        QString headerName = horizontalHeaderItem(i)->text();
        if (values.contains(headerName))
        {
            QTableWidgetItem *widgetItem = new QTableWidgetItem(values.value(headerName));
            Qt::ItemFlags flags = widgetItem->flags();
            flags.setFlag(Qt::ItemIsEditable, false);
            widgetItem->setFlags(flags);
            setItem(0,i,widgetItem);
        }
    }
}
