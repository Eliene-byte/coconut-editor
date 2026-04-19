#pragma once
#include <QGraphicsRectItem>
#include <QBrush>
#include <QObject>

class ClipItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    ClipItem(qreal x, qreal y, qreal w, qreal h, int pixelsPerSecond);
    
signals:
    void requestSnap(ClipItem* clip);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool m_dragging;
    QPointF m_dragStartPos;
    int m_pixelsPerSecond;
};
