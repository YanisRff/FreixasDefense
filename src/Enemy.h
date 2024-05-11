//
// Created by nirin on 5/9/2024.
//

#ifndef PROJETTOWERDEFENSE_ENEMY_H
#define PROJETTOWERDEFENSE_ENEMY_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QSharedPointer>

class Enemy : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
private:
    QPixmap backgroundImage;
    float health = 80;
    float damages = 10;
    float speed = 1;
    int goldDropped = 10;
    int posInPath = 0;
public:
    explicit Enemy(QPixmap bI);
    Enemy(QPixmap bI, float hp, float dmg, float spd, int gD);
    void moveAlongPath(const QSharedPointer<QVector<QPointF>>& pathPoints);

    void incrementPos();
    [[nodiscard]] int getPosInPath() const;
};

#endif //PROJETTOWERDEFENSE_ENEMY_H
