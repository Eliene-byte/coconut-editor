#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>

class ClipItem;

class TimelineWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TimelineWidget(QWidget *parent = nullptr);
    void addClip(qreal startSeconds, qreal durationSeconds, int track);

private slots:
    void snapClipToRuler(ClipItem* clip);

private:
    QGraphicsScene *m_scene;
    int m_pixelsPerSecond = 100;
    int m_trackHeight = 60;
    void drawRuler();
    void drawTracks(int numTracks);
    qreal snapToSecond(qreal x) const;
};
