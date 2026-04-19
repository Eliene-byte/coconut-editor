#pragma once
#include <QMainWindow>

class TimelineWidget;
class QTextEdit;
class QLabel;
class QDockWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private:
    void setupDocks();
    void setupMenuBar();
    
    TimelineWidget *m_timeline;
    QDockWidget *m_projectDock;
    QDockWidget *m_previewDock;
    QDockWidget *m_effectsDock;
    QTextEdit *m_projectPanel;
    QLabel *m_previewPanel;
    QTextEdit *m_effectsPanel;
};
