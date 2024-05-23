#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H
#include <iostream>
#include <QPointF>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QColor>
#include <QThread>
#include "Enemy.h"
#include "Tower.h"  
#include "Castle.h"
#include "GameWidgets.h"

class Enemy;
class Tower;
class Castle;


class MyScene : public QGraphicsScene{
    Q_OBJECT
private:
    QTimer* timer = nullptr;
    QPixmap* pixBackground = nullptr;

    QVector<Enemy*> *enemies = nullptr;     //keep track of the ennemies on scene
    QVector<Tower*> *towers = nullptr;  //keep track of the tower on scene
    Castle* castle = nullptr;

    QGraphicsPathItem* pathItem = nullptr;  //graphic item showed in scene to represent the ennemies path
    QSharedPointer<QVector<QPointF>> pathPoints = nullptr; //points that ennemies will follow

    //scene widgets
    QGraphicsProxyWidget* towerMenu = nullptr;


    QPointF mousePos;   //Keep track of the mouse position
    bool hasLeftClicked = false; //Keep track of the last left mouse click

    QTimer waveIncreaseRate;
    QTimer spawnRate;
    int waveNumber = 0;
    int numberBaseEnemy = 3;
    int numberIntermediateEnemy = 1;
    int numberDifficultEnemy = 0;

public:
    explicit MyScene(QObject* parent = nullptr, QPixmap* pixBackground = nullptr);
    ~MyScene() override;
    void drawBackground(QPainter* painter, const QRectF &rect) override;

    [[nodiscard]] QPixmap* getPixBackground() const;
    [[nodiscard]] QVector<Enemy*>* getEnnemies() const;
    [[nodiscard]] Castle* getCastle() const;
    void setPixBackground(QPixmap* pB);

    void update();
    void moveEnemies();
    void addEnemy(Enemy* e);
    void removeEnemy(Enemy* e);
    void addTower(Tower* t);
    void createPathToScene();
    void createPathPointsToScene();
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void showTowerMenu(QPointF clickedPos);
    void hideTowerMenu();
    bool doesTowerCollideWithAnother(Tower *t);

    static void fadeToRedPixmap(Tower* t);
    static void restoreOriginalBackground(Tower* t);
    void tryTowerPlacement(Tower* t, QPointF);


    public slots:
    void killEnemy(Enemy* e);
    void spawnTowerOnScene(QAbstractButton* button);
    void restartGame();



};



#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
