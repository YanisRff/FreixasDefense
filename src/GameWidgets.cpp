//
// Created by nirin on 5/17/2024.
//

#include "GameWidgets.h"


TowerMenu::TowerMenu(const MyScene* relativeScene) {
    layout = new QGridLayout(this);
    buttonGroup = new QButtonGroup(this);
    setLayout(layout);

    addButtonToPanel("Classic Tower Nv.1 10g", 0, 0, relativeScene);
    addButtonToPanel("Classic Tower Nv.2 15g", 0, 1, relativeScene);
    addButtonToPanel("Classic Tower Nv.3 25g", 0, 2, relativeScene);
    addButtonToPanel("Tesla Tower Nv.1 15g", 1, 0, relativeScene);
    addButtonToPanel("Tesla Tower Nv.2 25g", 1, 1, relativeScene);
    addButtonToPanel("Tesla Tower Nv.3 55g", 1, 2, relativeScene);
    addButtonToPanel("Canon Tower Nv.1 15g", 2, 0, relativeScene);
    addButtonToPanel("Canon Tower Nv.2 20g", 2, 1, relativeScene);
    addButtonToPanel("Canon Tower Nv.3 30g", 2, 2, relativeScene);
    addButtonToPanel("Crossbow Tower Nv.1 10g", 3, 0, relativeScene);
    addButtonToPanel("Crossbow Tower Nv.2 20g", 3, 1, relativeScene);
    addButtonToPanel("Crossbow Tower Nv.3 40g", 3, 2, relativeScene);

    connect(buttonGroup, qOverload<QAbstractButton*>(&QButtonGroup::buttonClicked), relativeScene, &MyScene::spawnTowerOnScene); //connect the buttonClicked event to the function that place a tower
}

void TowerMenu::addButtonToPanel(const QString& buttonName, int row, int column , const MyScene* relativeScene) {
    QPushButton *tower = new QPushButton(buttonName, this);
    tower->setEnabled(true);
    tower->resize(100, 100);
    buttonGroup->addButton(tower);
    buttonArray.append(tower);
    layout->addWidget(tower, row, column);
}

HealthBar::HealthBar(QGraphicsItem* parent, float health) : QGraphicsWidget(parent) {
    progressBar = new QProgressBar();
    progressBar->setMaximum(health);
    progressBar->setMinimum(0);
    progressBar->setValue(health);
    progressBar->setTextVisible(false);

    layout = new QGraphicsLinearLayout();
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

void HealthBar::addToLayout(QGraphicsProxyWidget *w) {
    layout->addItem(w);
}

void HealthBar::setLabel(QLabel *l) {
    if(label != nullptr){
        delete label;
    }
    label = l;
}

GoldWidget::GoldWidget(const QString &imagePath, const QString &text, QGraphicsItem *parent)
        : QGraphicsWidget(parent) {
    // Créez un conteneur QWidget pour contenir les QLabels
    containerWidget = new QWidget;

    // Rendre le fond du conteneur transparent
    containerWidget->setAttribute(Qt::WA_NoSystemBackground, true);
    containerWidget->setAttribute(Qt::WA_TranslucentBackground, true);
    containerWidget->setStyleSheet("background: transparent;");

    // Créez un QLabel pour l'image
    imageLabel = new QLabel(containerWidget);
    QPixmap pixmap(imagePath);
    imageLabel->setPixmap(pixmap);

    // Créez un QLabel pour le texte
    textLabel = new QLabel(text, containerWidget);
    textLabel->setAlignment(Qt::AlignCenter);

    // Utilisez un QVBoxLayout pour organiser les labels verticalement
    QHBoxLayout *layout = new QHBoxLayout(containerWidget);
    layout->addWidget(imageLabel);
    layout->addWidget(textLabel);
    containerWidget->setLayout(layout);

    // Créez un QGraphicsProxyWidget pour contenir le QWidget
    proxyWidget = new QGraphicsProxyWidget(this);
    proxyWidget->setWidget(containerWidget);

    // Ajustez la taille de GoldWidget pour correspondre à celle du containerWidget
    setPreferredSize(containerWidget->sizeHint());
}

void GoldWidget::setText(const QString &newText) {
    textLabel->setText(newText);
}

//All the slots

