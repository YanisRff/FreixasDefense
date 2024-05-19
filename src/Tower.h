//
// Created by nirin on 5/11/2024.
//

#ifndef PROJETTOWERDEFENSE_TOWER_H
#define PROJETTOWERDEFENSE_TOWER_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QVector>
#include "Enemy.h"
class Enemy;
class MyScene;

class Tower: public QObject, public QGraphicsPixmapItem {
private:
    QPixmap backgroundImage;
    QPixmap originalBackgroundImage;
    QTimer* attackTimer = nullptr;
    int attackRadius = 500;
    int collideRadius = 500;
    int updateRate = 1000; //in ms
    int numberOfTargets = 1;
    QGraphicsEllipseItem* collideItem = nullptr;
    QGraphicsEllipseItem* rangeItem = nullptr;
    bool isPlaceable = true;

    float damages = 10;
public:
    Tower(int aR, int cR,int uR, int nT, float dmg, QPixmap bI);
    ~Tower();
    void attackEnemy(Enemy* e);
    void checkEnnemiesInRange();
    bool containsTower(const Tower* t);
    [[nodiscard]] MyScene* getScene() const;
    [[nodiscard]] QPixmap getBackgroundImage() const;
    [[nodiscard]] QPixmap getOriginalBackgroundImage() const;
    [[nodiscard]] bool getIfTowerPlaceable() const;

    void setPlaceableTower(bool b);

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
};




#endif //PROJETTOWERDEFENSE_TOWER_H
