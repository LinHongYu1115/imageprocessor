#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);
    void openNewWindowWithImage(QString filename);

private slots:
    void showOpenFile();
    void zoomIn();
    void zoomOut();
    void openNewWindowWithZoomedImage(double scale);

private:
    QWidget *central;
    QMenu *fileMenu;
    QToolBar *fileTool;
    QImage img;
    QString filename;
    QLabel *imgwin;
    QAction *openFileAction;
    QAction *exitAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
};

#endif // MAINWINDOW_H
