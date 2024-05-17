//
// Created by nirin on 17/05/2024.
//

#ifndef PROJETTOWERDEFENSE_CASTLE_HPP
#define PROJETTOWERDEFENSE_CASTLE_HPP
#include <QObject>
#include <QGraphicsPixmapItem>
#include "Enemy.h"

class Castle : public QObject, public QGraphicsPixmapItem {
private:
    int gold;
    float health;
public:
    void setGold(int g);
    void setHealth(float hp);
    [[nodiscard]] int getGold() const;
    [[nodiscard]] float getHealth() const;

    void isAttacked(const Enemy* e);
};

#endif //PROJETTOWERDEFENSE_CASTLE_HPP
