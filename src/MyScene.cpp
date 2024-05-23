#include "MyScene.h"

MyScene::MyScene(QObject* parent, QPixmap* pixBackground) : QGraphicsScene(parent) {
    this->pixBackground = pixBackground;
    //create the timer
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MyScene::update);
    timer->start(30); ///30 milliseconds

    enemies = new QVector<Enemy*>(100);
    towers = new QVector<Tower*>(5);
    castle = new Castle(QPixmap("../assets/castle.jpg"), *pixBackground, 1000, 10, this);
    addItem(castle);

    towerMenu =  addWidget(new TowerMenu(this));
    hideTowerMenu();


    createPathToScene();
    createPathPointsToScene();

    //create an enemy
    QPixmap enemy_bg("../assets/hqdefault.jpg");
    QPixmap skull_bg("../assets/Skeleton.png");
    QPixmap zombie_bg("../assets/Zombie.png");
    QPixmap gobelin_bg("../assets/gobelin.png");
    QPixmap gargoyle_bg("../assets/gargoyle.png");
    QPixmap orc_bg("../assets/orc.png");
    QPixmap necromancer_bg("../assets/necromancer.png");
    QPixmap gouls_bg("../assets/goule.png");
    QPixmap mage_bg("../assets/mage.png");
    QPixmap commander_bg("../assets/commander.png");
    //QPixmap Freixas_bg("../assets/Freixas.png");

    Skeleton* skeleton = new Skeleton(skull_bg, this);
    Zombies* zombies = new Zombies(zombie_bg, this);
    Gobelin* gobelin = new Gobelin(gobelin_bg, this);
    Gargoyles* gargoyle = new Gargoyles(gargoyle_bg, this);
    Orcs* orc = new Orcs(orc_bg, this);
    Necromancer* necromancer = new Necromancer(necromancer_bg, this);
    Gouls* gouls = new Gouls(gouls_bg, this);
    Mage* mage = new Mage(mage_bg, this);
    Commander* commander = new Commander(commander_bg, this);
    //Freixas* freixas = new Freixas(Freixas_bg, this);


    addEnemy(skeleton);
    addEnemy(zombies);
    addEnemy(gobelin);
    addEnemy(gargoyle);
    addEnemy(orc);
    addEnemy(necromancer);
    addEnemy(gouls);
    addEnemy(mage);
    addEnemy(commander);
    //addEnemy(freixas);

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
void MyScene::removeEnemy(Enemy *e) {
    enemies->remove(enemies->indexOf(e));
    //do not remove the item from the scene or the scene() method accessed in the destructor will return null
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
    e->hide();
    removeEnemy(e);
    delete e;
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
    if(button->text() == "Classic Tower Nv.1"){
        tempTower = new ClassicTower1();
    }
    if(button->text() == "Classic Tower Nv.2"){
        tempTower = new ClassicTower2();
    }
    if(button->text() == "Classic Tower Nv.3"){
        tempTower = new ClassicTower3();
    }
    if(button->text() == "Tesla Tower Nv.1"){
        tempTower = new TeslaTower1();
    }
    if(button->text() == "Tesla Tower Nv.2"){
        tempTower = new TeslaTower2();
    }
    if(button->text() == "Tesla Tower Nv.3"){
        tempTower = new TeslaTower3();
    }
    if(button->text() == "Canon Tower Nv.1"){
        tempTower = new CanonTower1();
    }
    if(button->text() == "Canon Tower Nv.2"){
        tempTower = new CanonTower2();
    }
    if(button->text() == "Canon Tower Nv.3"){
        tempTower = new CanonTower3();
    }
    if(button->text() == "Crossbow Tower Nv.1"){
        tempTower = new CrossbowTower1();
    }
    if(button->text() == "Crossbow Tower Nv.2"){
        tempTower = new CrossbowTower2();
    }
    if(button->text() == "Crossbow Tower Nv.3"){
        tempTower = new CrossbowTower3();
    }

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

Castle* MyScene::getCastle() const {
    return castle;
}






