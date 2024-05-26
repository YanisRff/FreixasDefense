//
// Created by nirin on 5/8/2024.
//

#ifndef PROJETTOWERDEFENSE_MYVIEW_H
#define PROJETTOWERDEFENSE_MYVIEW_H
#include <QGraphicsView>
#include "QKeyEvent"
#include "MyScene.h"
#include <QWheelEvent>
#include <iostream>
#include <QTimeLine>
#include <QScrollBar>


class MyView : public QGraphicsView{
    Q_OBJECT
private:
    bool blockResizeEvent = false;
    int dx = 20;
    int dy = 10;
    qreal scale_factor_in = 1.15;
protected:
    virtual void resizeEvent(QResizeEvent* event);
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

};

#endif //PROJETTOWERDEFENSE_MYVIEW_H
