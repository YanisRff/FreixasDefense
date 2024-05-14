//
// Created by nirin on 5/11/2024.
//

#include "Tower.h"

Tower::Tower(QPixmap bI) : backgroundImage(bI){
    setPixmap(backgroundImage);
    rangeItem = new QGraphicsEllipseItem(0, 0, rangeDiameter, rangeDiameter, this);
}

Tower::Tower(int rD, int uR, int nT) : rangeDiameter(rD), updateRate(uR), numberOfTargets(nT) {
    QTimer* timer = new QTimer();
    timer->start(updateRate);
    connect(timer, &QTimer::timeout, this, &Tower::checkEnnemiesInRange);
    rangeItem = new QGraphicsEllipseItem(0, 0, rangeDiameter, rangeDiameter, this); //child of visible QGraphicsItem are also shown in scene. So this range is visible.
    rangeItem->setPos(this->pos().rx() - this->boundingRect().width()/2, this->pos().ry() - this->boundingRect().height()/2);
}

MyScene* Tower::getScene() const {
    QGraphicsScene* tempScene =  this->scene();
    return dynamic_cast<MyScene*>(tempScene);
}

void Tower::attackEnemy(Enemy* e) {

}

void Tower::checkEnnemiesInRange() {
    QVector<Enemy*>* ennemies = this->getScene()->getEnnemies();
    int targetedEnnemies = 0;
    for(auto& enemy: *ennemies){
        if(targetedEnnemies == numberOfTargets){
            return;
        }

        if(rangeItem->contains(enemy->pos())){
            attackEnemy(enemy);
            targetedEnnemies += 1;
        }
    }
}

