//
// Created by nirin on 5/11/2024.
//

#include "Tower.h"

Tower::Tower(int aR, int cR,int uR, int nT, int dmg, int tC,  QPixmap bI) : originalBackgroundImage(bI), backgroundImage(bI), attackRadius(aR), collideRadius(cR),updateRate(uR), numberOfTargets(nT), damages(dmg), towerCost(tC) {
    setPixmap(backgroundImage);
    attackTimer =  new QTimer();
    attackTimer->start(updateRate);
    rangeItem = new QGraphicsEllipseItem(-attackRadius/2 + this->pixmap().width()/2,  -attackRadius/2 +this->pixmap().height()/2, attackRadius, attackRadius, this);
    collideItem = new QGraphicsEllipseItem(-collideRadius/2 + this->pixmap().width()/2,  -collideRadius/2 +this->pixmap().height()/2, collideRadius, collideRadius, this);

    // Définir la bordure rouge
    QPen pen(Qt::red);
    pen.setWidth(2);
    collideItem->setPen(pen);

    connect(attackTimer, &QTimer::timeout, this, &Tower::checkEnnemiesInRange);
}
Tower::~Tower(){
    MyScene* relativeScene = this->getScene();
    relativeScene->removeItem(this);
    delete rangeItem;
    delete collideItem;
    disconnect(attackTimer, &QTimer::timeout, this, &Tower::checkEnnemiesInRange);
    delete attackTimer;
}

MyScene* Tower::getScene() const {
    QGraphicsScene* tempScene =  this->scene();
    if(tempScene == nullptr){
        qDebug() << "Dynamic cast to MyScene failed in Tower";
    }
    return dynamic_cast<MyScene*>(tempScene);
}

void Tower::attackEnemy(Enemy* e) {
    e->setHealth(e->getHealth() - damages);
    if(e->getHealth() <= 0){
        emit e->enemyKilled(e);
    }
    std::cout << "New health of " << e << ": " << e->getHealth() << std::endl;
}

void Tower::checkEnnemiesInRange() {
    if(!canAttack){
        return;
    }
    QVector<Enemy*>* ennemies = this->getScene()->getEnnemies();
    int targetedEnnemies = 0;
    for(auto& enemy: *ennemies){
        if(enemy != nullptr &&  targetedEnnemies != numberOfTargets && enemy->getHealth() > 0){
            if(rangeItem->contains(mapFromScene(enemy->sceneBoundingRect().center()))){ //check if enemy is in range. Moreover, as ennemies will not be removed from the QVector ennemies but on ly hidden, it checks if the enemy is still alive<=>visible before attacking it
                attackEnemy(enemy);
                targetedEnnemies += 1;
            }
        }
    }
}

bool Tower::containsTower(const Tower *t) {
    if(t == nullptr){
        return false;
    }
    QRectF rect = t->sceneBoundingRect();
    QPointF corners[4] = {
            rect.topLeft(),
            rect.topRight(),
            rect.bottomLeft(),
            rect.bottomRight()
    };
    for(auto corner : corners){
        if(collideItem->contains(mapFromScene(corner))){
            return true;
        }
    }
    return false;
}

bool Tower::containsPath(QGraphicsPathItem* pathItem) {
    return collideItem->collidesWithItem(pathItem);
}

void Tower::hideCollideRange() {
    collideItem->hide();
}

QPixmap Tower::getBackgroundImage() const{
    return backgroundImage;
}

QPixmap Tower::getOriginalBackgroundImage() const {
    return originalBackgroundImage;
}

void Tower::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    rangeItem->show();
}

void Tower::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    rangeItem->hide();
}

void Tower::setPlaceableTower(bool b) {
    isPlaceable = b;
}
void Tower::setAttackTower(bool b) {
    canAttack = b;
}

bool Tower::getIfTowerPlaceable() const {
    return isPlaceable;
}

int Tower::getCost() const {
    return towerCost;
}



ClassicTower1::ClassicTower1(int aR, int cR, int uR, int nT, int dmg, int tC, QPixmap bI) : Tower(aR, cR, uR, nT, dmg, tC, bI) {}

ClassicTower2::ClassicTower2(int aR, int cR, int uR, int nT, int dmg, int tC, QPixmap bI) : Tower(aR, cR, uR, nT, dmg, tC, bI) {}

ClassicTower3::ClassicTower3(int aR, int cR, int uR, int nT, int dmg, int tC, QPixmap bI) : Tower(aR, cR, uR, nT, dmg, tC, bI) {}

TeslaTower1::TeslaTower1(int aR, int cR, int uR, int nT, int dmg, int tC, QPixmap bI) : Tower(aR, cR, uR, nT, dmg, tC, bI) {}

TeslaTower2::TeslaTower2(int aR, int cR, int uR, int nT, int dmg, int tC, QPixmap bI) : Tower(aR, cR, uR, nT, dmg, tC, bI) {}

TeslaTower3::TeslaTower3(int aR, int cR, int uR, int nT, int dmg, int tC, QPixmap bI) : Tower(aR, cR, uR, nT, dmg, tC, bI) {}

CanonTower1::CanonTower1(int aR, int cR, int uR, int nT, int dmg, int tC, QPixmap bI) : Tower(aR, cR, uR, nT, dmg, tC, bI) {}

CanonTower2::CanonTower2(int aR, int cR, int uR, int nT, int dmg, int tC, QPixmap bI) : Tower(aR, cR, uR, nT, dmg, tC, bI) {}

CanonTower3::CanonTower3(int aR, int cR, int uR, int nT, int dmg, int tC, QPixmap bI) : Tower(aR, cR, uR, nT, dmg, tC, bI) {}

CrossbowTower1::CrossbowTower1(int aR, int cR, int uR, int nT, int dmg, int tC, QPixmap bI) : Tower(aR, cR, uR, nT, dmg, tC, bI) {}

CrossbowTower2::CrossbowTower2(int aR, int cR, int uR, int nT, int dmg, int tC, QPixmap bI) : Tower(aR, cR, uR, nT, dmg, tC, bI) {}

CrossbowTower3::CrossbowTower3(int aR, int cR, int uR, int nT, int dmg, int tC, QPixmap bI) : Tower(aR, cR, uR, nT, dmg, tC, bI) {}

