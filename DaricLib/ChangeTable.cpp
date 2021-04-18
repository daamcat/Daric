#include "ChangeTable.h"

#include "databasemanager.h"
#include "TableView.h"
#include "TableWidget.h"
#include "IdentityProxyModel.h"
#include "MySqlTableModel2.h"

#include <QTableWidgetItem>
#include <QComboBox>
#include <QSqlRecord>
#include <QSqlRelationalDelegate>
#include <QHeaderView>

ChangeTable::ChangeTable(QComboBox* comboBox,
                         TableView* tableView,
                         TableWidget* tableWidget,
                         DatabaseManager* databaseManager,
                         QObject* parent) :
  m_comboBox(comboBox),
  m_tableView(tableView),
  m_tableWidget(tableWidget),
  m_databaseManager(databaseManager)
{
    QStringList headerNames = m_databaseManager->getTableModel(m_comboBox->currentText())->getHeaderNames();
    m_tableWidget->slotSetHeaderNames(headerNames);

    this->slotSetTableInModel(m_comboBox->currentText());

    connect(m_databaseManager, &DatabaseManager::signalTableChanged, m_tableWidget, &TableWidget::slotSetHeaderNames);
    connect(m_comboBox, &QComboBox::currentTextChanged, this, &ChangeTable::slotSetTableInModel);
}

void ChangeTable::slotSetTableInModel(const QString& tableName)
{
    MySqlTableModel2* sqlTableModel= m_databaseManager->getTableModel(tableName);
    m_tableView->setModel(sqlTableModel);

    bool propertyTable = tableName.contains(m_config.tableNamePropertiesEnding);
    if (!propertyTable)
        // If this table is not a property table,...
    {
        QMap<QString,Field> tableProperties = m_databaseManager->getTableProperties();

        for (Field f : tableProperties.values())
        {
            if (f.foreignKey == 1)
                // If the field has foreign key,...
            {
                // We know that the name of the foreign key table is the same as the name of the field.
                const int currencyIndex = sqlTableModel->record().indexOf(f.fieldName);
                sqlTableModel->setRelation(currencyIndex,
                                           QSqlRelation(f.fieldName,
                                                        m_config.foreignKeyTableIdHeader,
                                                        f.fieldName));
                m_tableView->setItemDelegate(new QSqlRelationalDelegate(m_tableView));
            }
        }
        sqlTableModel->select(); // Needs to be called to apply relations.

        // Proxy model comes between "source model" and view:
        IdentityProxyModel* proxyModel = new IdentityProxyModel(tableProperties, this);
        proxyModel->setSourceModel(sqlTableModel);

        // Set the proxy model to view.
        m_tableView->setModel(proxyModel);

        /*
        // In proxy model, set the header view names:
        for (Field f : tableProperties.values())
        {
            const int currencyIndex = sqlTableModel->record().indexOf(f.fieldName);
            proxyModel->setHeaderData(currencyIndex,Qt::Orientation::Horizontal,
                                         f.fieldHeaderViewName);
        }
        */
    }
    else
        // If the table is property table,...
    {
        // In property tables there are no foreign keys and no proxy model.
        m_tableView->setModel(sqlTableModel);
        sqlTableModel->select(); // Needs to be called to apply relations.
    }
}

