//
// Created by nirin on 5/8/2024.
//

#ifndef PROJETTOWERDEFENSE_MYVIEW_H
#define PROJETTOWERDEFENSE_MYVIEW_H
#include <QGraphicsView>

class MyView : public QGraphicsView {
protected:
    virtual void resizeEvent(QResizeEvent* event);
};

#endif //PROJETTOWERDEFENSE_MYVIEW_H
