#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include "Configuration.h"


#include <QObject>

class TableView;
class DatabaseManager;
class TableWidget;
class QComboBox;


class TableManager : public QObject
{
    Q_OBJECT
public:
    TableManager(QComboBox* comboBox,
                 TableView* tableView,
                 TableWidget* tableWidget,
                 DatabaseManager* databaseManager,
                 QObject* parent = nullptr);

private slots:
    void slotSetTableInModel(const QString& text);



private:
    QComboBox* m_comboBox;
    TableView* m_tableView;
    TableWidget* m_tableWidget;
    DatabaseManager* m_databaseManager;
    Configuration m_config;

};

#endif // TABLEMANAGER_H
