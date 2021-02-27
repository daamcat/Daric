#include "Chart.h"
#include <QLineSeries>

Chart::Chart(const QVector<ItemInfo> &itemInfo, QObject *parent)
{
    QLineSeries *series = new QLineSeries(this);

    for (ItemInfo item : itemInfo)
    {
        series->append(item.date.toJulianDay(),item.price);
    }

    addSeries(series);

    series->setName("My expenditure");
    createDefaultAxes();
    setAutoFillBackground(true);
    legend()->setAlignment(Qt::AlignBottom);
    setAnimationOptions(QChart::AllAnimations);

}
