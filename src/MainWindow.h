#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H


#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QApplication>
#include <QScreen>
#include <QRectF>
#include <QFile>
#include "MyScene.h"
#include "MyView.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private :
    MyScene* mainScene;
    MyView* mainView;
    QMenu* helpMenu;


public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();
    void insertAndSortData(const QString& filename, const QString& pseudo, int best_time);


public slots:
    void slot_aboutRestart();
    signals:
    void userRestarted();
};


#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H
