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

class Skeleton : public Enemy{
public:
    explicit Skeleton(QPixmap bI);
    Skeleton(QPixmap bI, MyScene* relativeScene , float hp = 100, float dmg = 10, float spd = 2, int gD = 1);
};

class Zombies : public Enemy{
public:
    explicit Zombies(QPixmap bI);
    Zombies(QPixmap bI, MyScene* relativeScene , float hp = 200, float dmg = 20, float spd = 1, int gD = 2);
};

class Gobelin : public Enemy{
public:
    explicit Gobelin(QPixmap bI);
    Gobelin(QPixmap bI, MyScene* relativeScene , float hp = 50, float dmg = 5, float spd = 3, int gD = 1);
};

class Gargoyles : public Enemy{
public:
    explicit Gargoyles(QPixmap bI);
    Gargoyles(QPixmap bI, MyScene* relativeScene , float hp = 500, float dmg = 50, float spd = 1, int gD = 5);
};

class Orcs : public Enemy{
public:
    explicit Orcs(QPixmap bI);
    Orcs(QPixmap bI, MyScene* relativeScene , float hp = 300, float dmg = 30, float spd = 2, int gD = 3);
};

class Necromancer : public Enemy{
public:
    explicit Necromancer(QPixmap bI);
    Necromancer(QPixmap bI, MyScene* relativeScene , float hp = 200, float dmg = 10, float spd = 2, int gD = 2);
};

class Gouls : public Enemy{
public:
    explicit Gouls(QPixmap bI);
    Gouls(QPixmap bI, MyScene* relativeScene , float hp = 10, float dmg = 5, float spd = 2, int gD = 0);
};

class Mage : public Enemy{
public:
    explicit Mage(QPixmap bI);
    Mage(QPixmap bI, MyScene* relativeScene , float hp = 100, float dmg = 20, float spd = 2, int gD = 2);
};

class Commander : public Enemy{
public:
    explicit Commander(QPixmap bI);
    Commander(QPixmap bI, MyScene* relativeScene , float hp = 500, float dmg = 50, float spd = 2, int gD = 5);
};

class Freixas : public Enemy{
public:
    explicit Freixas(QPixmap bI);
    Freixas(QPixmap bI, MyScene* relativeScene , float hp = 10000, float dmg = 500, float spd = 2, int gD = 100);
};

#endif //PROJETTOWERDEFENSE_ENEMY_H
