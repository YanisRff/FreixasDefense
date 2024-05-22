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
#include <QProgressBar>
#include <QGraphicsLinearLayout>
#include "MyScene.h"
class MyScene;

class TowerMenu : public QWidget{
    Q_OBJECT
private:
    QHBoxLayout *layout;
    QButtonGroup *buttonGroup;
    QVector<QPushButton*> buttonArray = QVector<QPushButton*>(10);
public:
    explicit TowerMenu(const MyScene* relativeScene);
    void addButtonToPanel(const QString& buttonName, const MyScene* relativeScene); //remember, buttonName = the name of the tower to construct !

};

class HealthBar : public QGraphicsWidget{
private:
    QProgressBar* progressBar;
public:
    explicit HealthBar(QGraphicsItem* parent = nullptr, float health = 100);
    ~HealthBar();
    void setBarColor();
    [[nodiscard]] QProgressBar* getProgressBar();
    void setValue(float hp);
};

#endif //PROJETTOWERDEFENSE_GAMEWIDGETS_H
