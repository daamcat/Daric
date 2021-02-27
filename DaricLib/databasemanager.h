#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H


#include <QSqlDatabase> // Forward declaration is impossible, since we call the class constructor with creating an object of the class.
#include <QStringList>
#include <QObject>
#include <QMap>

#include "CreateSqliteDatabase.h"
#include "Configuration.h"


class MySqlTableModel2;

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    DatabaseManager(const QString &databaseName);
    ~DatabaseManager();

    QString getSelectedTableName();
    QStringList getTableNames();
    MySqlTableModel2* getTableModel(const QString &tableName);
    MySqlTableModel2* getCurrentTableModel();
    QStringList getRoleNames();
    QStringList getHeaderNames();
    bool addRecord(const int& row, QMap<int , QString> values);
    bool setRecord(const int& row, QMap<int , QString> values);
    QSqlRecord getRecord(const int& row);
    QMap<QString , QString> getRow(const int& row);

    QMap<QString,Field> getTableProperties();

signals:
    void signalTableChanged(QStringList headers);

public slots:
    bool slotRemoveRecord(int row);


private:
    void setSelectedTableName(const QString &tableName);
    void readTablePropertiesFromDatabase(const QString &tableName);


    QSqlDatabase m_databaseConnectionDefault;
    QSqlDatabase m_databaseConnectionForPropertiesTables;
    QStringList m_tableNames;
    QString m_selectedTableName;
    MySqlTableModel2* m_tableModel;

    QStringList m_roleNames;
    QStringList m_headerNames;
    QMap<QString,Field> m_tableProperties;
    Configuration m_config;

};

#endif // DATABASEMANAGER_H
