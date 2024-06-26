//
// Created by nirin on 5/9/2024.
//

#include "Enemy.h"

Enemy::Enemy(QPixmap bI, MyScene* relativeScene ,float hp, float dmg, float spd, int gD) : backgroundImage(std::move(bI)), health(hp), damages(dmg), speed(spd), goldDropped(gD), posInPath(0) {
    setPixmap(backgroundImage);
    healthBar = new HealthBar(this, hp);
    relativeScene->addItem(healthBar);
    connect(this, &Enemy::castleAttacked, relativeScene->getCastle(), &Castle::isAttacked);
    connect(this, &Enemy::enemyKilled, relativeScene, &MyScene::killEnemy);
}
Enemy::~Enemy(){
    MyScene* relativeScene = this->getScene();
    relativeScene->removeItem(this);
    relativeScene->removeItem(healthBar);
    delete healthBar;
    disconnect(this, &Enemy::castleAttacked, relativeScene->getCastle(), &Castle::isAttacked);
    disconnect(this, &Enemy::enemyKilled, relativeScene, &MyScene::killEnemy);
}


void Enemy::incrementPos(int step) {
    if(step == 0){
        posInPath += 1*speed;
    }
    else posInPath += step;
}

void Enemy::moveAlongPath(const QSharedPointer<QVector<QPointF>>& pathPoints) {
    if(this->getPosInPath() >= pathPoints->size()){ //enemy touched the base
        emit castleAttacked(this);
        emit enemyKilled(this);
        return;
    }
    QPointF newPos = pathPoints->data()[this->getPosInPath()]; // data() get the raw pointer encapsulated to the QVector
    this->setPos(newPos.rx() +  - this->boundingRect().width()/2, newPos.ry() - this->boundingRect().height()/2); //correct the translation center from the top left corner to the center of the image
    healthBar->setPos(newPos.rx()   - this->boundingRect().width()/2, newPos.ry() - this->boundingRect().height()/2);
    this->incrementPos();
}

Enemy::Enemy(QPixmap bI) : backgroundImage(std::move(bI)){
    setPixmap(backgroundImage);
}

///All the getters
MyScene *Enemy::getScene() const {
    QGraphicsScene* tempScene =  this->scene();
    if(tempScene == nullptr){
        qDebug() << "Dynamic cast to MyScene failed in Enemy";
    }
    return dynamic_cast<MyScene*>(tempScene);
}
int Enemy::getPosInPath() const {
    return posInPath;
}
float Enemy::getHealth() const {
    return health;
}
float Enemy::getDamages() const {
    return damages;
}
int Enemy::getDroppedGold() const {
    return goldDropped;
}

//All the setters
void Enemy::setHealth(float hp) {
    health = hp;
    healthBar->setValue(hp);
}

//Enemy
Skeleton::Skeleton(QPixmap bI) : Enemy(std::move(bI)) {}
Skeleton::Skeleton(QPixmap bI, MyScene* relativeScene, float hp, float dmg, float spd, int gD) : Enemy(std::move(bI), relativeScene, hp, dmg, spd, gD) {}

Zombies::Zombies(QPixmap bI) : Enemy(std::move(bI)) {}
Zombies::Zombies(QPixmap bI, MyScene* relativeScene, float hp, float dmg, float spd, int gD) : Enemy(std::move(bI), relativeScene, hp, dmg, spd, gD) {}

Gobelin::Gobelin(QPixmap bI) : Enemy(std::move(bI)) {}
Gobelin::Gobelin(QPixmap bI, MyScene* relativeScene, float hp, float dmg, float spd, int gD) : Enemy(std::move(bI), relativeScene, hp, dmg, spd, gD) {}

Gargoyles::Gargoyles(QPixmap bI) : Enemy(std::move(bI)) {}
Gargoyles::Gargoyles(QPixmap bI, MyScene* relativeScene, float hp, float dmg, float spd, int gD) : Enemy(std::move(bI), relativeScene, hp, dmg, spd, gD) {}

Orcs::Orcs(QPixmap bI) : Enemy(std::move(bI)) {}
Orcs::Orcs(QPixmap bI, MyScene* relativeScene, float hp, float dmg, float spd, int gD) : Enemy(std::move(bI), relativeScene, hp, dmg, spd, gD) {}

Necromancer::Necromancer(QPixmap bI) : Enemy(std::move(bI)) {}
Necromancer::Necromancer(QPixmap bI, MyScene* relativeScene, float hp, float dmg, float spd, int gD) : Enemy(std::move(bI), relativeScene, hp, dmg, spd, gD) {}

Gouls::Gouls(QPixmap bI) : Enemy(std::move(bI)) {}
Gouls::Gouls(QPixmap bI, MyScene* relativeScene, float hp, float dmg, float spd, int gD) : Enemy(std::move(bI), relativeScene, hp, dmg, spd, gD) {}

Mage::Mage(QPixmap bI) : Enemy(std::move(bI)) {}
Mage::Mage(QPixmap bI, MyScene* relativeScene, float hp, float dmg, float spd, int gD) : Enemy(std::move(bI), relativeScene, hp, dmg, spd, gD) {}

Commander::Commander(QPixmap bI) : Enemy(std::move(bI)) {}
Commander::Commander(QPixmap bI, MyScene* relativeScene, float hp, float dmg, float spd, int gD) : Enemy(std::move(bI), relativeScene, hp, dmg, spd, gD) {}

Freixas::Freixas(QPixmap bI) : Enemy(std::move(bI)) {}
Freixas::Freixas(QPixmap bI, MyScene* relativeScene, float hp, float dmg, float spd, int gD) : Enemy(std::move(bI), relativeScene, hp, dmg, spd, gD) {}



