#include "widgetnode.h"
#include "widgetedge.h"
#include "widgetgraph.h"

widgetNode::widgetNode(widgetGraph *widgetGraph, const Noeud& noeud) : graph(widgetGraph), noeud{std::make_unique<Noeud>(noeud)} {
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void widgetNode::addEdge(widgetEdge *edge) {
    edgeList << edge;
    edge->adjust();
}

QList<widgetEdge *> widgetNode::edges() const {
    return edgeList;
}

const std::unique_ptr<Noeud>& widgetNode::getNoeud() const {
    return noeud;
}

void widgetNode::calculateForces() {
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }
    // Sum up all forces pushing this item away
    qreal xvel = 0;
    qreal yvel = 0;

    QRectF sceneRect = scene()->sceneRect();
    qreal adjust = 10.5;
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + adjust), sceneRect.right() - adjust));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + adjust), sceneRect.bottom() - adjust));
}

bool widgetNode::advancePosition() {
    if (newPos == pos()) {
        return false;
    }

    setPos(newPos);
    return true;
}

QRectF widgetNode::boundingRect() const {
    return {-size / 2, -size / 2, size, size};
}


QPainterPath widgetNode::shape() const {
    QPainterPath path;
    path.addEllipse(-size / 2, -size / 2, size, size);
    return path;
}


void widgetNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    // Dessin du noeud
    painter->setPen(Qt::NoPen);

    auto color = QColor(Qt::red).darker(120);

    if (option->state & QStyle::State_Sunken) { // Si le noeud est cliqué
        painter->setBrush(color.lighter(120));
    } else {
        painter->setBrush(color);
    }
    painter->drawPath(shape());

    painter->setPen(QPen(Qt::black, 0));
    painter->drawPath(shape());

    // Dessin de l'id du noeud
    QString number;
    number.setNum(noeud->getId());

    QFont font(painter->font());
    QPointF idPos;
    if(noeud->getId() < 10) {
        font.setPointSize(13);
        idPos = {-4, 6};
    } else if(noeud->getId() < 100) {
        font.setPointSize(10);
        idPos = {-7, 5};
    }

    painter->setFont(font);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(idPos, number);
}

QVariant widgetNode::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
    case ItemPositionHasChanged:
        for (widgetEdge *edge : qAsConst(edgeList)) {
            edge->adjust();
        }
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void widgetNode::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mousePressEvent(event);
}

void widgetNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mouseReleaseEvent(event);
    graph->itemMoved();
}







