//
// Created by nirin on 5/17/2024.
//

#include "GameWidgets.h"

TowerMenu::TowerMenu() {
    layout = new QHBoxLayout(this);
    buttonGroup = new QButtonGroup(this);
    setLayout(layout);

    QPushButton* towerOne = new QPushButton("towerOne", this);
    QPushButton* towerTwo = new QPushButton("towerTwo", this);
    buttonGroup->addButton(towerOne);
    buttonGroup->addButton(towerTwo);
    layout->addWidget(towerOne);
    layout->addWidget(towerTwo);
    //connect(buttonGroup, &QButtonGroup::buttonClicked, //connect the buttonClicked event to the function that place a tower
}

//All the slots

