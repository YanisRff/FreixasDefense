//
// Created by nirin on 5/11/2024.
//

#ifndef PROJETTOWERDEFENSE_TOWER_H
#define PROJETTOWERDEFENSE_TOWER_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include "Enemy.h"
class Enemy;
class MyScene;

class Tower: public QObject, public QGraphicsPixmapItem {
private:
    QPixmap backgroundImage;
    QTimer* attackTimer = nullptr;
    int attackRadius = 500;
    int updateRate = 1000; //in ms
    int numberOfTargets = 1;
    QGraphicsEllipseItem* rangeItem = nullptr;

    float damages = 10;
public:
    Tower(int aR, int uR, int nT, float dmg, QPixmap bI);
    void attackEnemy(Enemy* e);
    void checkEnnemiesInRange();
    [[nodiscard]] MyScene* getScene() const;
};




#endif //PROJETTOWERDEFENSE_TOWER_H
