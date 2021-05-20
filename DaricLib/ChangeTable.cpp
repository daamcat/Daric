#include "ChangeTable.h"

#include "DatabaseManager.h"
#include "TableView.h"
#include "TableWidget.h"
#include "IdentityProxyModel.h"
#include "MySqlTableModel2.h"
#include "CostEntryForm.h"

#include <QTableWidgetItem>
#include <QComboBox>
#include <QSqlRecord>
#include <QSqlRelationalDelegate>
#include <QHeaderView>

ChangeTable::ChangeTable(QComboBox* comboBox,
                         TableView* tableView,
                         TableWidget* tableWidget,
                         DatabaseManager* databaseManager,
                         CostEntryForm* costEntryForm,
                         QObject* parent) :
  m_comboBox(comboBox),
  m_tableView(tableView),
  m_tableWidget(tableWidget),
  m_databaseManager(databaseManager),
  m_costEntryForm(costEntryForm)
{
    m_databaseManager->changeTable(m_comboBox->currentText());
    QStringList headerNames = m_databaseManager->getTableModel()->getHeaderNames();
    m_tableWidget->slotSetHeaderNames(headerNames);

    this->slotSetTableInModel(m_comboBox->currentText());
    this->slotSetCostEntryFormVisibility(m_comboBox->currentText());

    connect(m_databaseManager, &DatabaseManager::signalTableChanged, m_tableWidget, &TableWidget::slotSetHeaderNames);
    connect(m_comboBox, &QComboBox::currentTextChanged, this, &ChangeTable::slotSetTableInModel);
    connect(m_comboBox, &QComboBox::currentTextChanged, this, &ChangeTable::slotSetCostEntryFormVisibility);

}

void ChangeTable::slotSetTableInModel(const QString& tableName)
{
    m_databaseManager->changeTable(tableName);
    MySqlTableModel2* sqlTableModel= m_databaseManager->getTableModel();

    bool propertyTable = tableName.contains(m_config.tableNamePropertiesEnding);
    if (!propertyTable)
        // If this table is not a property table,...
    {
        QVector<Field> tableProperties = m_databaseManager->getTablePropertiesVector();

        for (Field f : tableProperties)
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
        m_proxyModel = new IdentityProxyModel(tableProperties, this);
        m_proxyModel->setSourceModel(sqlTableModel);

        // Set the proxy model to view.
        m_tableView->setModel(m_proxyModel);
    }
    else
        // If the table is property table,...
    {
        // In property tables there are no foreign keys and no proxy model.
        m_tableView->setModel(sqlTableModel);
        sqlTableModel->select(); // Needs to be called to apply relations.
    }
}

void ChangeTable::slotSetCostEntryFormVisibility(const QString& text)
{
    m_costEntryForm->setVisible(text == m_config.TableNameCosts);
    m_costEntryForm->setSqlTableModel(m_databaseManager->getTableModel());
}

