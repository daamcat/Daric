#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QDate>

#include "CreateSqliteDatabase.h"
#include "Configuration.h"


class SortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    SortFilterProxyModel(QVector<Field> tableProperties, QObject* parent = nullptr);

    void setFilterDateMin(QDate dateMin);
    void setFilterDateMax(QDate dateMax);
    void setFilterDate(QDate dateMin , QDate dateMax);

    // We reimplement QAbstractItemModel::data():
    QVariant data(const QModelIndex &proxyIndex, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;


protected:

    // "Custom filtering behavior can be achieved by reimplementing filterAcceptsRow() and
    // filterAcceptsColumn() functions." (Ref: Qt doc)
    // Reimplementing filterAcceptsRow() is the first step in programming a filter for model rows.
    // If filterAcceptsRow() returns true, the row will be included in proxy model and will be displayed
    // in view. If filterAcceptsRow() returns false, the row will not be included in model.
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

    // We also need to think of how the conditions are checked. There must be a comparison in values.
    // If we are dealing with basic types (int, double, QDate,...) we don't need to reimplement lessThan().
    // But for other types, we need to implement our means of "comparison" in reimplementation of lessThan():
    // bool lessThan(const QModelIndex& sourceLeft , const QModelIndex& sourceRight) const override;




private:

    QVector<Field> m_tableProperties;
    QDate m_dateMin = QDate(0,0,0); // Invalid date
    QDate m_dateMax = QDate(0,0,0); // Invalid date

    int m_columnToFilter = -1; // Initially invalid.

    Configuration m_config;
};

#endif // SORTFILTERPROXYMODEL_H
