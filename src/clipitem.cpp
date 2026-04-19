#include "clipitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QPainter>

ClipItem::ClipItem(qreal x, qreal y, qreal w, qreal h, int pixelsPerSecond)
    : QGraphicsRectItem(x, y, w, h), m_dragging(false), m_pixelsPerSecond(pixelsPerSecond)
{
    // Verde escuro industrial
    setBrush(QBrush(QColor(0, 100, 0)));
    // Borda amarelo âmbar
    setPen(QPen(QColor(255, 191, 0), 2));
    
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

void ClipItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_dragging = true;
    m_dragStartPos = event->pos();
    setBrush(QBrush(QColor(0, 150, 0))); // Clareia quando segura
    setZValue(10);
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
    setBrush(QBrush(QColor(0, 100, 0))); // Volta ao normal
    setZValue(0);
    emit requestSnap(this);
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void ClipItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF r = rect();
    
    // Bloco chapado sem antialias
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->drawRect(r);
    
    // Label no clipe
    painter->setPen(QColor(255, 255, 255));
    painter->setFont(QFont("Consolas", 9, QFont::Bold));
    painter->drawText(r.adjusted(4, 2, -4, -2), Qt::AlignLeft | Qt::AlignTop, "CLIPE");
}
