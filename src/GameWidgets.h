//
// Created by nirin on 5/17/2024.
//

#ifndef PROJETTOWERDEFENSE_GAMEWIDGETS_H
#define PROJETTOWERDEFENSE_GAMEWIDGETS_H
#include <QWidget>
#include <QButtonGroup>
#include<QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QAbstractButton>
#include <QProgressBar>
#include <QGraphicsLinearLayout>
#include <QLabel>
#include "MyScene.h"
class MyScene;

class TowerMenu : public QWidget{
    Q_OBJECT
private:
    QGridLayout *layout;
    QButtonGroup *buttonGroup;
    QVector<QPushButton*> buttonArray = QVector<QPushButton*>(10);
public:
    explicit TowerMenu(const MyScene* relativeScene);
    void addButtonToPanel(const QString& buttonName, int row, int column, const MyScene* relativeScene); //remember, buttonName = the name of the tower to construct !

};

class HealthBar : public QGraphicsWidget{
    Q_OBJECT
private:
    QProgressBar* progressBar;
    QLabel* label = nullptr;
    QGraphicsLinearLayout *layout = nullptr;
public:
    explicit HealthBar(QGraphicsItem* parent = nullptr, float health = 100);
    ~HealthBar();
    void setBarColor();
    [[nodiscard]] QProgressBar* getProgressBar();
    void setValue(float hp);
    void addToLayout(QGraphicsProxyWidget* w);
    void setLabel(QLabel* l);
};

class GoldWidget : public QGraphicsWidget {
Q_OBJECT

public:
    explicit GoldWidget(const QString &imagePath, const QString &text, QGraphicsItem *parent = nullptr);
    void setText(const QString &newText);

private:
    QLabel *imageLabel;
    QLabel *textLabel;
    QWidget *containerWidget;
    QGraphicsProxyWidget *proxyWidget;
};

#endif //PROJETTOWERDEFENSE_GAMEWIDGETS_H
