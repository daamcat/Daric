#include "TableModel.h"

TableModel::TableModel(QObject *parent)
{
    m_mapTags.insert(Tags::Food,"#Food");
    m_mapTags.insert(Tags::Leisure, "#Leisure");
    m_mapTags.insert(Tags::Travel, "#Travel");

    m_mapColumns.insert(Columns::Description, "Description");
    m_mapColumns.insert(Columns::Price, "Price");
    m_mapColumns.insert(Columns::Tag, "Tag");


    ItemInfo info;
    info.description = "Cheese";
    info.date = QDate(2020,7,20);
    info.price = 5.23;
    info.tag = m_mapTags.value(Tags::Food);
    m_model.push_back(info);

    info.description = "Beer in bar";
    info.date = QDate(2020,8,20);
    info.price = 23.70;
    info.tag = m_mapTags.value(Tags::Leisure);
    m_model.push_back(info);

    info.description = "Bordeaux";
    info.date = QDate(2020,9,20);
    info.price = 400;
    info.tag = m_mapTags.value(Tags::Travel);
    m_model.push_back(info);
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::ItemDataRole::DisplayRole)
    {
        return QVariant();
    }
    if (index.row()<m_model.size())
    {
        switch (static_cast<Columns>(index.column()))
        {
        case Columns::Description:
            return m_model.at(index.row()).description;
        case Columns::Price:
            return m_model.at(index.row()).price;
        case Columns::Tag:
            return m_model.at(index.row()).tag;
        case Columns::Date:
            //return m_model.at(index.row()).date.toString(Qt::DateFormat::ISODate);
            return m_model.at(index.row()).date;
        default:
            return QVariant();
        }
    }
    return QVariant();
}
int TableModel::rowCount(const QModelIndex &parent) const
{
    return m_model.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::ItemDataRole::DisplayRole)
    {
        if (orientation == Qt::Orientation::Vertical)
        {
            return QString("Row ") + QString::number(section);
        }
        else if (orientation == Qt::Orientation::Horizontal)
        {
            switch (static_cast<Columns>(section))
            {
            case Columns::Description:
                return QVariant("Description");
            case Columns::Price:
                return QVariant("Price");
            case Columns::Tag:
                return QVariant("Tag");
            case Columns::Date:
                return QVariant("Date");
            default:
                return QVariant();
            }
        }
    }
    return QVariant();
}

QVector<ItemInfo> TableModel::getModel()
{
    return m_model;
}
