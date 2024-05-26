#include "MyScene.h"

MyScene::MyScene(QObject* parent, QPixmap* pixBackground) : QGraphicsScene(parent) {
    this->pixBackground = pixBackground;
    //create the timer
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MyScene::update);
    timer->start(30); ///30 milliseconds

    enemies = new QVector<Enemy*>(100);
    towers = new QVector<Tower*>(20);
    castle = new Castle(QPixmap("../assets/castle.png"), *pixBackground, 1000, 30, this);
    addItem(castle);

    towerMenu =  addWidget(new TowerMenu(this));
    hideTowerMenu();


    createPathToScene();
    createPathPointsToScene();

    //create an enemy
    QPixmap skull_bg("../assets/Skeleton.png");
    Skeleton* skeleton = new Skeleton(skull_bg, this);

    addEnemy(skeleton);

    QPixmap Freixas_bg("../assets/master_freixas.png");
    Freixas* freixas = new Freixas(Freixas_bg, this);
    addEnemy(freixas);


    launchEnemyWaves();
    elapsedTimer.start();

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
    //enemies->data()[enemies->indexOf(e)] = nullptr;
    //do not remove the item from the scene or the scene() method accessed in the destructor will return null
}

void MyScene::addTower(Tower *t) {
    if(t->getCost() > castle->getGold()){
        delete t;
    }
    else{
        removeItem(t); //remove previous phantom of the tower
        castle->setGold(castle->getGold() - t->getCost());
        t->setAttackTower(true);
        t->hideCollideRange();
        towers->append(t);
        addItem(t);
    }
}

QVector<Enemy *> *MyScene::getEnnemies() const {
    return enemies;
}


