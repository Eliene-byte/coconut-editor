#pragma once
#include <QMainWindow>

class TimelineWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private:
    TimelineWidget *m_timeline;
};
