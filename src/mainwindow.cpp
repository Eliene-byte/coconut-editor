#include "mainwindow.h"
#include "timelinewidget.h"
#include <QDockWidget>
#include <QTextEdit>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QFile>
#include <QApplication>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("COCONUT EDITOR [INDUSTRIAL]");
    resize(1440, 900);

    QFile styleFile("src/industrial.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(style);
    }

    setupMenuBar();
    setupToolBar();
    setupDocks();

    m_timeline = new TimelineWidget(this);
    setCentralWidget(m_timeline);

    statusBar()->showMessage("SYS: READY | TRANSPORT: STOP | SNAP: ON | TEMP: 42C");
}

void MainWindow::setupMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu("[ARQUIVO]");
    fileMenu->addAction("F1 - NOVO PROJETO");
    fileMenu->addAction("F2 - ABRIR");
    fileMenu->addAction("F3 - SALVAR");
    fileMenu->addSeparator();
    fileMenu->addAction("F10 - SAIR", this, &QWidget::close);

    QMenu *editMenu = menuBar()->addMenu("[EDITAR]");
    editMenu->addAction("CORTAR ", this, &MainWindow::onCut);
    editMenu->addAction("SNAP ON/OFF ", this, &MainWindow::onToggleSnap);

    QMenu *viewMenu = menuBar()->addMenu("[VISUALIZAR]");
    viewMenu->addAction("RESET LAYOUT");
}

void MainWindow::setupToolBar()
{
    m_transportBar = addToolBar("Transporte");
    m_transportBar->setMovable(false);
    m_transportBar->setIconSize(QSize(32, 32));
    m_transportBar->setStyleSheet(R"(
        QToolBar {
            background-color: #1e1e1e;
            border: 2px solid #0a0a0a;
            spacing: 4px;
            padding: 4px;
        }
        QToolButton {
            background-color: #3a3a3a;
            border: 2px outset #4a4a4a;
            color: #e0e0e0;
            font-family: Consolas;
            font-size: 11px;
            font-weight: bold;
            min-width: 80px;
            min-height: 40px;
            padding: 4px;
        }
        QToolButton:pressed {
            border: 2px inset #2a2a2a;
            background-color: #2a2a2a;
        }
        QToolButton:checked {
            background-color: #006400;
            border: 2px inset #004000;
            color: #ffffff;
        }
    )");

    // PLAY - ícone padrão do Qt
    m_playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), "F5\nPLAY", this);
    m_playAction->setCheckable(true);
    connect(m_playAction, &QAction::triggered, this, &MainWindow::onPlay);
    m_transportBar->addAction(m_playAction);

    // STOP
    m_stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), "F6\nSTOP", this);
    connect(m_stopAction, &QAction::triggered, this, &MainWindow::onStop);
    m_transportBar->addAction(m_stopAction);

    m_transportBar->addSeparator();

    // CORTE - usando ícone de tesoura
    m_cutAction = new QAction(style()->standardIcon(QStyle::SP_DialogResetButton), "F7\nCORTE", this);
    connect(m_cutAction, &QAction::triggered, this, &MainWindow::onCut);
    m_transportBar->addAction(m_cutAction);

    m_transportBar->addSeparator();

    // SNAP ON/OFF
    m_snapAction = new QAction("F8\nSNAP", this);
    m_snapAction->setCheckable(true);
    m_snapAction->setChecked(true);
    connect(m_snapAction, &QAction::triggered, this, &MainWindow::onToggleSnap);
    m_transportBar->addAction(m_snapAction);
}

void MainWindow::setupDocks()
{
    m_projectPanel = new QTextEdit(this);
    m_projectPanel->setPlainText(
        "UNIDADE: C:\\MEDIA\n\n"
        "DIR: /PROJETO_01/\n"
        "---------------------------\n"
        "VID_001.MP4 00:03:24\n"
        "AUD_001.WAV 00:03:24\n"
        "IMG_LOGO.PNG 1920x1080\n"
        "---------------------------\n"
        "TOTAL: 3 ARQ | 248.2 MB"
    );
    m_projectPanel->setReadOnly(true);
    m_projectDock = new QDockWidget("[ F1 ] ARQUIVOS", this);
    m_projectDock->setWidget(m_projectPanel);
    addDockWidget(Qt::LeftDockWidgetArea, m_projectDock);

    m_previewPanel = new QLabel(this);
    m_previewPanel->setAlignment(Qt::AlignCenter);
    m_previewPanel->setStyleSheet(R"(
        background-color: #0a0a0a;
        color: #00ff00;
        font-family: Consolas;
        font-size: 14px;
        border: 3px inset #1a1a1a;
    )");
    m_previewPanel->setText(":: MONITOR DE SAIDA ::\n\nSINAL: 1920x1080p @ 29.97\nCODEC: H.264\nSTATUS: STOP");
    m_previewPanel->setMinimumHeight(300);
    m_previewDock = new QDockWidget("[ F2 ] MONITOR", this);
    m_previewDock->setWidget(m_previewPanel);
    addDockWidget(Qt::TopDockWidgetArea, m_previewDock);

    m_effectsPanel = new QTextEdit(this);
    m_effectsPanel->setPlainText(
        "PARAMETROS DO CLIPE\n"
        "===================\n\n"
        "POS_X: 0960\n"
        "POS_Y: 0540\n"
        "ESCALA: 100%\n"
        "ROTAC: 000.0\n\n"
        "OPACID: 100%\n"
        "BLEND: NORMAL\n\n"
        "[PLAYHEAD: 00:00:00]"
    );
    m_effectsPanel->setReadOnly(true);
    m_effectsDock = new QDockWidget("[ F3 ] PARAMETROS", this);
    m_effectsDock->setWidget(m_effectsPanel);
    addDockWidget(Qt::RightDockWidgetArea, m_effectsDock);
}

void MainWindow::onPlay()
{
    m_isPlaying = true;
    m_playAction->setChecked(true);
    m_previewPanel->setText(":: MONITOR DE SAIDA ::\n\nSINAL: 1920x1080p @ 29.97\nCODEC: H.264\nSTATUS: PLAY >>");
    statusBar()->showMessage("SYS: RUNNING | TRANSPORT: PLAY | SNAP: ON | TEMP: 43C");
}

void MainWindow::onStop()
{
    m_isPlaying = false;
    m_playAction->setChecked(false);
    m_previewPanel->setText(":: MONITOR DE SAIDA ::\n\nSINAL: 1920x1080p @ 29.97\nCODEC: H.264\nSTATUS: STOP");
    statusBar()->showMessage("SYS: READY | TRANSPORT: STOP | SNAP: ON | TEMP: 42C");
}

void MainWindow::onCut()
{
    statusBar()->showMessage("SYS: EXEC | COMANDO: CORTE NA POSICAO DO PLAYHEAD | TEMP: 42C", 2000);
}

void MainWindow::onToggleSnap()
{
    bool snapOn = m_snapAction->isChecked();
    QString snapTxt = snapOn? "ON" : "OFF";
    statusBar()->showMessage(QString("SYS: READY | TRANSPORT: STOP | SNAP: %1 | TEMP: 42C").arg(snapTxt));
}
