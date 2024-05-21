 //
// Created by nirin on 17/05/2024.
//

#ifndef PROJETTOWERDEFENSE_CASTLE_H
#define PROJETTOWERDEFENSE_CASTLE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include "Enemy.h"
#include "MyScene.h"
class Enemy;

class Castle : public QObject, public QGraphicsPixmapItem {
private:
    QPixmap backgroundImage;
    int gold;
    float health;
public:
    Castle(const QPixmap& bI, const QPixmap& sceneBI, float hp, int gD);
    void setGold(int g);
    void setHealth(float hp);
    [[nodiscard]] int getGold() const;
    [[nodiscard]] float getHealth() const;

    public slots:
    void isAttacked(const Enemy* e);
};

#endif //PROJETTOWERDEFENSE_CASTLE_H
