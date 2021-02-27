#include "GraphicsView.h"

#include <QDateTimeAxis>
#include <QValueAxis>


GraphicsView::GraphicsView(QWidget* parent) : QGraphicsView (new QGraphicsScene, parent)
{
    m_chart = new QChart();
    scene()->addItem(m_chart);
    QLineSeries *series = new QLineSeries();
    series->append(200,40);
    series->append(400,20);
    series->setName("My expenditure");
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    if (scene() && m_chart->series().size()>0)
    {
        scene()->setSceneRect(QRect(QPoint(0,0), event->size()));
        m_chart->resize(event->size());
    }
    QGraphicsView::resizeEvent(event);
}
void GraphicsView::setTableModel(TableModel *model)
{
    m_chart->removeAllSeries();
    QVXYModelMapper* modelMapper = new QVXYModelMapper();
    m_model = model;
    modelMapper->setModel(model);

    modelMapper->setXColumn(2); // Date
    modelMapper->setYColumn(1); // Price
    QLineSeries* series = new QLineSeries();
    series->setName("Line 1");
    modelMapper->setSeries(series);
    m_chart->addSeries(series);

    QDateTimeAxis* axisX = new QDateTimeAxis();
    axisX->setTitleText("Date");
    m_chart->addAxis(axisX,Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Price");
    m_chart->addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisY);

    m_chart->setAutoFillBackground(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);
    m_chart->setAnimationOptions(QChart::AllAnimations);

}
