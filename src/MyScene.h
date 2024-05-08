#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H
#include <iostream>
#include <QPointF>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include <QGraphicsPixmapItem>


class MyScene : public QGraphicsScene {
    Q_OBJECT
private:
    QTimer* timer = nullptr;
    QPixmap* pixBackground = nullptr;
    QGraphicsPixmapItem* qtpm = nullptr;

public:
    MyScene(QObject* parent = nullptr);
    void drawBackground(QPainter* painter, const QRectF &rect);
    QPixmap* getPixBackground() const;
    void setPixBackground(QPixmap* pB);

    void update();
    virtual ~MyScene();

};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
