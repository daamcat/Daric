#include "mysqltablemodel.h"

#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

MySqlTableModel::MySqlTableModel(QObject * parent, QSqlDatabase db) :
    QSqlTableModel (parent,db)
{
    if (db.isOpen())
    {
        qDebug()<<" Database in constructor of MySqlTableModel is open!";
    }
    else
    {
        qDebug()<<" Database in constructor of MySqlTableModel is NOT open!";
    }

}

MySqlTableModel::~MySqlTableModel()
{
    qDebug()<<"MySqlTableModel destructor is called.";
}


QHash<int, QByteArray> MySqlTableModel::roleNames() const
{    
    // Trying to make a list of roles at initialization and passing it whenever roleNames() is called,
    // was not successful! Hence, we generate this list every time roleNames() is called.
    QHash<int, QByteArray> roles;
    // A "database record" or "record" is a row in a table in database. QSqlRecord represents a record.
    // A "field" is a column in database table.
    for (int i = 0; i < this->record().count(); i++)
    {
        QString columnHeader = this->record().fieldName(i) + "tor";

        roles.insert(Qt::UserRole + i + 1 , columnHeader.toUtf8());
        // UserRole + 1 for first column, UserRole + n for n-th column.
    }
    return roles;
}


QVariant MySqlTableModel::data ( const QModelIndex & index, int role ) const
{
    QVariant value;
    if (index.isValid())
    {
        if (role < Qt::ItemDataRole::UserRole)
        {
            value = QSqlQueryModel::data(index,role);
        }
        else
        {
            // Retrieve column index from role:
            int columnIndex = role - Qt::ItemDataRole::UserRole - 1;
            QModelIndex modelIndex = this->index(index.row(), columnIndex, QModelIndex());
            value = QSqlTableModel::data(modelIndex,Qt::ItemDataRole::DisplayRole);
        }
    }
    return value;
}

bool MySqlTableModel::setData(const QModelIndex &index, const QVariant &newValue, int role)
{
    //###################
    // Find roles
    //###################
    QHash<int, QByteArray> roles;
    roles.clear();
    for (int i = 0; i < this->record().count(); i++)
    {
        QString columnHeader = this->record().fieldName(i);
        if (columnHeader == "Price")
        {
            columnHeader = "price";
        }

        roles.insert(Qt::UserRole + i + 1 , columnHeader.toUtf8());
    }

    //###################
    // Find the input role between roles
    //###################
    bool indexIsValid = index.isValid();
    bool roleIsFound = false;
    QString foundRole = "";
    foreach(int i, roles.keys())
    {
        if (i == role)
        {
            roleIsFound = true;
            foundRole = QString::fromUtf8(roles.value(i));
            break;
        }
    }

    //###################
    // Set data
    //###################
    if (indexIsValid == true && roleIsFound)
    {
        int column = role - Qt::ItemDataRole::UserRole - 1;
        QModelIndex modelInd = this->index(index.row() , column);
        bool success = QSqlTableModel::setData(modelInd, newValue, Qt::ItemDataRole::EditRole);
        if (success)
        {
            if (this->database().isOpen())
            {
                if (submitAll() == false)
                {
                    qDebug() <<"The error is here: " << this->lastError().text();
                }
                else
                {
                    emit dataChanged(modelInd, modelInd, { role });
                }
            }
        }
        return success;
    }
    else
    {
        return false;
    }
}

Qt::ItemFlags MySqlTableModel::flags(const QModelIndex& index) const
{
    if (index.isValid() == false)
    {
        return Qt::ItemFlag::ItemIsEnabled;
    }

    return QAbstractItemModel::flags(index) | Qt::ItemFlag::ItemIsEditable;
}


