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
#include <QLabel>
#include <QConstOverload>
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

class Popup : public QGraphicsTextItem {
public:
    explicit Popup(const QString& text, QGraphicsItem* parent = nullptr)
            : QGraphicsTextItem(text, parent) {
        setDefaultTextColor(Qt::red);  // Couleur du texte, ajustez selon vos besoins
        setFont(QFont("Arial", 16));   // Police et taille du texte, ajustez selon vos besoins

        // Centrer le texte (facultatif, ajustez selon vos besoins)
        setTextWidth(200);  // Largeur du texte
        QGraphicsTextItem::adjustSize();
        setPos(-boundingRect().width() / 2, -boundingRect().height() / 2);
    }
};

#endif //PROJETTOWERDEFENSE_GAMEWIDGETS_H
