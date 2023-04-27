#ifndef WIDGETEDGE_H
#define WIDGETEDGE_H

#include "widgetnode.h"

class widgetEdge : public QGraphicsItem
{
private:
    widgetNode* source,* dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

public:
    widgetEdge(widgetNode* sourceNode, widgetNode* destNode);

    widgetNode* sourceNode() const;
    widgetNode* destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }
};

#endif // WIDGETEDGE_H
