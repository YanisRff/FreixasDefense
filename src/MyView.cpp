//
// Created by nirin on 5/8/2024.
//
//
#include "MyView.h"

void MyView::resizeEvent(QResizeEvent *event) {
   //this->fitInView(sceneRect()); //block the zooming and translating functionnalities
}

void MyView::keyPressEvent(QKeyEvent *event) {
    switch(event->key()){
        case Qt::Key_Left:
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - dx);
            break;
        case Qt::Key_Right:
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() + dx);
            break;
        case Qt::Key_Up:
            verticalScrollBar()->setValue(verticalScrollBar()->value() - dy);
            break;
        case Qt::Key_Down:
            verticalScrollBar()->setValue(verticalScrollBar()->value() + dy);
            break;
        case Qt::Key_R:
            this->fitInView(QGraphicsView::sceneRect()); //error here
            break;
        case Qt::Key_S:
            MyScene* relativeScene = dynamic_cast<MyScene*>(scene());
            printf("Key S pressed\n");
            printf("Mouse Pos : %f, %f\n", relativeScene->mousePos.rx(), relativeScene->mousePos.ry());
            for(auto& tower : *relativeScene->towers){
                if(tower != nullptr && (tower->pos().rx()-100 <= relativeScene->mousePos.rx() <= tower->pos().rx() + 100) && (tower->pos().ry() - 100 <= relativeScene->mousePos.ry() <= tower->pos().ry() + 100)){
                    printf("Tower at %f, %f\n", tower->pos().rx(), tower->pos().ry());
                    relativeScene->removeTower(tower);
                    break;
                }
            }
            break;

    }
}

void MyView::wheelEvent(QWheelEvent* event)
{
    setTransformationAnchor(AnchorUnderMouse);
    if(event->angleDelta().y() > 0){
        scale(scale_factor_in, scale_factor_in);
    }
    else{
        scale(1/scale_factor_in, 1/scale_factor_in);
    }
}


