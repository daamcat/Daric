#include "MySqlTableModel2.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlIndex>

// I very likely need to consider inheritting from class QSqlRelationalTableModel.

MySqlTableModel2::MySqlTableModel2(QObject *parent, QSqlDatabase db) : QSqlRelationalTableModel (parent,db)
{
    setEditStrategy(EditStrategy::OnManualSubmit);

}

QVariant MySqlTableModel2::headerData(int section, Qt::Orientation orientation, int role) const
{
    // In reimplementation of headerData() it is important to check the input role and to return proper header
    // only for display role. I still don't know why, but without this check, headerData will not be set properly.
    if (orientation == Qt::Orientation::Horizontal && role == Qt::ItemDataRole::DisplayRole)
    {
        // We don't really reimplement this function at the moment:
        return QSqlRelationalTableModel::headerData(section,orientation,role);
    }
    return QVariant();
}

bool MySqlTableModel2::select()
{
    // First we "select" the model and then we read header names and role names:
    bool ok = QSqlRelationalTableModel::select();

    m_headerNames.clear();
    m_roleNames.clear();
    QHash<int , QByteArray> roleNames = this->roleNames();
    for (int e : roleNames.keys())
    {
        m_roleNames.push_back(QString::number(e));
    }

    for (int i = 0; i<columnCount() ; i++)
    {
        qDebug()<<"Hader name for column "<< QString::number(i) << ": " << headerData(i, Qt::Orientation::Horizontal).toString();
        m_headerNames.push_back(headerData(i, Qt::Orientation::Horizontal).toString());
    }

    return ok;
}



QStringList MySqlTableModel2::getHeaderNames()
{
    return m_headerNames;
}

QStringList MySqlTableModel2::getRoleNames()
{
    return m_roleNames;
}

bool MySqlTableModel2::addRecord(const int& row, QMap<int , QString> values)
{
    if (values.empty())
    {
        return false;
    }

    QSqlRecord record = this->record();

    for (int i : values.keys())
    {
        record.setValue(i,values[i]);
    }

    // How to get primary key:
    const QSqlIndex index = primaryKey();
    QString fieldName = index.fieldName(0);
    //record.setGenerated(fieldName,true);
    //bool isAuto = index.field(fieldName).isAutoValue();

    bool success = insertRecord(row,record);
    submitAll();
    return success;
}

bool MySqlTableModel2::setRecord(const int& row, QMap<int , QString> values)
{
    // Why don't I use "QSqlRecord::replace()"???
    // Here uses "setRecord" for editing too: https://doc.qt.io/qt-5/sql-model.html
    if (values.empty())
    {
        return false;
    }
    QSqlRecord record = this->record();

    for (int i : values.keys())
    {
        record.setValue(i,values[i]);
    }

    bool success = QSqlRelationalTableModel::setRecord(row,record);
    submitAll();
    return success;
}

QSqlRecord MySqlTableModel2::getRecord(const int& row)
{
    if (row >= rowCount())
    {
        return QSqlRecord();
    }
    return record(row);
}

QMap<QString , QString> MySqlTableModel2::getRow(const int& row)
{
    QMap<QString , QString> values;
    if (row >= rowCount())
    {
        return values;
    }

    QSqlRecord record = this->record(row);
    for (QString headerName : getHeaderNames())
    {
        values[headerName] = record.value(headerName).toString();
    }
    return values;
}

bool MySqlTableModel2::slotRemoveRecord(int row)
{
    bool success = removeRow(row);
    submitAll();
    return success;
}




