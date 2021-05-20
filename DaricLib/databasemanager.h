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
    void changeTable(const QString &tableName);
    MySqlTableModel2* getTableModel();
    MySqlTableModel2* getCurrentTableModel();

    QMap<QString,Field> getTableProperties();
    QVector<Field> getTablePropertiesVector();
    static QMap<int,QString> getFieldsFromForeignKeyTable(const QString& databaseName, const QString& tableName);

signals:
    void signalTableChanged(QStringList headers);



private:
    void setDatabaseTableInModel(const QString &databaseTableName);
    void readTablePropertiesFromDatabase(const QString &tableName);
    void readTablePropertiesFromDatabaseDeprecated(const QString &tableName);


    QString m_databaseName;
    QStringList m_tableNames;
    QString m_selectedTableName;
    MySqlTableModel2* m_tableModel;

    QMap<QString,Field> m_tableProperties;
    QVector<Field> m_tablePropertiesVector;
    Configuration m_config;

};

#endif // DATABASEMANAGER_H
