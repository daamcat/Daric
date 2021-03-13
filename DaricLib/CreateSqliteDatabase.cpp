#include "CreateSqliteDatabase.h"
#include "Configuration.h"

#include <QDebug>
#include <QtSql>
#include <QFile>
#include <QDateTime>
#include <QRandomGenerator>
#include <QThread>
#include <QVectorIterator>

void createTable(const QString& tableName, const QVector<Field>& fields);
void addRecordsToForeignKeyTable(const QString& tableName, const QVector<Field>& fields, QVector<QString> values);
void addRecordsToPropertyTable(const QString& tableName, const QVector<Field>& fields, const QVector<Field>& valueFields);
void addRecordsToCostsTable(const QString& tableName, const QVector<Field>& fields, int nRecords);
QString getCreateTableQueryString(const QString& tableName, const QVector<Field>& fields);
QString getInsertRecordQueryString(const QString& tableName, const QVector<Field>& fields);

CreateSqliteDatabase::CreateSqliteDatabase()
{
    Configuration config;
    Field InsertionDateTime {"InsertionDateTime", "Insertion date-time" , "INTEGER", "NOT NULL PRIMARY KEY UNIQUE", 0 , 0 , DisplayType::DisplayTypeEnum::dateTime, 0, 1, config.visibilityLevelUser};
    m_tableCosts.push_back(InsertionDateTime);
    Field Description {"Description" , "Description", "TEXT", "", 1, 0, DisplayType::DisplayTypeEnum::text, 1, 0, config.visibilityLevelUser};
    m_tableCosts.push_back(Description);
    Field Price{"Price" , "Price", "REAL", "NOT NULL", 1, 0, DisplayType::DisplayTypeEnum::real, 0, 0, config.visibilityLevelUser};
    m_tableCosts.push_back(Price);
    Field ShoppingDate{"ShoppingDate" , "Shopping date", "INTEGER", "", 1, 0, DisplayType::DisplayTypeEnum::date, 1, 0, config.visibilityLevelUser};
    m_tableCosts.push_back(ShoppingDate);
    Field Withdrawal{"Withdrawal" , "Withdrawal", "REAL", "", 1, 0, DisplayType::DisplayTypeEnum::real, 0, 0, config.visibilityLevelUser};
    m_tableCosts.push_back(Withdrawal);
    Field Tag{"Tag" , "Tag", "INTEGER", "", 1, 1, DisplayType::DisplayTypeEnum::foreignKey, 1, 0, config.visibilityLevelUser};
    m_tableCosts.push_back(Tag);
    Field Currency{"Currency" , "Currency", "INTEGER", "", 1, 1, DisplayType::DisplayTypeEnum::foreignKey, 1, 0, config.visibilityLevelUser};
    m_tableCosts.push_back(Currency);
    Field LastEditDateTime{"LastEditDateTime" , "Last edit date-time", "INTEGER", "", 1, 0, DisplayType::DisplayTypeEnum::dateTime, 0, 1, config.visibilityLevelUser};
    m_tableCosts.push_back(LastEditDateTime);
    Field PaymentMean{"PaymentMean" , "Payment mean", "INTEGER", "", 1, 1, DisplayType::DisplayTypeEnum::foreignKey, 1, 0, config.visibilityLevelUser};
    m_tableCosts.push_back(PaymentMean);
    Field ShoppingSource{"ShoppingSource" , "Shopping source", "INTEGER", "", 1, 1, DisplayType::DisplayTypeEnum::foreignKey, 1, 0, config.visibilityLevelUser};
    m_tableCosts.push_back(ShoppingSource);

    Field ID {"ID" , "ID", "INTEGER", " INTEGER PRIMARY KEY AUTOINCREMENT", 0 , 0 , DisplayType::DisplayTypeEnum::integer, 0, 1, config.visibilityLevelUser};
    m_tableForeignKeys.push_back(ID);
    Field Name {"Name" , "Name", "TEXT", "NOT NULL UNIQUE", 1 , 0 , DisplayType::DisplayTypeEnum::text, 0, 0, config.visibilityLevelUser};
    m_tableForeignKeys.push_back(Name);

    m_tableForeignKeysCurrency.push_back(ID);
    m_tableForeignKeysCurrency.push_back(Name);
    Field ExchangeRateToEuro {"ExchangeRateToEuro" , "Exchange to Euro", "REAL", "", 1 , 0 , DisplayType::DisplayTypeEnum::real, 1, 0, config.visibilityLevelUser};
    m_tableForeignKeysCurrency.push_back(ExchangeRateToEuro);
    Field Symbol {"Symbol" , "Symbol of currency", "TEXT", "", 1 , 0 , DisplayType::DisplayTypeEnum::text, 1, 0, config.visibilityLevelUser};
    m_tableForeignKeysCurrency.push_back(Symbol);

    m_tableProperties.push_back(ID);
    Field fieldName {"fieldName" , "fieldName", "TEXT", "NOT NULL UNIQUE", 1 , 0 , DisplayType::DisplayTypeEnum::text, 0, 0, config.visibilityLevelUser};
    m_tableProperties.push_back(fieldName);
    Field fieldHeaderViewName {"fieldHeaderViewName" , "fieldHeaderViewName", "TEXT", "NOT NULL", 0 , 0 , DisplayType::DisplayTypeEnum::text, 0, 0, config.visibilityLevelUser};
    m_tableProperties.push_back(fieldHeaderViewName);
    Field dataType {"dataType" , "dataType", "TEXT", "NOT NULL", 0 , 0 , DisplayType::DisplayTypeEnum::text, 0, 0, config.visibilityLevelUser};
    m_tableProperties.push_back(dataType);
    Field properties {"properties" , "properties", "TEXT", "", 0 , 0 , DisplayType::DisplayTypeEnum::text, 0, 0, config.visibilityLevelUser};
    m_tableProperties.push_back(properties);
    Field editable {"editable" , "editable", "INTEGER", "NOT NULL", 0 , 0 , DisplayType::DisplayTypeEnum::text, 0, 0, config.visibilityLevelUser};
    m_tableProperties.push_back(editable);
    Field foreignKey {"foreignKey" , "foreignKey", "INTEGER", "NOT NULL", 0 , 0 , DisplayType::DisplayTypeEnum::text, 0, 0, config.visibilityLevelUser};
    m_tableProperties.push_back(foreignKey);
    Field displayType {"displayType" , "displayType", "INTEGER", "NOT NULL", 0 , 1 , DisplayType::DisplayTypeEnum::text, 0, 0, config.visibilityLevelUser};
    m_tableProperties.push_back(displayType);
    Field nullValid {"nullValid" , "nullValid", "INTEGER", "NOT NULL", 0 , 0 , DisplayType::DisplayTypeEnum::text, 0, 0, config.visibilityLevelUser};
    m_tableProperties.push_back(nullValid);
    Field autoGenerated {"autoGenerated" , "autoGenerated", "INTEGER", "NOT NULL", 0 , 0 , DisplayType::DisplayTypeEnum::text, 0, 0, config.visibilityLevelUser};
    m_tableProperties.push_back(autoGenerated);
    Field visibilityLevel {"visibilityLevel" , "visibilityLevel", "INTEGER", "NOT NULL", 0 , 0 , DisplayType::DisplayTypeEnum::text, 0, 0, config.visibilityLevelUser};
    m_tableProperties.push_back(visibilityLevel);

    //++++++++++++++++++
    // Create database
    //++++++++++++++++++
    QFile::remove("newDB.sqlite");
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("newDB.sqlite");

    if (!db.open())
    {
        qDebug()<<"Couldn't open database!";
    }
    else
    {
        qDebug()<<"Database opened successfully!";
    }

    //++++++++++++++++++
    // Create tables in database
    //++++++++++++++++++
    createTable(QString("Currency"), m_tableForeignKeysCurrency);
    createTable(QString("Tag"), m_tableForeignKeys);
    createTable(QString("PaymentMean"), m_tableForeignKeys);
    createTable(QString("ShoppingSource"), m_tableForeignKeys);
    createTable(QString("Costs"), m_tableCosts);
    createTable(QString("DisplayType"), m_tableForeignKeys);
    createTable(QString("DataType"), m_tableForeignKeys);

    //++++++++++++++++++
    // Create property tables in database
    //++++++++++++++++++
    createTable(QString("Currency_properties"), m_tableProperties);
    createTable(QString("Tag_properties"), m_tableProperties);
    createTable(QString("PaymentMean_properties"), m_tableProperties);
    createTable(QString("ShoppingSource_properties"), m_tableProperties);
    createTable(QString("Costs_properties"), m_tableProperties);
    createTable(QString("DisplayType_properties"), m_tableProperties);
    createTable(QString("DataType_properties"), m_tableProperties);

    //++++++++++++++++++
    // Add values to tables
    //++++++++++++++++++
    addRecordsToForeignKeyTable(QString("Currency"), m_tableForeignKeysCurrency, Currency::elements());
    addRecordsToForeignKeyTable(QString("Tag"), m_tableForeignKeys, Tag::elements());
    addRecordsToForeignKeyTable(QString("PaymentMean"), m_tableForeignKeys, PaymentMean::elements());
    addRecordsToForeignKeyTable(QString("ShoppingSource"), m_tableForeignKeys, ShoppingSource::elements());
    addRecordsToForeignKeyTable(QString("DisplayType"), m_tableForeignKeys, DisplayType::elements());
    addRecordsToForeignKeyTable(QString("DataType"), m_tableForeignKeys, DataType::elements());
    addRecordsToCostsTable(QString("Costs"), m_tableCosts, 5);

    //++++++++++++++++++
    // Add values to property tables
    //++++++++++++++++++
    addRecordsToPropertyTable(QString("Currency_properties"), m_tableProperties, m_tableForeignKeysCurrency);
    addRecordsToPropertyTable(QString("Tag_properties"), m_tableProperties, m_tableForeignKeys);
    addRecordsToPropertyTable(QString("PaymentMean_properties"), m_tableProperties, m_tableForeignKeys);
    addRecordsToPropertyTable(QString("ShoppingSource_properties"), m_tableProperties, m_tableForeignKeys);
    addRecordsToPropertyTable(QString("Costs_properties"), m_tableProperties, m_tableCosts);
    addRecordsToPropertyTable(QString("DisplayType_properties"), m_tableProperties, m_tableForeignKeys);
    addRecordsToPropertyTable(QString("DataType_properties"), m_tableProperties, m_tableForeignKeys);

    //++++++++++++++++++
    // Close and copy database
    //++++++++++++++++++
    db.close();
    QFile::remove(QString(SOURCE_DIR) + "/testData/newDB.sqlite");
    QFile::copy("newDB.sqlite", QString(SOURCE_DIR) + "/testData/newDB.sqlite");
}

