#include "MyScene.h"

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent) {
    pixBackground = nullptr;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MyScene::update);
    timer->start(30); ///30 milliseconds

    //add image to the scene
    QPixmap bqtpm("../assets/st.png");
    qtpm = new QGraphicsPixmapItem(bqtpm);
    addItem(qtpm);
}

MyScene::~MyScene() {

}

void MyScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QPointF(0, 0), *pixBackground, sceneRect());
    // pixBackgroud est un attribut de type QPixmap qui contient l’image de fond
}

QPixmap *MyScene::getPixBackground() const {
    return pixBackground;
}

void MyScene::setPixBackground(QPixmap *pB) {
    pixBackground = pB;
}

void MyScene::update() {
    QPointF pos = qtpm->pos();
    std::cout << "x:" << pos.rx() << " y:" << pos.ry() << "\n";
    qtpm->setPos(pos.rx()+1, pos.ry()+1);
}
