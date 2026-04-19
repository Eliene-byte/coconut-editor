#include "timelinewidget.h"
#include "clipitem.h"
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QtMath>

TimelineWidget::TimelineWidget(QWidget *parent) : QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setDragMode(QGraphicsView::RubberBandDrag);
    setBackgroundBrush(QBrush(QColor(30, 30, 30)));
    
    drawRuler();
    drawTracks(4);
    
    addClip(1.3, 3.5, 0);
    addClip(5.7, 2.0, 1);
}

void TimelineWidget::drawRuler()
{
    QPen pen(Qt::gray, 1);
    QPen majorPen(QColor(180, 180, 180), 2);
    int totalSeconds = 60;
    
    for (int i = 0; i <= totalSeconds * 10; i++) {
        int x = i * m_pixelsPerSecond / 10;
        if (i % 10 == 0) {
            m_scene->addLine(x, 0, x, 20, majorPen);
            auto *text = m_scene->addText(QString::number(i / 10) + "s");
            text->setDefaultTextColor(Qt::white);
            text->setPos(x + 2, 0);
        } else if (i % 5 == 0) {
            m_scene->addLine(x, 10, x, 20, pen);
        } else {
            m_scene->addLine(x, 15, x, 20, pen);
        }
    }
}

void TimelineWidget::drawTracks(int numTracks)
{
    QPen pen(QColor(60, 60, 60), 1);
    for (int i = 0; i < numTracks; i++) {
        int y = 25 + i * m_trackHeight;
        m_scene->addLine(0, y, 6000, y, pen);
        auto *label = m_scene->addText(QString("V%1").arg(numTracks - i));
        label->setDefaultTextColor(Qt::gray);
        label->setPos(5, y + 5);
    }
}

void TimelineWidget::addClip(qreal startSeconds, qreal durationSeconds, int track)
{
    qreal x = startSeconds * m_pixelsPerSecond;
    qreal y = 25 + track * m_trackHeight + 5;
    qreal w = durationSeconds * m_pixelsPerSecond;
    qreal h = m_trackHeight - 10;
    
    auto *clip = new ClipItem(x, y, w, h, m_pixelsPerSecond);
    connect(clip, &ClipItem::requestSnap, this, &TimelineWidget::snapClipToRuler);
    m_scene->addItem(clip);
}

qreal TimelineWidget::snapToSecond(qreal x) const
{
    qreal seconds = x / m_pixelsPerSecond;
    qreal snappedSeconds = qRound(seconds);
    return snappedSeconds * m_pixelsPerSecond;
}

void TimelineWidget::snapClipToRuler(ClipItem* clip)
{
    qreal currentX = clip->x();
    qreal snappedX = snapToSecond(currentX);
    clip->setX(snappedX);
}
