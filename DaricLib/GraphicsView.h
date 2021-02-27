#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QVXYModelMapper>
#include "Chart.h"
#include "TableModel.h"

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = nullptr);
    void setTableModel(TableModel* model);





private:
    void resizeEvent(QResizeEvent *event);
    QChart* m_chart = nullptr;
    TableModel* m_model = nullptr;
    QVXYModelMapper m_modelMapper;
};

#endif // GRAPHICSVIEW_H
