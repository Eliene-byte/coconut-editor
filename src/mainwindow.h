#pragma once
#include <QMainWindow>

class TimelineWidget;
class QTextEdit;
class QLabel;
class QDockWidget;
class QToolBar;
class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onPlay();
    void onStop();
    void onCut();
    void onToggleSnap();

private:
    void setupDocks();
    void setupMenuBar();
    void setupToolBar();

    TimelineWidget *m_timeline;
    QDockWidget *m_projectDock;
    QDockWidget *m_previewDock;
    QDockWidget *m_effectsDock;
    QTextEdit *m_projectPanel;
    QLabel *m_previewPanel;
    QTextEdit *m_effectsPanel;

    QToolBar *m_transportBar;
    QAction *m_playAction;
    QAction *m_stopAction;
    QAction *m_cutAction;
    QAction *m_snapAction;

    bool m_isPlaying = false;
};
