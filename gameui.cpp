#include "gameui.h"
#include "ui_gameui.h"
#include <QTimer>
#include <QPushButton>

GameUI::GameUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameUI)
{
    ui->setupUi(this);
    srand((unsigned int) time(nullptr));

    connect(ui->startButton, &QPushButton::pressed,
            this, &GameUI::beginDealing);
    connect(ui->hitButton, &QPushButton::pressed,
            this, &GameUI::hitMe);
    connect(ui->standButton, &QPushButton::pressed,
            this, &GameUI::stand);
}

GameUI::~GameUI()
{
    delete ui;
}

void GameUI::startGame() {
    ui->bustLabel->hide();
    ui->winLabel->hide();
    ui->loseLabel->hide();
    ui->wagerLabel->show();
    ui->wagerEdit->show();
}

void GameUI::beginDealing() {
    ui->wagerLabel->hide();
    ui->wagerEdit->hide();
    ui->standButton->show();
    ui->hitButton->show();
}

void GameUI::stand() {
    ui->standButton->hide();
    ui->hitButton->hide();
    userNum = 18;
    checkDealer();
}

void GameUI::checkDealer() {
    int dealernum = (rand() % 10) + 14;
    if(dealernum > userNum && dealernum <= 21) {
        ui->loseLabel->setText("You Lose\nYou lost $" + QString::number(wager));
        money += wager;
    }
    else {
        ui->winLabel->setText("You Win!\nYou won $" + QString::number(wager));
        money += wager;
    }
    QTimer::singleShot(250, this, &GameUI::startGame);
}
