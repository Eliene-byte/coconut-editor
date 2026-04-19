#include "mainwindow.h"
#include "timelinewidget.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("CoConut Editor v0.2 - Timeline");
    resize(1400, 600);
    
    m_timeline = new TimelineWidget(this);
    setCentralWidget(m_timeline);
}
