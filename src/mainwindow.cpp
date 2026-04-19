#include "mainwindow.h"
#include "timelinewidget.h"
#include <QDockWidget>
#include <QTextEdit>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("CoConut Editor v0.4 - Premiere 2026 Layout");
    resize(1600, 900);
    
    setupMenuBar();
    setupDocks();
    
    // Timeline fica no centro embaixo
    m_timeline = new TimelineWidget(this);
    setCentralWidget(m_timeline);
    
    statusBar()->showMessage("CoConut Editor v0.4 - Pronto");
}

void MainWindow::setupMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu("&Arquivo");
    fileMenu->addAction("Novo Projeto");
    fileMenu->addAction("Abrir Projeto");
    fileMenu->addSeparator();
    fileMenu->addAction("Sair", this, &QWidget::close);
    
    QMenu *editMenu = menuBar()->addMenu("&Editar");
    editMenu->addAction("Desfazer");
    editMenu->addAction("Refazer");
    
    QMenu *viewMenu = menuBar()->addMenu("&Janela");
    viewMenu->addAction("Resetar Layout");
}

void MainWindow::setupDocks()
{
    // 1. Painel Projeto - esquerda
    m_projectPanel = new QTextEdit(this);
    m_projectPanel->setPlainText("Projeto\n\n[ ] video1.mp4\n[ ] audio1.wav\n[ ] imagem.png");
    m_projectDock = new QDockWidget("Projeto", this);
    m_projectDock->setWidget(m_projectPanel);
    m_projectDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::LeftDockWidgetArea, m_projectDock);
    
    // 2. Preview - topo
    m_previewPanel = new QLabel(this);
    m_previewPanel->setAlignment(Qt::AlignCenter);
    m_previewPanel->setStyleSheet("background-color: #1a1a1a; color: #666; font-size: 24px;");
    m_previewPanel->setText("PREVIEW\n\n1920x1080 @ 30fps");
    m_previewPanel->setMinimumHeight(300);
    m_previewDock = new QDockWidget("Program Monitor", this);
    m_previewDock->setWidget(m_previewPanel);
    m_previewDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::TopDockWidgetArea, m_previewDock);
    
    // 3. Efeitos/Propriedades - direita
    m_effectsPanel = new QTextEdit(this);
    m_effectsPanel->setPlainText("Efeitos\n\n> Movimento\n  Posição: 960, 540\n  Escala: 100%\n  Rotação: 0°\n\n> Opacidade\n  100%");
    m_effectsDock = new QDockWidget("Controles de Efeito", this);
    m_effectsDock->setWidget(m_effectsPanel);
    m_effectsDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::RightDockWidgetArea, m_effectsDock);
    
    // Deixa a timeline ocupar o resto
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
}
