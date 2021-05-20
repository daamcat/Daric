#ifndef CHANGETABLE_H
#define CHANGETABLE_H

#include "Configuration.h"


#include <QObject>

class TableView;
class DatabaseManager;
class TableWidget;
class QComboBox;
class IdentityProxyModel;
class CostEntryForm;


class ChangeTable : public QObject
{
    Q_OBJECT
public:
    ChangeTable(QComboBox* comboBox,
                TableView* tableView,
                TableWidget* tableWidget,
                DatabaseManager* databaseManager,
                CostEntryForm* costEntryForm,
                QObject* parent = nullptr);

private:
    QComboBox* m_comboBox;
    TableView* m_tableView;
    TableWidget* m_tableWidget;
    DatabaseManager* m_databaseManager;
    CostEntryForm* m_costEntryForm;
    Configuration m_config;
    IdentityProxyModel* m_proxyModel;

private slots:
    void slotSetTableInModel(const QString& text);
    void slotSetCostEntryFormVisibility(const QString& text);

};

#endif // CHANGETABLE_H
