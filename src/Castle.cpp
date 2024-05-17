//
// Created by nirin on 17/05/2024.
//

#include "Castle.hpp"

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
    health -= e->getDamages();
}