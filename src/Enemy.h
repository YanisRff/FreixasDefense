//
// Created by nirin on 5/9/2024.
//

#ifndef PROJETTOWERDEFENSE_ENEMY_H
#define PROJETTOWERDEFENSE_ENEMY_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QSharedPointer>
#include "MyScene.h"
class MyScene;

class Enemy : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
protected:
    QPixmap backgroundImage;
    float health = 80;
    float damages = 10;
    int speed = 1;
    int goldDropped = 10;
    int posInPath = 0;
public:
    explicit Enemy(QPixmap bI);
    Enemy(QPixmap bI, MyScene* relativeScene , float hp, float dmg, float spd, int gD);
    ~Enemy() override;

    void moveAlongPath(const QSharedPointer<QVector<QPointF>>& pathPoints);
    void incrementPos();

    [[nodiscard]] int getPosInPath() const;
    [[nodiscard]] MyScene* getScene() const;
    [[nodiscard]] float getHealth() const;
    [[nodiscard]] float getDamages() const;
    [[nodiscard]] int getDroppedGold() const;
    void setHealth(float hp);

public :signals:
    void enemyKilled(Enemy* e);
    void castleAttacked(const Enemy* e);

};


#endif //PROJETTOWERDEFENSE_ENEMY_H
