#include "DatabaseManager.h"
#include "MySqlTableModel2.h"

#include <QSqlDatabase>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlIndex>
#include <QSqlField>

DatabaseManager::DatabaseManager(const QString &databaseName) :
    m_databaseName(databaseName)
{
    // We don't use a member variable for QSqlDatabase. Because:
    // Qt: "It is highly recommended that you do not keep a copy of the QSqlDatabase around as a member of a class,
    // as this will prevent the instance from being correctly cleaned up on shutdown."
    QSqlDatabase databaseConnectionDefault = QSqlDatabase::addDatabase("QSQLITE");
    databaseConnectionDefault.setDatabaseName(m_databaseName);
    if (databaseConnectionDefault.open() == false)
    {
        qDebug()<<"Connection to database failed.";
    }

    m_tableModel = new MySqlTableModel2(nullptr,databaseConnectionDefault);
    m_tableModel->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);

    m_tableNames = databaseConnectionDefault.tables(QSql::Tables);
    if (!m_tableNames.isEmpty())
    {
        setDatabaseTableInModel(m_tableNames.first());
    }
}

DatabaseManager::~DatabaseManager()
{
    qDebug()<<"DatabaseManager destructor is called.";
    //QSqlDatabase::database().close();
}

QString DatabaseManager::getSelectedTableName()
{
    return m_selectedTableName;
}
void DatabaseManager::setDatabaseTableInModel(const QString &databaseTableName)
{
    m_selectedTableName = databaseTableName;
    // Select to which database table the model must fit (the data in model doesn't get updated):
    m_tableModel->setTable(m_selectedTableName);
    // Update the data in model with respect to the data in given database table:
    m_tableModel->select();

    emit signalTableChanged(m_tableModel->getHeaderNames());
}


QStringList DatabaseManager::getTableNames()
{
    return m_tableNames;
}


MySqlTableModel2* DatabaseManager::getTableModel()
{
    return m_tableModel;
}
void DatabaseManager::changeTable(const QString &tableName)
{
    // First read table properties:
    const QString propertyTableName = tableName + m_config.tableNamePropertiesEnding;
    if (m_tableNames.contains(tableName + m_config.tableNamePropertiesEnding))
    {
        readTablePropertiesFromDatabase(propertyTableName);
    }

    // Now read table in model:
    setDatabaseTableInModel(tableName);
}

MySqlTableModel2* DatabaseManager::getCurrentTableModel()
{
    return m_tableModel;
}

QMap<QString,Field> DatabaseManager::getTableProperties()
{
    return m_tableProperties;
}
QVector<Field> DatabaseManager::getTablePropertiesVector()
{
    return m_tablePropertiesVector;
}

void DatabaseManager::readTablePropertiesFromDatabase(const QString &tableName)
{
    m_tableProperties.clear(); // Initially!
    m_tablePropertiesVector.clear();

    // Get the default connection to read property table:
    QSqlDatabase databaseConnection = QSqlDatabase::database();

    if (databaseConnection.open() == false)
    {
        qDebug()<<"Connection to database failed.";
        return;
    }

    const QString dmlStatement = "SELECT * FROM " + tableName; // Read the whole table.
    // Put the query inside a scope, so it gets destroyed outside it:
    {
        QSqlQuery query(dmlStatement, databaseConnection);
        query.setForwardOnly(true);
        // Execute the query:
        if (!query.exec())
        {
            qDebug()<<"Couldn't execute query. Error: " + query.lastError().text();
        }

        // Here we assume that we have read the whole table. In order to map the contents of the table into the vector,
        // we need to know the fields and their index in table. Hence, we create a vector in which, the index of each
        // element is equal to its index in table in database:
        QVector<QString> elements = Field::elements();
        QMap<QString,int> fieldMap;
        for (QString element : elements)
        {
            fieldMap[element] = query.record().indexOf(element);
        }

        while (query.next())
            // Navigating through valid records returned by query execution...
        {
            Field field;
            field.fieldName = query.value(fieldMap["fieldName"]).toString();
            field.fieldHeaderViewName = query.value(fieldMap["fieldHeaderViewName"]).toString();
            field.dataType = query.value(fieldMap["dataType"]).toString();
            field.properties = query.value(fieldMap["properties"]).toString();
            field.editable = query.value(fieldMap["editable"]).toInt();
            field.foreignKey = query.value(fieldMap["foreignKey"]).toInt();
            field.displayType = DisplayType::intToEnum(query.value(fieldMap["displayType"]).toInt());
            field.nullValid = query.value(fieldMap["nullValid"]).toInt();
            field.autoGenerated = query.value(fieldMap["autoGenerated"]).toInt();

            m_tableProperties[field.fieldName] = field;
            m_tablePropertiesVector.push_back(field);
        }
    }
}


