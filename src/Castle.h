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
#include "GameWidgets.h"
class Enemy;
class GoldWidget;

class Castle : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
private:
    QPixmap backgroundImage;
    int gold;
    float health;
    HealthBar* healthBar = nullptr;
    GoldWidget* goldWidget = nullptr;
public:
    Castle(const QPixmap& bI, const QPixmap& sceneBI, float hp, int gD, MyScene* relativeScene);
    void setGold(int g);
    void setHealth(float hp);
    [[nodiscard]] int getGold() const;
    [[nodiscard]] float getHealth() const;

    public slots:
    void isAttacked(const Enemy* e);
    signals:
    void gameLost();
};

#endif //PROJETTOWERDEFENSE_CASTLE_H
