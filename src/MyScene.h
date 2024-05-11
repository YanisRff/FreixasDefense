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
#include "Enemy.h"
#include "Towers.h"



class MyScene : public QGraphicsScene {
    Q_OBJECT
private:
    QTimer* timer = nullptr;
    QPixmap* pixBackground = nullptr;
    QVector<Enemy*> *enemies = nullptr;
    QVector<Towers*> *towers = nullptr;
    QGraphicsPathItem* pathItem = nullptr;
    QSharedPointer<QVector<QPointF>> pathPoints = nullptr;

public:
    explicit MyScene(QObject* parent = nullptr, QPixmap* pixBackground = nullptr);
    void drawBackground(QPainter* painter, const QRectF &rect) override;

    [[nodiscard]] QPixmap* getPixBackground() const;
    void setPixBackground(QPixmap* pB);

    void update();
    void moveEnemies();
    void addEnemy(Enemy* e);
    void createPathToScene();
    void createPathPointsToScene();
    virtual ~MyScene();

};



#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
