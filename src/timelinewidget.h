#pragma once
#include <QGraphicsView>

class QGraphicsScene;
class QGraphicsLineItem;
class QTimer;
class ClipItem;

class TimelineWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TimelineWidget(QWidget *parent = nullptr);
    void addClip(qreal startSeconds, qreal durationSeconds, int track);
    void addClipWithFile(qreal startSeconds, qreal durationSeconds, int track, const QString &filePath);
    void cutSelectedClip();
    void togglePlay();
    void stopPlay();

private slots:
    void snapClipToRuler(ClipItem* clip);
    void updatePlayhead();

private:
    void drawRuler();
    void drawTracks(int numTracks);
    qreal snapToSecond(qreal x) const;

    QGraphicsScene *m_scene;
    int m_pixelsPerSecond = 50;
    int m_trackHeight = 60;
    QGraphicsLineItem *m_playhead = nullptr;
    QTimer *m_playTimer = nullptr;
    qreal m_playheadPos = 0;
    bool m_isPlaying = false;
};