void DatabaseManager::readTablePropertiesFromDatabaseDeprecated(const QString &tableName)
{
    m_tableProperties.clear(); // Initially!
    m_tablePropertiesVector.clear();

    // Get the default connection to read property table:
    QSqlDatabase databaseConnection = QSqlDatabase::database();

    if (databaseConnection.open() == false)
    {
        qDebug()<<"Connection to database failed.";
        return;
    }

    // This part of the code can be written without using TableModel too. We just need to read the whole table
    // with a SQL query.
    MySqlTableModel2 *tableModel = new MySqlTableModel2(nullptr,databaseConnection);

    if (!tableModel)
    {
        qDebug()<<"Table model is null.";
        return;
    }
    if (!databaseConnection.isValid())
    {
        qDebug()<<"Connection is not valid.";
        return;
    }
    tableModel->setTable(tableName);
    tableModel->select(); // Shouldn't be forgotten!!! "...to populate the model with data."
    int rowCount = tableModel->rowCount();

    QVector<QString> elements = Field::elements();
    for (int i = 0; i<rowCount; i++)
        // As many as the number of rows in table_properties,...
        // As many as the number of columns in table,...
    {
        Field field;
        QSqlRecord record = tableModel->record(i);
        field.fieldName = record.value(elements.at(0)).toString();
        field.fieldHeaderViewName = record.value(elements.at(1)).toString();
        field.dataType = record.value(elements.at(2)).toString();
        field.properties = record.value(elements.at(3)).toString();
        field.editable = record.value(elements.at(4)).toInt();
        field.foreignKey = record.value(elements.at(5)).toInt();
        field.displayType = DisplayType::intToEnum(record.value(elements.at(6)).toInt());
        field.nullValid = record.value(elements.at(7)).toInt();
        field.autoGenerated = record.value(elements.at(8)).toInt();

        m_tableProperties[field.fieldName] = field;
        m_tablePropertiesVector.push_back(field);
    }
}

QMap<int,QString> DatabaseManager::getFieldsFromForeignKeyTable(const QString& databaseName, const QString& tableName)
{
    QMap<int,QString> result;
    const QString connectionName = "cnn3";

    // We put the whole database connection and the query in a scope. We do this in order to be able to remove
    // the connection to database after reading the desired records. For more info, read QSqlDatabase::removeDatabase().
    {
        // From Qt: " You can have multiple connections to one database."
        // For whatever reason I am not able to specify connection name:
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE",connectionName);
        db.setDatabaseName(databaseName);

        if (!db.open())
        {
            qDebug()<<"Connection to database "<< databaseName <<" to access table " << tableName << " failed.";
            return result;
        }
        if (!db.isValid())
        {
            qDebug()<<"Connection to database "<< databaseName <<" to access table " << tableName << " is not valid.";
            return result;
        }
        // If we are here, database is open and valid.

        // We want to read two fields: "ID" and tableName. We separate them with comma:
        // (we already know that table name in our case is the same as field name):
        QString fieldName = tableName; // Just to clarify what we are doing in here!!!
        const QString dmlStatement = "SELECT ID, " + fieldName + " FROM " + tableName;
        QSqlQuery query(dmlStatement, db);
        // We are sure that we only will use .next() to navigate through the records. Therefore, setting navigation
        // to forward only improves performance and saves memory (Ref:Qt):
        query.setForwardOnly(true);

        // Execute the query:
        if (!query.exec())
        {
            qDebug()<<"Couldn't execute query. Error: " + query.lastError().text();
        }

        // If exec() is successful, the state of query is "active". Otherwiese "inactive".
        // exec() puts the query on an invalid record. But if we navigate the active query e.g. with next(),
        // we can sweep the valid records returned by the query:
        while (query.next())
            // Navigating through valid records returned by query execution...
        {
            result[query.value(0).toInt()] = query.value(1).toString();
        }

        db.close();
    }
    // Now both database connection and query are destroyed, because they are out of scope (Ref: Qt)

    QSqlDatabase::removeDatabase(connectionName);
    return result;
}
