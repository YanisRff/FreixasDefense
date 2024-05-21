//
// Created by nirin on 5/17/2024.
//

#include "GameWidgets.h"


TowerMenu::TowerMenu(const MyScene* relativeScene){
    layout = new QHBoxLayout(this);
    buttonGroup = new QButtonGroup(this);
    setLayout(layout);

    QPushButton* towerOne = new QPushButton("towerOne", this);
    towerOne->setEnabled(true);
    QPushButton* towerTwo = new QPushButton("towerTwo", this);
    towerOne->resize(100, 100);
    buttonGroup->addButton(towerOne, 1);
    buttonGroup->addButton(towerTwo, 2);
    layout->addWidget(towerOne);
    layout->addWidget(towerTwo);
    connect(buttonGroup, &QButtonGroup::buttonPressed, relativeScene, &MyScene::spawnTowerOnScene); //connect the buttonClicked event to the function that place a tower
}

//All the slots

