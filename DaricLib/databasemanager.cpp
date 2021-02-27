#include "databasemanager.h"
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

DatabaseManager::DatabaseManager(const QString &databaseName)
{
    m_databaseConnectionDefault = QSqlDatabase::addDatabase("QSQLITE");
    m_databaseConnectionDefault.setDatabaseName(databaseName);
    if (m_databaseConnectionDefault.open() == false)
    {
        qDebug()<<"Connection to database failed.";
    }

    m_tableModel = new MySqlTableModel2(nullptr,m_databaseConnectionDefault);
    m_tableModel->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);

    m_tableNames = m_databaseConnectionDefault.tables(QSql::Tables);
    if (!m_tableNames.isEmpty())
    {
        setSelectedTableName(m_tableNames.first());
    }

    // Connection for property tables:
    m_databaseConnectionForPropertiesTables = QSqlDatabase::addDatabase("QSQLITE", "cnn2");
    m_databaseConnectionForPropertiesTables.setDatabaseName(databaseName);
    // We don't open this connection yet!
}

DatabaseManager::~DatabaseManager()
{
    qDebug()<<"DatabaseManager destructor is called.";
}

QString DatabaseManager::getSelectedTableName()
{
    return m_selectedTableName;
}
void DatabaseManager::setSelectedTableName(const QString &tableName)
{
    m_selectedTableName = tableName;
    m_tableModel->setTable(m_selectedTableName);
    m_tableModel->select();

    QHash<int , QByteArray> roleNames = m_tableModel->roleNames();
    m_headerNames.clear();
    for (int e : roleNames.keys())
    {
        m_roleNames.push_back(QString::number(e));
    }

    int nCols = m_tableModel->columnCount();
    m_roleNames.clear();
    for (int i = 0; i<nCols ; i++)
    {
        m_headerNames.push_back(m_tableModel->headerData(i, Qt::Orientation::Horizontal).toString());
    }

    emit signalTableChanged(m_headerNames);
}

QStringList DatabaseManager::getRoleNames()
{
    return m_roleNames;
}
QStringList DatabaseManager::getHeaderNames()
{
    return m_headerNames;
}

QStringList DatabaseManager::getTableNames()
{
    return m_tableNames;
}

MySqlTableModel2* DatabaseManager::getTableModel(const QString &tableName)
{
    setSelectedTableName(tableName);
    const QString propertyTableName = tableName + m_config.tableNamePropertiesEnding;
    if (m_tableNames.contains(propertyTableName))
    {
        readTablePropertiesFromDatabase(propertyTableName);
    }
    return m_tableModel;
}

MySqlTableModel2* DatabaseManager::getCurrentTableModel()
{
    return m_tableModel;
}


bool DatabaseManager::addRecord(const int& row, QMap<int , QString> values)
{
    if (!m_tableModel || values.empty())
    {
        return false;
    }

    QSqlRecord record = m_tableModel->record();

    for (int i : values.keys())
    {
        record.setValue(i,values[i]);
    }

    // How to get primary key:
    const QSqlIndex index = m_tableModel->primaryKey();
    QString fieldName = index.fieldName(0);
    //record.setGenerated(fieldName,true);
    //bool isAuto = index.field(fieldName).isAutoValue();

    bool success = m_tableModel->insertRecord(row,record);
    m_tableModel->submitAll();
    return success;
}

bool DatabaseManager::setRecord(const int& row, QMap<int , QString> values)
{
    // Why don't I use "QSqlRecord::replace()"???
    // Here uses "setRecord" for editing too: https://doc.qt.io/qt-5/sql-model.html
    if (!m_tableModel || values.empty())
    {
        return false;
    }
    QSqlRecord record = m_tableModel->record();

    for (int i : values.keys())
    {
        record.setValue(i,values[i]);
    }

    bool success = m_tableModel->setRecord(row,record);
    m_tableModel->submitAll();
    return success;
}

QSqlRecord DatabaseManager::getRecord(const int& row)
{
    if (row >= m_tableModel->rowCount())
    {
        return QSqlRecord();
    }
    return m_tableModel->record(row);
}

QMap<QString , QString> DatabaseManager::getRow(const int& row)
{
    QMap<QString , QString> values;
    if (row >= m_tableModel->rowCount())
    {
        return values;
    }

    QSqlRecord record = m_tableModel->record(row);
    for (QString headerName : m_headerNames)
    {
        values[headerName] = record.value(headerName).toString();
    }
    return values;
}

bool DatabaseManager::slotRemoveRecord(int row)
{
    if (!m_tableModel)
    {
        return false;
    }
    bool success = m_tableModel->removeRow(row);
    m_tableModel->submitAll();
    return success;
}

QMap<QString,Field> DatabaseManager::getTableProperties()
{
    return m_tableProperties;
}


void DatabaseManager::readTablePropertiesFromDatabase(const QString &tableName)
{
    m_tableProperties.clear(); // Initially!
    if (m_databaseConnectionForPropertiesTables.open() == false)
    {
        qDebug()<<"Connection to database failed.";
        return;
    }

    MySqlTableModel2 *tableModel = new MySqlTableModel2(nullptr,m_databaseConnectionForPropertiesTables);

    if (!tableModel)
    {
        qDebug()<<"Table model is null.";
        return;
    }
    if (!m_databaseConnectionForPropertiesTables.isValid())
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
    }

    m_databaseConnectionForPropertiesTables.close();
}
