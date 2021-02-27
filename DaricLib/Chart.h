#ifndef CHART_H
#define CHART_H

#include <QtCharts>
#include "TableModel.h"


class Chart : public QChart
{
public:
    Chart(const QVector<ItemInfo> &itemInfo, QObject *parent = nullptr);
};

#endif // CHART_H
