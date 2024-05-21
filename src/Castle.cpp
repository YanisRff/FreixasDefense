//
// Created by nirin on 17/05/2024.
//

#include "Castle.h"

Castle::Castle(const QPixmap& bI, const QPixmap& sceneBI, float hp, int gD) : backgroundImage(bI), health(hp), gold(gD) {
    setPixmap(bI);
    setPos(sceneBI.width() - bI.width()/2, sceneBI.height()/2 - bI.height()/2);
}

void Castle::setHealth(float hp) {
    health = hp;
}
void Castle::setGold(int g){
    gold = g;
}
float Castle::getHealth() const {
    return health;
}
int Castle::getGold() const {
    return gold;
}
void Castle::isAttacked(const Enemy *e) {
    std::cout << "Caste attacked" << std::endl;
    health -= e->getDamages();
    std::cout << "Caste attacked, new health : " << health << std::endl;
}
