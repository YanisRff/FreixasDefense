//
// Created by nirin on 5/11/2024.
//

#include "Tower.h"

Tower::Tower(int aR, int uR, int nT, float dmg,  QPixmap bI) : backgroundImage(bI), attackRadius(aR), updateRate(uR), numberOfTargets(nT), damages(dmg) {
    setPixmap(backgroundImage);
    attackTimer =  new QTimer();
    attackTimer->start(updateRate);
    rangeItem = new QGraphicsEllipseItem(-attackRadius/2 + this->pixmap().width()/2,  -attackRadius/2 +this->pixmap().height()/2, attackRadius, attackRadius, this);
    connect(attackTimer, &QTimer::timeout, this, &Tower::checkEnnemiesInRange);

}

MyScene* Tower::getScene() const {
    QGraphicsScene* tempScene =  this->scene();
    return dynamic_cast<MyScene*>(tempScene);
}

void Tower::attackEnemy(Enemy* e) {
    e->setHealth(e->getHealth() - damages);
    std::cout << "New health of " << e << ": " << e->getHealth() << std::endl;
}

void Tower::checkEnnemiesInRange() {
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


