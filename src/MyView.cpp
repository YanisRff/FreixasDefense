//
// Created by nirin on 5/8/2024.
//

#include "MyView.h"

void MyView::resizeEvent(QResizeEvent *event) {
    this->fitInView(sceneRect());
}
