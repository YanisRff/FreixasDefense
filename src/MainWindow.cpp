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

void MainWindow::insertAndSortData(const QString &filename, const QString &pseudo, int best_time) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for reading:" << file.errorString();
            return;
        }

        // Lire les données existantes dans le fichier
        QTextStream in(&file);
        QStringList dataList;
        while (!in.atEnd()) {
            QString line = in.readLine();
            dataList.append(line);
        }
        file.close();

        // Ajouter la nouvelle entrée
        QString newEntry = QString("%1;%2").arg(pseudo).arg(best_time);
        dataList.append(newEntry);

        // Trier les données par ordre décroissant de best_time
        std::sort(dataList.begin(), dataList.end(), [](const QString &a, const QString &b) {
            int bestTimeA = a.split(";").last().toInt();
            int bestTimeB = b.split(";").last().toInt();
            return bestTimeA > bestTimeB;
        });

        // Écrire les données triées dans le fichier
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            qDebug() << "Failed to open file for writing:" << file.errorString();
            return;
        }
        QTextStream out(&file);
        for (const QString& entry : dataList) {
            out << entry << "\n";
        }
        file.close();
    }
