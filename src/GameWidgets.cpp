//
// Created by nirin on 5/17/2024.
//

#include "GameWidgets.h"


TowerMenu::TowerMenu(const MyScene* relativeScene) {
    layout = new QHBoxLayout(this);
    buttonGroup = new QButtonGroup(this);
    setLayout(layout);

    addButtonToPanel("towerOne", relativeScene);
    addButtonToPanel("towerTwo", relativeScene);

}

void TowerMenu::addButtonToPanel(const QString& buttonName, const MyScene* relativeScene) {
    QPushButton* tower = new QPushButton(buttonName, this);
    tower->setEnabled(true);
    tower->resize(100, 100);
    buttonGroup->addButton(tower);
    buttonArray.append(tower);
    layout->addWidget(tower);
    connect(buttonGroup, &QButtonGroup::buttonPressed, relativeScene, &MyScene::spawnTowerOnScene); //connect the buttonClicked event to the function that place a tower
}

HealthBar::HealthBar(QGraphicsItem* parent, float health) : QGraphicsWidget(parent) {
    progressBar = new QProgressBar();
    progressBar->setMaximum(health);
    progressBar->setMinimum(0);
    progressBar->setValue(health);
    progressBar->setTextVisible(false);
    progressBar->setGeometry(0, 0, 10, 5);
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout();
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(progressBar);
    layout->addItem(proxy);
    setLayout(layout);
}
HealthBar::~HealthBar(){
    delete progressBar;
}

void HealthBar::setBarColor() {
    int value = progressBar->value();
    QString color;

    if (value > 0.5*progressBar->maximum()) {
        color = "green";
    } else if (value > 0.25*progressBar->maximum()) {
        color = "yellow";
    } else {
        color = "red";
    }
    QString styleSheet = QString("QProgressBar::chunk { background: %1; }").arg(color);
    progressBar->setStyleSheet(styleSheet);
}

QProgressBar *HealthBar::getProgressBar() {
    return progressBar;
}

void HealthBar::setValue(float hp) {
    progressBar->setValue(hp);
    setBarColor();
}



//All the slots

