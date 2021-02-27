#include "TableManager.h"
#include "databasemanager.h"
#include "TableView.h"
#include "TableWidget.h"
#include "IdentityProxyModel.h"
#include "MySqlTableModel2.h"

#include <QTableWidgetItem>
#include <QComboBox>
#include <QSqlRecord>
#include <QSqlRelationalDelegate>


TableManager::TableManager(QComboBox* comboBox,
                           TableView* tableView,
                           TableWidget* tableWidget,
                           DatabaseManager* databaseManager,
                           QObject* parent) :
    m_comboBox(comboBox),
    m_tableView(tableView),
    m_tableWidget(tableWidget),
    m_databaseManager(databaseManager)
{

    QStringList headerNames = databaseManager->getHeaderNames();
    m_tableWidget->slotSetHeaderNames(headerNames);

    this->slotSetTableInModel(m_comboBox->currentText());

    connect(m_databaseManager, &DatabaseManager::signalTableChanged, m_tableWidget, &TableWidget::slotSetHeaderNames);
    connect(m_comboBox, &QComboBox::currentTextChanged, this, &TableManager::slotSetTableInModel);
}

void TableManager::slotSetTableInModel(const QString& tableName)
{
    MySqlTableModel2* sqlTableModel= m_databaseManager->getTableModel(tableName);

    bool propertyTable = tableName.contains(m_config.tableNamePropertiesEnding);
    if (!propertyTable)
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
                                                        m_config.foreignKeyTableNameHeader));
                m_tableView->setItemDelegate(new QSqlRelationalDelegate(m_tableView));
            }
        }
        sqlTableModel->select(); // Needs to be called to apply relations.

        // Proxy model comes between "source model" and view:
        IdentityProxyModel* proxyModel = new IdentityProxyModel(tableProperties, this);

        proxyModel->setSourceModel(sqlTableModel);
        m_tableView->setModel(proxyModel);
    }
    else
        // If the table is property table,...
    {
        // In property tables there are no foreign keys and no proxy model.
        m_tableView->setModel(sqlTableModel);
        sqlTableModel->select(); // Needs to be called to apply relations.
    }
}



