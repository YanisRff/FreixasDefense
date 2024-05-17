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

    QVector<Enemy*> *enemies = nullptr;
    QVector<Tower*> *towers = nullptr;
    Castle* castle = nullptr;

    QGraphicsPathItem* pathItem = nullptr;
    QSharedPointer<QVector<QPointF>> pathPoints = nullptr;

    //scene widgets
    QGraphicsProxyWidget* towerMenu = addWidget(new TowerMenu());

public:
    explicit MyScene(QObject* parent = nullptr, QPixmap* pixBackground = nullptr);
    void drawBackground(QPainter* painter, const QRectF &rect) override;

    [[nodiscard]] QPixmap* getPixBackground() const;
    [[nodiscard]] QVector<Enemy*>* getEnnemies() const;
    void setPixBackground(QPixmap* pB);

    void update();
    void moveEnemies();
    void addEnemy(Enemy* e);
    void addTower(Tower* t);
    void createPathToScene();
    void createPathPointsToScene();
    virtual ~MyScene();
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    void showTowerMenu(QPointF clickedPos);
    void hideTowerMenu();
    public slots:
    void killEnemy(Enemy* e);

};



#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
