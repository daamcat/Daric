#include "SortFilterProxyModel.h"

#include "Configuration.h"

SortFilterProxyModel::SortFilterProxyModel(QVector<Field> tableProperties, QObject* parent) :
    QSortFilterProxyModel(parent),
    m_tableProperties(tableProperties)
{
    Configuration config;
    // On which column the filter is going to be applied?
    for (int i = 0; i < m_tableProperties.size() ; i++)
    {
        if (m_tableProperties.at(i).fieldName == config.fieldNameShoppingDate)
        {
            m_columnToFilter = i;
            break;
        }
    }
}

bool SortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    // return true: display row. return false: filter row.
    // To see what this function does, simply return true and false and check the view.
    // return true;
    if (m_columnToFilter < 0 || !m_dateMin.isValid() || !m_dateMax.isValid())
        // If no filter is set,...
    {
        return true;
    }

    QModelIndex modelIndex = this->sourceModel()->index(sourceRow, m_columnToFilter, sourceParent);
    QDate shoppingDate = QDate::fromJulianDay(this->sourceModel()->data(modelIndex).toInt());
    if ( shoppingDate >= m_dateMin && shoppingDate <= m_dateMax)
    {
        return true;
    }
    return false;
}

void SortFilterProxyModel::setFilterDateMin(QDate dateMin)
{
    m_dateMin = dateMin;
    // Since the criterion has changed, the filtering must be updated:
    invalidateFilter();
}
void SortFilterProxyModel::setFilterDateMax(QDate dateMax)
{
    m_dateMax = dateMax;
    // Since the criterion has changed, the filtering must be updated:
    invalidateFilter();
}
void SortFilterProxyModel::setFilterDate(QDate dateMin , QDate dateMax)
{
    m_dateMin = dateMin;
    m_dateMax = dateMax;
    // Since the criterion has changed, the filtering must be updated:
    invalidateFilter();
}

//bool SortFilterProxyModel::lessThan(const QModelIndex& sourceLeft , const QModelIndex& sourceRight) const
//{

//}

QVariant SortFilterProxyModel::data(const QModelIndex &index, int role) const
{
    Field props = m_tableProperties.at(index.column());
    if (role == Qt::ItemDataRole::DisplayRole)
    {
        switch (props.displayType)
        {
            case DisplayType::DisplayTypeEnum::dateTime :
            {
                qint64 msecs = QSortFilterProxyModel::data(index,role).toLongLong();
                return QDateTime::fromMSecsSinceEpoch(msecs).toString(m_config.dateTimeDisplayFormat);
            }
            case DisplayType::DisplayTypeEnum::date :
            {
                qint64 days = QSortFilterProxyModel::data(index,role).toLongLong();
                return QDate::fromJulianDay(days).toString(m_config.dateDisplayFormat);
            }
        }
    }
    return QSortFilterProxyModel::data(index,role);
}

QVariant SortFilterProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
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
//    else if (Qt::ItemDataRole::ToolTipRole)
//    {
//        // QHeaderView documentation: Not all ItemDataRoles are covered in HeaderView.
//        // For example ToolTipRole is not covered. But FontRole or ForegroundRole are covered.
//    }
    return QSortFilterProxyModel::headerData(section,orientation,role);
}

