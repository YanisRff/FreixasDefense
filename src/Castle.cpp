//
// Created by nirin on 17/05/2024.
//

#include "Castle.h"

Castle::Castle(const QPixmap& bI, const QPixmap& sceneBI, float hp, int gD, MyScene* relativeScene) : backgroundImage(bI), health(hp), gold(gD) {
    setPixmap(bI);
    setPos(sceneBI.width() - bI.width()/2 - 15, sceneBI.height()/2 - bI.height()/2);
    healthBar = new HealthBar(this, hp);
    healthBar->setPos(sceneBI.width()/2 - 1000/2, 20);
    healthBar->getProgressBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    healthBar->setMinimumWidth(1000);
    healthBar->setMinimumHeight(50);
    healthBar->getProgressBar()->setTextVisible(true);

    QLabel* pLabel = new QLabel("HP Château");
    pLabel->setAlignment(Qt::AlignCenter);
    QGraphicsProxyWidget *labelProxy = new QGraphicsProxyWidget(this);
    labelProxy->setWidget(pLabel);
    healthBar->addToLayout(labelProxy);

    goldWidget = new GoldWidget("../assets/gold.png", "Or: " + QString::number(gD), this);

    relativeScene->addItem(healthBar);
    relativeScene->addItem(goldWidget);
    connect(this, &Castle::castleKilled, relativeScene, &MyScene::pauseGame);
}

void Castle::setHealth(float hp) {
    health = hp;
    healthBar->setValue(health);
}
void Castle::setGold(int g){
    gold = g;
    goldWidget->setText("Or: " + QString::number(g));
}
float Castle::getHealth() const {
    return health;
}
int Castle::getGold() const {
    return gold;
}
void Castle::isAttacked(const Enemy *e) {
    std::cout << "Caste attacked" << std::endl;
    health -= e->getDamages();
    healthBar->setValue(health);
    gold -= e->getDroppedGold();
    if(health <= 0){ //player lost
        healthBar->setValue(0);
        emit castleKilled();
    }
    std::cout << "Caste attacked, new health : " << health << std::endl;
}
