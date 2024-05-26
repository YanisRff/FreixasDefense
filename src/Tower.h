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
    Q_OBJECT
protected:
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
    bool canAttack = false;
    int towerCost = 5;
    int damages = 10;
public:
    Tower(int aR, int cR,int uR, int nT, int dmg, int tC, QPixmap bI);
    ~Tower() override;
    void attackEnemy(Enemy* e);
    void checkEnnemiesInRange();
    bool containsTower(const Tower* t);
    bool containsPath(QGraphicsPathItem* pathItem);
    void hideCollideRange();
    [[nodiscard]] MyScene* getScene() const;
    [[nodiscard]] QPixmap getBackgroundImage() const;
    [[nodiscard]] QPixmap getOriginalBackgroundImage() const;
    [[nodiscard]] bool getIfTowerPlaceable() const;
    [[nodiscard]] int getCost() const;

    void setPlaceableTower(bool b);
    void setAttackTower(bool b);

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;


};

class ClassicTower1: public Tower{
    Q_OBJECT
public:
    ClassicTower1(int aR = 400, int cR = 450,int uR = 1000, int nT = 1, int dmg = 20, int tC = 10, QPixmap bI = QPixmap("../assets/ClassicTower.png"));
};

class ClassicTower2: public Tower{
    Q_OBJECT
public:
    ClassicTower2(int aR = 500, int cR = 550,int uR = 900, int nT = 1, int dmg = 60, int tC = 15, QPixmap bI = QPixmap("../assets/ClassicTower.png"));
};

class ClassicTower3: public Tower{
    Q_OBJECT
public:
    ClassicTower3(int aR = 800, int cR = 850,int uR = 900, int nT = 1, int dmg = 90, int tC = 25, QPixmap bI = QPixmap("../assets/ClassicTower.png"));
};

class TeslaTower1: public Tower{
    Q_OBJECT
public:
    TeslaTower1(int aR = 300, int cR = 410,int uR = 500, int nT = 2, int dmg = 10, int tC = 15, QPixmap bI = QPixmap("../assets/TeslaTower.png"));
};

class TeslaTower2: public Tower{
    Q_OBJECT
public:
    TeslaTower2(int aR = 400, int cR = 510,int uR = 500, int nT = 3, int dmg = 20, int tC = 25, QPixmap bI = QPixmap("../assets/TeslaTower.png"));
};

class TeslaTower3: public Tower{
    Q_OBJECT
public:
    TeslaTower3(int aR = 400, int cR = 510,int uR = 500, int nT = 4, int dmg = 25, int tC = 55, QPixmap bI = QPixmap("../assets/TeslaTower.png"));
};


class CanonTower1: public Tower{
    Q_OBJECT
public:
    CanonTower1(int aR = 250, int cR = 225,int uR = 2500, int nT = 2, int dmg = 40, int tC = 15, QPixmap bI = QPixmap("../assets/CanonTower.png"));
};

class CanonTower2: public Tower{
    Q_OBJECT
public:
    CanonTower2(int aR = 350, int cR = 300,int uR = 2500, int nT = 3, int dmg = 90, int tC = 20, QPixmap bI = QPixmap("../assets/CanonTower.png"));
};

class CanonTower3: public Tower{
    Q_OBJECT
public:
    CanonTower3(int aR = 450, int cR = 400,int uR = 2000, int nT = 3, int dmg = 120, int tC = 30, QPixmap bI = QPixmap("../assets/CanonTower.png"));
};

class CrossbowTower1: public Tower{
    Q_OBJECT
public:
    CrossbowTower1(int aR = 500, int cR = 400,int uR = 2000, int nT = 1, int dmg = 35, int tC = 10, QPixmap bI = QPixmap("../assets/CrossbowTower.png"));
};

class CrossbowTower2: public Tower{
    Q_OBJECT
public:
    CrossbowTower2(int aR = 600, int cR = 450,int uR = 1750, int nT = 1, int dmg = 90, int tC = 20, QPixmap bI = QPixmap("../assets/CrossbowTower.png"));
};

class CrossbowTower3: public Tower{
    Q_OBJECT
public:
    CrossbowTower3(int aR = 650, int cR = 500,int uR = 1500, int nT = 1, int dmg = 110, int tC = 40, QPixmap bI = QPixmap("../assets/CrossbowTower.png"));
};





#endif //PROJETTOWERDEFENSE_TOWER_H
