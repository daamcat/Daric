#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include "TableModel.h"

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene(const QVector<ItemInfo> &model, QObject *parent = nullptr);
};

#endif // GRAPHICSSCENE_H
