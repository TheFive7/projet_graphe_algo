#ifndef WIDGETNODE_H
#define WIDGETNODE_H

#include "noeud.h"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

class widgetEdge;
class widgetGraph;

class widgetNode : public QGraphicsItem
{
public:
    static inline qreal size = 20;

    widgetNode(widgetGraph *widgetGraph, const Noeud& noeud);

    void addEdge(widgetEdge *edge);
    QList<widgetEdge *> edges() const;
    const std::unique_ptr<Noeud>& getNoeud() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void calculateForces();
    bool advancePosition();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<widgetEdge*>      edgeList;
    widgetGraph*            graph;
    QPointF                 newPos;
    std::unique_ptr<Noeud>  noeud;

};
#endif // WIDGETNODE_H
