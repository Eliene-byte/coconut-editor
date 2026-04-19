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
    setRenderHint(QPainter::Antialiasing, false);
    
    // Fundo chapado cinza escuro
    setBackgroundBrush(QBrush(QColor(43, 43, 43)));
    setStyleSheet("border: 3px inset #1a1a1a;");
    
    drawRuler();
    drawTracks(6);
    
    addClip(1.0, 4.0, 0);
    addClip(6.0, 3.0, 1);
    addClip(10.0, 5.0, 0);
}

void TimelineWidget::drawRuler()
{
    QPen majorPen(QColor(255, 191, 0), 3); // Âmbar
    QPen minorPen(QColor(100, 100, 100), 1);
    int totalSeconds = 180;
    
    // Régua grossa
    m_scene->addRect(0, 0, 8000, 30, QPen(QColor(10, 10, 10)), QBrush(QColor(30, 30, 30)));
    
    for (int i = 0; i <= totalSeconds; i++) {
        int x = i * m_pixelsPerSecond;
        // Traço maior a cada segundo
        m_scene->addLine(x, 0, x, 30, majorPen);
        
        auto *text = m_scene->addText(QString("%1s").arg(i, 3, 10, QChar('0')));
        text->setDefaultTextColor(QColor(255, 191, 0));
        QFont font("Consolas", 10, QFont::Bold);
        text->setFont(font);
        text->setPos(x + 3, 4);
        
        // Traços menores
        for (int j = 1; j < 10; j++) {
            int subX = x + j * m_pixelsPerSecond / 10;
            m_scene->addLine(subX, 20, subX, 30, minorPen);
        }
    }
}

void TimelineWidget::drawTracks(int numTracks)
{
    for (int i = 0; i < numTracks; i++) {
        int y = 35 + i * m_trackHeight;
        // Linha de track grossa
        QPen trackPen(QColor(10, 10, 10), 2);
        m_scene->addRect(0, y, 8000, m_trackHeight, trackPen, QBrush(QColor(51, 51, 51)));
        
        // Label do track
        auto *label = m_scene->addText(QString("TRK_%1").arg(i + 1, 2, 10, QChar('0')));
        label->setDefaultTextColor(QColor(0, 255, 0)); // Verde CRT
        QFont font("Consolas", 11, QFont::Bold);
        label->setFont(font);
        label->setPos(10, y + m_trackHeight/2 - 10);
    }
}

void TimelineWidget::addClip(qreal startSeconds, qreal durationSeconds, int track)
{
    qreal x = startSeconds * m_pixelsPerSecond;
    qreal y = 35 + track * m_trackHeight + 3;
    qreal w = durationSeconds * m_pixelsPerSecond;
    qreal h = m_trackHeight - 6;
    
    auto *clip = new ClipItem(x, y, w, h, m_pixelsPerSecond);
    connect(clip, &ClipItem::requestSnap, this, &TimelineWidget::snapClipToRuler);
    m_scene->addItem(clip);
}

qreal TimelineWidget::snapToSecond(qreal x) const
{
    // Snap industrial: só em segundo inteiro. Sem meio termo.
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
