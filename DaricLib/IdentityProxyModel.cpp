#include "IdentityProxyModel.h"
#include "MySqlTableModel2.h"

#include <QDateTime>
#include <QDate>

IdentityProxyModel::IdentityProxyModel(QMap<QString,Field> tableProperties,
                                       QObject* parent) :
    QIdentityProxyModel(parent),
    m_tableProperties(tableProperties)
{




}

IdentityProxyModel::~IdentityProxyModel()
{

}

//QVariant IdentityProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    if (role == Qt::ItemDataRole::DisplayRole)
//    {
//        if (orientation == Qt::Orientation::Vertical)
//        {
//            return QString("Row ") + QString::number(section);
//        }
//        else if (orientation == Qt::Orientation::Horizontal)
//        {
//            return QVariant("Hala ye chizi");
//        }
//    }
//    return QVariant();
//}

QVariant IdentityProxyModel::data(const QModelIndex &index, int role) const
{

    QString headerName = this->sourceModel()->headerData(index.column(),
                                          Qt::Orientation::Horizontal,
                                          Qt::ItemDataRole::DisplayRole).toString();
    Field props = m_tableProperties.value(headerName);
    if (role == Qt::ItemDataRole::DisplayRole)
    {
        switch (props.displayType)
        {
        case DisplayType::DisplayTypeEnum::dateTime :
        {
            qint64 msecs = QIdentityProxyModel::data(index,role).toLongLong();
            return QDateTime::fromMSecsSinceEpoch(msecs).toString(m_config.dateTimeDisplayFormat);
        }
        case DisplayType::DisplayTypeEnum::date :
        {
            qint64 days = QIdentityProxyModel::data(index,role).toLongLong();
            return QDate::fromJulianDay(days).toString(m_config.dateDisplayFormat);
        }

        }

    }
    return QIdentityProxyModel::data(index,role);
}
