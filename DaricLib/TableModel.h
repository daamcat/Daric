#ifndef TABLEMODELL_H
#define TABLEMODELL_H

#include <QAbstractTableModel>
#include <QDate>

enum class Tags
{
    Food,
    Leisure,
    Travel
};


struct ItemInfo
{
    QString description;
    double price;
    QDate date;
    QString tag;
};

enum class Columns
{
    Description = 0,
    Price = 1,
    Date = 2,
    Tag = 3
};

class TableModel : public QAbstractTableModel
{
public:
    TableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::ItemDataRole::DisplayRole) const;
    //Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    QVector<ItemInfo> getModel();

private:
    QVector<ItemInfo> m_model;

    QMap<Tags, QString> m_mapTags;
    QMap<Columns, QString> m_mapColumns;

};

#endif // TABLEMODELL_H
