#ifndef CHANGETABLE_H
#define CHANGETABLE_H

#include "Configuration.h"


#include <QObject>

class TableView;
class DatabaseManager;
class TableWidget;
class QComboBox;


class ChangeTable : public QObject
{
    Q_OBJECT
public:
    ChangeTable(QComboBox* comboBox,
                TableView* tableView,
                TableWidget* tableWidget,
                DatabaseManager* databaseManager,
                QObject* parent = nullptr);

private:
    QComboBox* m_comboBox;
    TableView* m_tableView;
    TableWidget* m_tableWidget;
    DatabaseManager* m_databaseManager;
    Configuration m_config;

private slots:
    void slotSetTableInModel(const QString& text);

};

#endif // CHANGETABLE_H
