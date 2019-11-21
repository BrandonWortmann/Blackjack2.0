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
    ui->hitButton->hide();
    ui->standButton->hide();
    ui->doubleButton->hide();
    ui->splitButton->hide();
    money = 500;
    startGame();

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

    wager = ui->wagerEdit->text().toInt();

    ui->wagerLabel->hide();
    ui->wagerEdit->hide();
    ui->startButton->hide();
    ui->standButton->show();
    ui->hitButton->show();
    ui->doubleButton->show();

    // Maybe show split button, depending on engine
}

void GameUI::dealCard(bool isPlayer) {
    int xPos;
    int yPos;
    if(isPlayer) {
        xPos = playerNextCardPos;
        yPos = 500;
    }
    else {
        xPos = dealerNextCardPos;
        yPos = 200;
    }

    QLabel* newCard = new QLabel();
    newCard->setGeometry(xPos, yPos, 75, 150);
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
        ui->loseLabel->show();
        money -= wager;

    }
    else {
        ui->winLabel->setText("You Win!\nYou won $" + QString::number(wager));
        ui->winLabel->show();
        money += wager;
    }
    ui->moneyLabel->setText("$" + QString::number(money));
    QTimer::singleShot(1500, this, &GameUI::startGame);
}

void GameUI::hitMe() {

}

void GameUI::doubleDown() {

}

void GameUI::split() {

}
