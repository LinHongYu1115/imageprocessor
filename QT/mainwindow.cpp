#include "mainwindow.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Image Processing"));

    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    imgwin = new QLabel();
    QPixmap *initPixmap = new QPixmap(300, 200);
    initPixmap->fill(QColor(255, 255, 255));

    imgwin->resize(300, 200);
    imgwin->setScaledContents(true);
    imgwin->setPixmap(*initPixmap);

    mainLayout->addWidget(imgwin);
    setCentralWidget(central);

    createActions();
    createMenus();
    createToolBars();
}

MainWindow::~MainWindow() {}

void MainWindow::createActions()
{
    openFileAction = new QAction(QStringLiteral("開啟檔案&O"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("開啟影像檔案"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(showOpenFile()));

    exitAction = new QAction(QStringLiteral("結束&Q"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程式"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    zoomInAction = new QAction(QStringLiteral("放大&+"), this);
    zoomInAction->setShortcut(tr("Ctrl++"));
    zoomInAction->setStatusTip(QStringLiteral("放大影像"));
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAction = new QAction(QStringLiteral("縮小&-"), this);
    zoomOutAction->setShortcut(tr("Ctrl+-"));
    zoomOutAction->setStatusTip(QStringLiteral("縮小影像"));
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案&F"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);
}

void MainWindow::createToolBars()
{
    fileTool = addToolBar("檔案");
    fileTool->addAction(openFileAction);
    fileTool->addAction(zoomInAction);
    fileTool->addAction(zoomOutAction);
}

void MainWindow::loadFile(QString filename)
{
    qDebug() << QString("檔名：%1").arg(filename);

    QByteArray ba = filename.toLatin1();
    printf("FN:%s\n", (char *)ba.data());

    img.load(filename);
    imgwin->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::openNewWindowWithImage(QString filename)
{
    MainWindow *newIPWin = new MainWindow();
    newIPWin->show();
    newIPWin->loadFile(filename);
}

void MainWindow::showOpenFile()
{
    filename = QFileDialog::getOpenFileName(this, QStringLiteral("開啟影像"), tr("."), "bmp(*.bmp);;png(*.png);;jpeg(*.jpg)");

    if (!filename.isEmpty())
    {
        if (img.isNull())
        {
            loadFile(filename);
        }
        else
        {
            openNewWindowWithImage(filename);
        }
    }
}

void MainWindow::zoomIn()
{
    openNewWindowWithZoomedImage(1.2);
}

void MainWindow::zoomOut()
{
    openNewWindowWithZoomedImage(0.8);
}

void MainWindow::openNewWindowWithZoomedImage(double scale)
{
    MainWindow *newIPWin = new MainWindow();
    newIPWin->show();
    newIPWin->loadFile(filename);
    newIPWin->imgwin->resize(imgwin->size() * scale);

    QPixmap scaledPixmap = QPixmap::fromImage(img).scaled(newIPWin->imgwin->size(), Qt::KeepAspectRatio);
    newIPWin->imgwin->setPixmap(scaledPixmap);
}
