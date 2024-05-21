//
// Created by nirin on 5/17/2024.
//

#ifndef PROJETTOWERDEFENSE_GAMEWIDGETS_H
#define PROJETTOWERDEFENSE_GAMEWIDGETS_H
#include <QWidget>
#include <QButtonGroup>
#include<QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QAbstractButton>
#include "MyScene.h"
class MyScene;

class TowerMenu : public QWidget{
    Q_OBJECT
private:
    QHBoxLayout *layout;
    QButtonGroup *buttonGroup;
public:
    explicit TowerMenu(const MyScene* relativeScene);

};

#endif //PROJETTOWERDEFENSE_GAMEWIDGETS_H
