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
    setWindowTitle("My main window");
    resize(pbWidth, pbHeight); //fit the window to the background image size

    helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction* actionHelp = new QAction(tr("&About"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    helpMenu->addAction(actionHelp);

}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutMenu(){
    QMessageBox msgBox;
    msgBox.setText("A small QT/C++ projet...");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}