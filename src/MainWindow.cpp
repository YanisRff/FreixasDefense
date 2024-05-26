#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //Define the background image. All the windows/scence/view size will be based on the background image size
    QPixmap* pixBackground = new QPixmap("../assets/mapImage.png");
    int pbWidth = pixBackground->width();
    int pbHeight = pixBackground->height();

    //Create the scene and draw the image
    mainScene = new MyScene(this, pixBackground);
    mainScene->drawBackground(new QPainter(), QRectF());
    mainScene->setSceneRect(0, 0, pbWidth, pbHeight); //make the scene the exact same size as the window

    //Create the view to the scene
    mainView = new MyView();
    mainView->setScene(mainScene);
    mainView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(mainView);
    setWindowTitle("Freixas Defense");
    resize(pbWidth, pbHeight); //fit the window to the background image size

    helpMenu = menuBar()->addMenu(tr("&Game"));
    QAction* actionHelp = new QAction(tr("&Restart"), this);
    connect(actionHelp, &QAction::triggered, this, &MainWindow::slot_aboutRestart);
    connect(this, &MainWindow::userRestarted, mainScene, &MyScene::restartGame);
    helpMenu->addAction(actionHelp);

}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutRestart() {
    emit userRestarted();
}