void createTable(const QString& tableName, const QVector<Field>& table)
{
    QString query = getCreateTableQueryString(tableName,table);
    QSqlQuery qry;
    if (qry.prepare(query))
    {
        if (!qry.exec(query))
        {
            qDebug()<<"Couldn't create table " + tableName;
        }
        else
        {
            qDebug()<<"Table " + tableName + " created successfully!";
        }
    }
    else
    {
        qDebug()<<"Couldn't prepare query to table " + tableName + "!";
        qDebug()<<qry.lastError().text();
    }
}


void addRecordsToForeignKeyTable(const QString& tableName, const QVector<Field>& fields, QVector<QString> values)
{
    for (int i=0; i<values.size();i++)
    {
        QString query = getInsertRecordQueryString(tableName, fields);
        QSqlQuery qry;
        qry.prepare(query);
        qry.addBindValue(i);
        qry.addBindValue(values.at(i));

        // Insert empty string for possible remaining empty fields:
        if (fields.size() > 2)
        {
            for (int p = 3 ; p <= fields.size() ;p++)
            {
                qry.addBindValue(QVariant(QVariant::String));
            }
        };
        if (!qry.exec())
        {
            qDebug()<<"Couldn't add record to table " + tableName + "!";
            qDebug()<<qry.lastError().text();
        }
        else
        {
            qDebug()<<"Record added to table " + tableName + " successfully!";
        }
    }
}

