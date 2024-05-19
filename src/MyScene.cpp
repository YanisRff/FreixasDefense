#include "MyScene.h"

MyScene::MyScene(QObject* parent, QPixmap* pixBackground) : QGraphicsScene(parent) {
    this->pixBackground = pixBackground;
    //create the timer
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MyScene::update);
    timer->start(30); ///30 milliseconds

    enemies = new QVector<Enemy*>(100);
    towers = new QVector<Tower*>(5);
    castle = new Castle(QPixmap("../assets/castle.jpg"), *pixBackground, 1000, 10);
    addItem(castle);

    towerMenu =  addWidget(new TowerMenu(this));


    createPathToScene();
    createPathPointsToScene();

    //create an enemy
    QPixmap enemy_bg("../assets/hqdefault.jpg");
    Enemy* enemyOne = new Enemy(enemy_bg, 300, 100, 3, 1);
    connect(enemyOne, &Enemy::enemyKilled, this, &MyScene::killEnemy); //TODO pass the connection to the constructor of enemy!!
    connect(enemyOne, &Enemy::castleAttacked, castle, &Castle::isAttacked);
    Enemy* enemyTwo = new Enemy(enemy_bg, 300, 10, 3, 1);
    connect(enemyTwo, &Enemy::enemyKilled, this, &MyScene::killEnemy);
    connect(enemyTwo, &Enemy::castleAttacked, castle, &Castle::isAttacked);
    Enemy* enemyThree = new Enemy(enemy_bg, 300, 10, 2, 1);
    connect(enemyThree, &Enemy::enemyKilled, this, &MyScene::killEnemy);
    connect(enemyThree, &Enemy::castleAttacked, castle, &Castle::isAttacked);
    Enemy* enemyFour = new Enemy(enemy_bg, 100, 10, 1, 1);
    connect(enemyFour, &Enemy::enemyKilled, this, &MyScene::killEnemy);
    connect(enemyFour, &Enemy::castleAttacked, castle, &Castle::isAttacked);

    addEnemy(enemyOne);
    addEnemy(enemyTwo);
    addEnemy(enemyThree);
    addEnemy(enemyFour);

    QPixmap tower_bg("../assets/tower_image.jpg");
    //Tower* tower = new Tower(500, 300, 1000, 3, 20, tower_bg);
    //addTower(tower);
    //tower->setPos(QPointF(300, 600));

}

MyScene::~MyScene() {
    delete pixBackground;
    for(auto& enemy: *enemies){
        if(enemy != nullptr){
            disconnect(enemy, &Enemy::enemyKilled, this, &MyScene::killEnemy); //TODO  do the disconnect in the destructor
            disconnect(enemy, &Enemy::castleAttacked, castle, &Castle::isAttacked);
            delete enemy;
            enemy = nullptr;
        }
    }
    delete enemies;
    enemies = nullptr;

    for(auto& tower : *towers){
        if(tower != nullptr){
            delete tower;
            tower = nullptr;
        }
    }
    delete towers;
    towers = nullptr;
    delete timer; //MAKE SURE ALL OBJECT ARE DISCONNECTED FROM IT!
    delete castle;
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
    QPointF controlPointOne(pixBackground->width()/3, pixBackground->height()/3 +  QRandomGenerator::global()->bounded(300, pixBackground->height()/2));
    QPointF controlPointTwo(2*pixBackground->width()/3, pixBackground->height()/4 +  QRandomGenerator::global()->bounded(300, pixBackground->height()/2));

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
    const int numSamples = pixBackground->width();  // Nombre de points à échantillonner
    for (int i = 0; i <= numSamples; i++) {
        // Calculer la position le long du chemin
        qreal t = static_cast<qreal>(i) / numSamples;
        QPointF point = pathItem->path().pointAtPercent(t);
        pathPoints->push_back(point);
    }
}

void MyScene::moveEnemies() {
    for(auto & enemy : *enemies){
        if(enemy != nullptr && enemy->getHealth() > 0){
            enemy->moveAlongPath(pathPoints);
        }
    }
}

void MyScene::addEnemy(Enemy *e) {
    enemies->append(e);
    addItem(e);
}

void MyScene::addTower(Tower *t) {
    towers->append(t);
    addItem(t);
}

QVector<Enemy *> *MyScene::getEnnemies() const {
    return enemies;
}

//Slots
void MyScene::killEnemy(Enemy *e) {
    e->setHealth(0);
    castle->setGold(castle->getGold() + e->getDroppedGold());
    removeItem(e);
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    switch (mouseEvent->button()) {
        case Qt::RightButton:
            showTowerMenu(mouseEvent->lastScenePos());
            break;
            //open tower menu selector
        case Qt::LeftButton:
            //hideTowerMenu();
            hasLeftClicked = true;
            break;
            //close tower menu selector
    }
}
void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    mousePos = event->scenePos();
    //std::cout << "New mouse pos " << mousePos.rx() << ", " << mousePos.ry() << std::endl;
}

void MyScene::showTowerMenu(QPointF clickedPos) {
    towerMenu->setPos(clickedPos);
    towerMenu->show();
}
void MyScene::hideTowerMenu() {
    towerMenu->hide();
}

void MyScene::spawnTowerOnScene(QAbstractButton* button) {
    hasLeftClicked = false; //purge previous left click
    Tower* tempTower = nullptr;
    if(button->text() == "towerOne"){
        QPixmap tower_bg = QPixmap("../assets/tower_image.jpg");
        tempTower = new Tower(400, 600, 1000, 2, 10, tower_bg);
    }
    //do other cases
    tempTower->setPos(mousePos.rx()-tempTower->getBackgroundImage().width()/2, mousePos.ry()-tempTower->getBackgroundImage().height()/2);
    addItem(tempTower);
    towerMenu->close();
    QTimer* localTimer = new QTimer();
    localTimer->start(30);
    connect(localTimer, &QTimer::timeout, [this, tempTower, localTimer](){
        tempTower->setPos(mousePos.rx()-tempTower->getBackgroundImage().width()/2, mousePos.ry()-tempTower->getBackgroundImage().height()/2);
        if(hasLeftClicked && tempTower->getIfTowerPlaceable()){ //player wants to place the tower (and can)
            localTimer->stop();
            delete localTimer;
            removeItem(tempTower);
            addTower(tempTower);
            return;
        }
        if(doesTowerCollideWithAnother(tempTower)){
            fadeToRedPixmap(tempTower);
            tempTower->setPlaceableTower(false);
        }
        else{
            restoreOriginalBackground(tempTower);
            tempTower->setPlaceableTower(true);
        }
        hasLeftClicked = false;
    });

}

void MyScene::fadeToRedPixmap(Tower* t) {
    QPixmap pixTower = t->getBackgroundImage();
    QPainter p(&pixTower);
    p.setOpacity(0.5);
    p.fillRect(pixTower.rect(), QColor(Qt::red).lighter(150));
    t->setPixmap(pixTower);
}

bool MyScene::doesTowerCollideWithAnother(Tower *t) {
    for(const auto tower : *towers){
        if(t->containsTower(tower)){
            return true;
        }
    }
    return false;
}

void MyScene::restoreOriginalBackground(Tower *t) {
    t->setPixmap(t->getOriginalBackgroundImage());
}






