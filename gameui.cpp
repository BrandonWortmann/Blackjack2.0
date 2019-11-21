#include "gameui.h"
#include "ui_gameui.h"
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>

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

    ui->backgroundLabel->setStyleSheet("border-image: url(:/new/images/Resources/green-felt.jpg) 0 0 0 0 stretch");

    money = 500;
    startGame();

    connect(ui->startButton, &QPushButton::pressed,
            this, &GameUI::beginDealing);
    connect(ui->hitButton, &QPushButton::pressed,
            this, &GameUI::hitMe);
    connect(ui->standButton, &QPushButton::pressed,
            this, &GameUI::stand);
    connect(ui->wagerEdit, &QLineEdit::textChanged,
            this, &GameUI::wagerChanged);
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
    ui->startButton->show();
}

void GameUI::beginDealing() {
    unsigned long newWager = (unsigned long) ui->wagerEdit->text().toLong();
    if(newWager > money) {
        ui->wagerLabel->setText("You can't wager\n more than you own!");
        QTimer::singleShot(3000, [this] () {
            ui->wagerLabel->setText("What is your wager?");
            });
        return;
    }
    wager = (unsigned long) ui->wagerEdit->text().toLong();

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
    ui->splitButton->hide();
    ui->doubleButton->hide();
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

void GameUI::wagerChanged() {
    QString val = ui->wagerEdit->text();
    int len = val.length();
    if(len < 1) {
        return;
    }
    if(val.at(len - 1) < 48 || val.at(len - 1) > 57) {
        val.chop(1);
        ui->wagerEdit->setText(val);
    }
}