void addRecordsToPropertyTable(const QString& tableName, const QVector<Field>& fields, const QVector<Field>& valueFields)
{
    for (int i = 0; i < valueFields.size(); i++)
        // As many as the number of fields in table
    {
        Field f = valueFields.at(i);
        QString query = getInsertRecordQueryString(tableName, fields);
        qDebug()<<query;
        QSqlQuery qry;
        qry.prepare(query);
        qry.addBindValue(i); //ID
        qry.addBindValue(f.fieldName); //Name
        qry.addBindValue(f.fieldHeaderViewName);
        qry.addBindValue(f.dataType); //DataType
        qry.addBindValue(f.properties); //Properties
        qry.addBindValue(f.editable); //Editable
        qry.addBindValue(f.foreignKey); //ForeignKey
        qry.addBindValue(DisplayType::enumToInt(f.displayType)); //DisplayType
        qry.addBindValue(f.nullValid); //NullValid
        qry.addBindValue(f.autoGenerated); //AutoGenerated
        qry.addBindValue(f.visibilityLevel); //AutoGenerated

        if (!qry.exec())
        {
            qDebug()<<"Couldn't add record " + f.fieldName + " to table " + tableName + "!";
            qDebug()<<qry.lastError().text();
        }
        else
        {
            qDebug()<<"Record " + f.fieldName + " added to table " + tableName + " successfully!";
        }
    }
}