//Slots
void MyScene::killEnemy(Enemy *e) {
    e->setHealth(0);
    castle->setGold(castle->getGold() + e->getDroppedGold());
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
        case Qt::NoButton:
            break;
        case Qt::MiddleButton:
            break;
        case Qt::BackButton:
            break;
        case Qt::ForwardButton:
            break;
        case Qt::TaskButton:
            break;
        case Qt::ExtraButton4:
            break;
        case Qt::ExtraButton5:
            break;
        case Qt::ExtraButton6:
            break;
        case Qt::ExtraButton7:
            break;
        case Qt::ExtraButton8:
            break;
        case Qt::ExtraButton9:
            break;
        case Qt::ExtraButton10:
            break;
        case Qt::ExtraButton11:
            break;
        case Qt::ExtraButton12:
            break;
        case Qt::ExtraButton13:
            break;
        case Qt::ExtraButton14:
            break;
        case Qt::ExtraButton15:
            break;
        case Qt::ExtraButton16:
            break;
        case Qt::ExtraButton17:
            break;
        case Qt::ExtraButton18:
            break;
        case Qt::ExtraButton19:
            break;
        case Qt::ExtraButton20:
            break;
        case Qt::ExtraButton21:
            break;
        case Qt::ExtraButton22:
            break;
        case Qt::ExtraButton23:
            break;
        case Qt::ExtraButton24:
            break;
        case Qt::AllButtons:
            break;
        case Qt::MouseButtonMask:
            break;
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
            addTower(tempTower);
            return;
        }
        if(hasLeftClicked && !tempTower->getIfTowerPlaceable()){
            localTimer->stop();
            delete localTimer;
            delete tempTower;
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

void MyScene::restartGame() {
    std::cout << "USER RESTARTED" << std::endl;
    timer->stop();
    for(auto& enemy: *enemies){
        if(enemy != nullptr){
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

    waveNumber = 0;
    numberBaseEnemy = 3;
    numberIntermediateEnemy = 1;
    numberDifficultEnemy = 0;
    waveIncreaseRate.setInterval(30000);
    castle->setGold(30);
    castle->setHealth(1000);
    enemies = new QVector<Enemy*>(100);
    towers = new QVector<Tower*>(5);
    timer->start();
}

void MyScene::launchEnemyWaves() {

    waveNumber = 0;
    numberBaseEnemy = 3;
    numberIntermediateEnemy = 1;
    numberDifficultEnemy = 0;

    //interval between each wave incrementation
    connect(&waveIncreaseRate, &QTimer::timeout, [this]() {
        //Upgrade waves stats
        this->waveNumber++;
        numberBaseEnemy *= 0.2 + 1;
        numberIntermediateEnemy *= 0.15 + 1;
        numberDifficultEnemy = waveNumber;
        //do other incrementations

        connect(&spawnRate, &QTimer::timeout, [this](){
            quint32 dice = QRandomGenerator::global()->bounded(20);
            //BASE ENEMY
            if(dice < 10){
                for(int i=0; i < numberBaseEnemy; i++){
                    quint32 internType = QRandomGenerator::global()->bounded(3);
                    quint32 pos = QRandomGenerator::global()->bounded(45);
                    switch (internType) {
                        case 0: {
                            QPixmap skull_bg("../assets/Skeleton.png");
                            Skeleton *skeleton = new Skeleton(skull_bg, this);
                            skeleton->incrementPos(pos);
                            addEnemy(skeleton);
                            break;
                        }
                        case 1: {
                            QPixmap zombie_bg("../assets/Zombie.png");
                            Zombies *zombies = new Zombies(zombie_bg, this);
                            zombies->incrementPos(pos);
                            addEnemy(zombies);
                            break;
                        }
                        case 2: {
                            QPixmap gobelin_bg("../assets/gobelin.png");
                            Gobelin *gobelin = new Gobelin(gobelin_bg, this);
                            gobelin->incrementPos(pos);
                            addEnemy(gobelin);
                            break;
                        }
                    }
                }
            }
            //INTERMEDIATE ENEMY
            if(dice < 16){
                for(int i=0; i < numberIntermediateEnemy; i++){
                    quint32 internType = QRandomGenerator::global()->bounded(4);
                    quint32 pos = QRandomGenerator::global()->bounded(45);
                    switch (internType) {
                        case 0: {
                            QPixmap gargoyle_bg("../assets/gargoyle.png");
                            Gargoyles* gargoyle = new Gargoyles(gargoyle_bg, this);
                            gargoyle->incrementPos(pos);
                            addEnemy(gargoyle);
                            break;
                        }
                        case 1: {
                            QPixmap orc_bg("../assets/orc.png");
                            Orcs* orc = new Orcs(orc_bg, this);
                            orc->incrementPos(pos);
                            addEnemy(orc);
                            break;

                        }
                        case 2: {
                            QPixmap necromancer_bg("../assets/necromancer.png");
                            Necromancer* necromancer = new Necromancer(necromancer_bg, this);
                            necromancer->incrementPos(pos);
                            addEnemy(necromancer);
                            break;
                        }
                        case 3: {
                            QPixmap gouls_bg("../assets/goule.png");
                            Gouls* gouls = new Gouls(gouls_bg, this);
                            gouls->incrementPos(pos);
                            addEnemy(gouls);
                            break;
                        }
                    }
                }
            }
            //DIFFICULT ENEMY
            if(dice < 19){
                for(int i=0; i < numberDifficultEnemy; i++){
                    quint32 internType = QRandomGenerator::global()->bounded(2);
                    quint32 pos = QRandomGenerator::global()->bounded(45);
                    switch (internType) {
                        case 0: {
                            QPixmap mage_bg("../assets/mage.png");
                            Mage* mage = new Mage(mage_bg, this);
                            mage->incrementPos(pos);
                            addEnemy(mage);
                            break;
                        }
                        case 1: {
                            QPixmap commander_bg("../assets/commander.png");
                            Commander* commander = new Commander(commander_bg, this);
                            commander->incrementPos(pos);
                            addEnemy(commander);
                            break;
                        }
                    }
                }
            }
            //THE GREAT MIGHTY FREIXAS
            if(dice == 19){
                QPixmap Freixas_bg("../assets/master_freixas.png");
                Freixas* freixas = new Freixas(Freixas_bg, this);
                addEnemy(freixas);
                std::cout << "The great mighty Freixas have been invoked! " << std::endl;
            }
        });
        waveIncreaseRate.setInterval(30000 + waveNumber*15000); //increase by 15 seconds the time between each wave upgrade
    });
    waveIncreaseRate.start(30000); //every 30seconds increase wave difficulty
    spawnRate.start(10000); //spawn new wave every 10 seconds
}

void MyScene::pauseGame() {
    timer->stop();
    Popup* looseMess = new Popup("Vous avez perdu");
    looseMess->setPos(this->width()/2, this->height()/2);
    addItem(looseMess);
    QTimer* t = new QTimer();
    connect(t, &QTimer::timeout, [this, looseMess, t](){
        delete looseMess;
        delete t;
    });
    t->start(5000);
}






