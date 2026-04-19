#pragma once
#include <QGraphicsRectItem>
#include <QObject>

class QPainter;
class QStyleOptionGraphicsItem;

class ClipItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    ClipItem(qreal x, qreal y, qreal w, qreal h, int pixelsPerSecond);
    void setFilePath(const QString &p){ m_filePath = p; }
    QString filePath() const { return m_filePath; }

signals:
    void requestSnap(ClipItem* clip);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    bool m_dragging;
    QPointF m_dragStartPos;
    int m_pixelsPerSecond;
    QString m_filePath;
};
