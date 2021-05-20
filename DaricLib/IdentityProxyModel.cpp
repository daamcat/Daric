#include "IdentityProxyModel.h"
#include "MySqlTableModel2.h"

#include <QDateTime>
#include <QDate>

IdentityProxyModel::IdentityProxyModel(QVector<Field> tableProperties,
                                       QObject* parent) :
    QIdentityProxyModel(parent),
    m_tableProperties(tableProperties)
{




}

IdentityProxyModel::~IdentityProxyModel()
{

}

QVariant IdentityProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::ItemDataRole::DisplayRole)
    {
        if (orientation == Qt::Orientation::Vertical)
        {
            return QString("Row ") + QString::number(section);
        }
        else if (orientation == Qt::Orientation::Horizontal)
        {
            // At the moment we have an unfixed bug: When the table is changed by the user, the model is updated
            // and headerData, here, tries to update the view. The model is new, but m_tableProperties still
            // belongs to the old model. Hence, it can be the case that the new table has 5 columns, but m_tableProperties
            // has still 3 elements (related to the old table model). That's why we first control the sizes in here.
            // But ideally, we don't want the view to update as long as the model and properties both are not updated.
            if (section < m_tableProperties.size())
            {
                Field props = m_tableProperties.at(section);
                return QVariant(props.fieldHeaderViewName);
            }
        }
    }
    return QVariant();
}

QVariant IdentityProxyModel::data(const QModelIndex &index, int role) const
{
    Field props = m_tableProperties.at(index.column());
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
