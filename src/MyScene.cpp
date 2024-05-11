#include "MyScene.h"

MyScene::MyScene(QObject* parent, QPixmap* pixBackground) : QGraphicsScene(parent) {
    this->pixBackground = pixBackground;
    //create the timer
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MyScene::update);
    timer->start(30); ///30 milliseconds

    enemies = new QVector<Enemy*>();
    towers = new QVector<Towers*>();

    //create an enemy
    QPixmap bqtpm("../assets/st.png");
    Enemy* qtpm = new Enemy(bqtpm);
    addEnemy(qtpm);

    createPathToScene();
    createPathPointsToScene();

}

MyScene::~MyScene() {

}

void MyScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QPointF(0, 0), *pixBackground, sceneRect());
    // pixBackgroud est un attribut de type QPixmap qui contient l’image de fond
}

QPixmap *MyScene::getPixBackground() const {
    return pixBackground;
}

void MyScene::setPixBackground(QPixmap *pB) {
    pixBackground = pB;
}
/**
 * @brief Used to refresh the scene and move the QGraphicsItem in it.
 * Refresh rate determined by the QTimer timer attribute
 */
void MyScene::update() {
    moveEnemies();
}

/**
 * @brief Create a QGraphicsPathItem containing a bezier curved line from the spawn to the target and add it to the scene.
 * Initialize the attribute pathItem
 */
void MyScene::createPathToScene() {
    // Point A et point B
    QPointF pointA(0, pixBackground->height()/2);
    QPointF pointB(pixBackground->width(), pixBackground->height()/2);

    // Point de contrôle pour la courbe quadratique (quelque part entre A et B)
    QPointF controlPointOne(pixBackground->width()/3, pixBackground->height()/3 +  QRandomGenerator::global()->bounded(100, pixBackground->height()/2));
    QPointF controlPointTwo(2*pixBackground->width()/3, pixBackground->height()/4 +  QRandomGenerator::global()->bounded(100, pixBackground->height()/2));

    // Créer un chemin quadratique
    QPen pen(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    QPainterPath path(pointA);
    path.cubicTo(controlPointOne, controlPointTwo, pointB);
    QGraphicsPathItem* pI = new QGraphicsPathItem(path);
    pathItem = pI;
    addItem(pathItem);
}
/**
 * @brief An array containing every position to follow from the spawn point to the target.
 * Initialize the attribute pathPoints using the associated QPath from QGraphicsPathItem pathItem
 */
void MyScene::createPathPointsToScene() {
    // Vecteur pour stocker les points du chemin
    pathPoints = QSharedPointer<QVector<QPointF>>(new QVector<QPointF>);
    // Échantillonner le chemin
    const int numSamples = pixBackground->width()/2;  // Nombre de points à échantillonner
    for (int i = 0; i <= numSamples; i++) {
        // Calculer la position le long du chemin
        qreal t = static_cast<qreal>(i) / numSamples;
        QPointF point = pathItem->path().pointAtPercent(t);
        pathPoints->push_back(point);
    }

    // Afficher les points échantillonnés
    for (const auto& point : *pathPoints) {
        qDebug() << point;
    }
}

void MyScene::moveEnemies() {
    for(auto & enemie : *enemies){
        enemie->moveAlongPath(pathPoints);
    }
}

void MyScene::addEnemy(Enemy *e) {
    enemies->push_back(e);
    addItem(e);
}
