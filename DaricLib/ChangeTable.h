#ifndef CHANGETABLE_H
#define CHANGETABLE_H

#include "Configuration.h"


#include <QObject>

class TableView;
class DatabaseManager;
class TableWidget;
class QComboBox;
class IdentityProxyModel;
class SortFilterProxyModel;
class CostEntryForm;
class TimeRangeForm;


class ChangeTable : public QObject
{
    Q_OBJECT
public:
    ChangeTable(QComboBox* comboBox,
                TableView* tableView,
                TableWidget* tableWidget,
                DatabaseManager* databaseManager,
                CostEntryForm* costEntryForm,
                TimeRangeForm* timeRangeForm,
                QObject* parent = nullptr);
    void slotSetTimeRangeOnFilterModel(QDate dateFrom, QDate dateTo);


private:
    QComboBox* m_comboBox;
    TableView* m_tableView;
    TableWidget* m_tableWidget;
    DatabaseManager* m_databaseManager;
    CostEntryForm* m_costEntryForm;
    TimeRangeForm* m_timeRangeForm;
    Configuration m_config;
    IdentityProxyModel* m_proxyModel;
    SortFilterProxyModel* m_proxyModel2;

private slots:
    void slotSetTableInModel(const QString& text);
    void slotSetCostEntryFormVisibility(const QString& text);

};

#endif // CHANGETABLE_H