QString getInsertRecordQueryString(const QString& tableName, const QVector<Field>& fields)
{
    QString query = "INSERT INTO " + tableName + " (";
    QString values = "VALUES (";
    for (int i = 0; i<fields.size();i++)
    {
        query += "\"" + fields.at(i).fieldName + "\"";
        if (i != fields.size() - 1)
        {
            query += ",";
            values += "?, ";
        }
        else
        {
            query += ")";
            values += "?);";
        }
    }

    query += values;
    return query;
}


QString getCreateTableQueryString(const QString& tableName, const QVector<Field>& fields)
{
    // There is also the possibility to say: CREATE TABLE IF NOT EXISTS ...
    QString query = "CREATE TABLE \"" + tableName + "\" (";

    for (int i = 0; i<fields.size();i++)
    {
        query += fields.at(i).fieldName + " " + fields.at(i).properties;
        if (i != fields.size() - 1)
        {
            query += ",";
        }
        else
        {
            query += ");";
        }
    }
    return query;
}

void addRecordsToCostsTable(const QString& tableName, const QVector<Field>& fields, int nRecords)
{
    for (int i=0;i<nRecords;i++)
        // As many as number of requested records,...
    {
        QThread::msleep(3); // To make sure insertion date-time remains unique.
        //"InsertionDateTime INTEGER NOT NULL UNIQUE,"
        qint64 nowDateTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
        //"Description TEXT,"
        QString description = "Item " + QString::number(i);
        //"Price REAL NOT NULL,"
        qreal price = QRandomGenerator::global()->bounded(73.44);
        //"ShoppingDate INTEGER,"
        qint64 nowDate = QDateTime::currentDateTime().date().toJulianDay();
        //"Withdrawal REAL,"
        qreal withdrawal = 0;
        //"Tag INTEGER,"
        qint64 tag = QRandomGenerator::global()->bounded(Tag::elements().size());
        //"Currency INTEGER,"
        qint64 currency = QRandomGenerator::global()->bounded(Currency::elements().size());
        //"LastEditDateTime INTEGER,"
        // We set it equal to insertion date-time.
        //"PaymentMean INTEGER,"
        qint64 paymentMean = QRandomGenerator::global()->bounded(PaymentMean::elements().size());
        //"ShoppingSource INTEGER);";
        qint64 shoppingSource = QRandomGenerator::global()->bounded(ShoppingSource::elements().size());

        QString query = getInsertRecordQueryString(tableName, fields);
        QSqlQuery qry;
        qry.prepare(query);
        qry.addBindValue(nowDateTime);
        qry.addBindValue(description);
        qry.addBindValue(price);
        qry.addBindValue(nowDate);
        qry.addBindValue(withdrawal);
        qry.addBindValue(tag);
        qry.addBindValue(currency);
        qry.addBindValue(nowDateTime);
        qry.addBindValue(paymentMean);
        qry.addBindValue(shoppingSource);

        if (!qry.exec())
        {
            qDebug()<<"Couldn't add record number " + QString::number(i) + " to table \"Costs\"!";
            qDebug()<<"Error: " + qry.lastError().text();
        }
        else
        {
            qDebug()<<"Record number " + QString::number(i) + "added to table \"Costs\" successfully!";
        }
    }
}
