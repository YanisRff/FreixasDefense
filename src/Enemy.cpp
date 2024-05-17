//
// Created by nirin on 5/9/2024.
//

#include "Enemy.h"
#include <utility>

Enemy::Enemy(QPixmap bI, float hp, float dmg, float spd, int gD) : backgroundImage(std::move(bI)), health(hp), damages(dmg), speed(spd), goldDropped(gD), posInPath(0) {
    setPixmap(backgroundImage);
}

void Enemy::incrementPos() {
    posInPath += 1*speed;
}

void Enemy::moveAlongPath(const QSharedPointer<QVector<QPointF>>& pathPoints) {
    if(this->getPosInPath() == pathPoints->size() - 1){ //enemy touched the base
        emit enemyKilled(this);
        emit castleAttacked(this);
    }
    QPointF newPos = pathPoints->data()[this->getPosInPath()]; // data() get the raw pointer encapsulated to the QVector
    this->setPos(newPos.rx() +  - this->boundingRect().width()/2, newPos.ry() - this->boundingRect().height()/2); //correct the translation center from the top left corner to the center of the image
    this->incrementPos();
}

Enemy::Enemy(QPixmap bI) : backgroundImage(std::move(bI)){
    setPixmap(backgroundImage);
}

///All the getters
MyScene *Enemy::getScene() const {
    QGraphicsScene* tempScene =  this->scene();
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
}






