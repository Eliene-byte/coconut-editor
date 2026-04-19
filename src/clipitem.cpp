#include "clipitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPen>

ClipItem::ClipItem(qreal x, qreal y, qreal w, qreal h, int pixelsPerSecond)
    : QGraphicsRectItem(x, y, w, h), m_dragging(false), m_pixelsPerSecond(pixelsPerSecond)
{
    setBrush(QBrush(QColor(72, 152, 255)));
    setPen(QPen(Qt::white, 1));
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setAcceptHoverEvents(true);
}

void ClipItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_dragging = true;
    m_dragStartPos = event->pos();
    setOpacity(0.7);
    setZValue(1);
    QGraphicsRectItem::mousePressEvent(event);
}

void ClipItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_dragging) {
        QGraphicsRectItem::mouseMoveEvent(event);
    }
}

void ClipItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_dragging = false;
    setOpacity(1.0);
    setZValue(0);
    emit requestSnap(this);
    QGraphicsRectItem::mouseReleaseEvent(event);
}
