#include "gameui.h"
#include "ui_gameui.h"
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>
#include <unistd.h>

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
    index = 0;
    money = 500;
    cards.push_back(ui->card1);
    cards.push_back(ui->card2);
    cards.push_back(ui->card3);
    cards.push_back(ui->card4);
    cards.push_back(ui->card5);
    cards.push_back(ui->card6);
    cards.push_back(ui->card7);
    cards.push_back(ui->card8);
    dealerCards.push_back(ui->dealerCard1);
    dealerCards.push_back(ui->dealerCard2);
    dealerCards.push_back(ui->dealerCard3);
    dealerCards.push_back(ui->dealerCard4);
    dealerCards.push_back(ui->dealerCard5);
    dealerCards.push_back(ui->dealerCard6);
    dealerCards.push_back(ui->dealerCard7);
    dealerCards.push_back(ui->dealerCard8);
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
    ui->card1->hide();
    ui->card2->hide();
    ui->card3->hide();
    ui->card4->hide();
    ui->card5->hide();
    ui->card6->hide();
    ui->card7->hide();
    ui->card8->hide();
    ui->dealerCard1->hide();
    ui->dealerCard2->hide();
    ui->dealerCard3->hide();
    ui->dealerCard4->hide();
    ui->dealerCard5->hide();
    ui->dealerCard6->hide();
    ui->dealerCard7->hide();
    ui->dealerCard8->hide();
    ui->bustLabel->hide();
    ui->winLabel->hide();
    ui->loseLabel->hide();
    ui->wagerLabel->show();
    ui->wagerEdit->show();
    ui->startButton->show();
    index = 0;
}

void GameUI::beginDealing() {
    unsigned long newWager = (unsigned long) ui->wagerEdit->text().toLong();
    if(newWager > money) {
        ui->wagerLabel->setText("You ain't got\nthe dough son!");
        QTimer::singleShot(3000, [this] () {
            ui->wagerLabel->setText("What is your wager?");
            });
        return;
    }

    if(newWager == 0) {
        ui->wagerLabel->setText("We're gonna need some\n money from ya dawg.");
        QTimer::singleShot(3000, [this] () {
            ui->wagerLabel->setText("What is your wager?");
            });
        return;
    }
    wager =  (unsigned long) (ui->wagerEdit->text().toLong());

    ui->wagerLabel->hide();
    ui->wagerEdit->hide();
    ui->startButton->hide();
    ui->standButton->show();
    ui->hitButton->show();
    ui->doubleButton->show();
    dealUserCard();
    dealUserCard();
    index = 1;
    ui->dealerCard1->setStyleSheet("border-image: url(:/new/images/Resources/cardBack.png) 0 0 0 0 stretch");
    ui->dealerCard1->show();
    dealDealerCard();

}

void GameUI::dealUserCard() {
    if(index == 8) {
        index = 0;
    }

    QString file_path = getCardPath();
    cards[index]->setStyleSheet(file_path);
    cards[index]->show();
    index++;
}

void GameUI::dealDealerCard() {
    if(index == 8) {
        index = 0;
    }
    QString file_path = getCardPath();
    dealerCards[index]->setStyleSheet(file_path);
    dealerCards[index]->show();
    index++;
}

void GameUI::stand() {
    ui->standButton->hide();
    ui->hitButton->hide();
    ui->splitButton->hide();
    ui->doubleButton->hide();
    userNum = 18;
    index = 2;
    checkDealer();
}

void GameUI::dealToDealer() {
    dealerNum = 11;
    while(dealerNum < 18) {
        dealDealerCard();
        dealerNum += rand() % 5;
    }
}

void GameUI::checkDealer() {
    dealToDealer();
    if(dealerNum > userNum && dealerNum <= 21) {
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
    dealUserCard();
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

QString GameUI::getCardPath() {
    int suit;
    int cardnum;
    QString file_path = "border-image: url(:/new/images/Resources/";
    QString card = "card";

    suit = (rand() % 4) + 1;
    cardnum = ((rand() % 13) + 1);

    switch(suit) {
        case 1:
            card += "Clubs";
            break;
        case 2:
            card += "Hearts";
            break;
        case 3:
            card += "Diamonds";
            break;
        case 4:
            card += "Spades";
            break;
    }

    switch(cardnum) {
        case 1:
            card += "A";
            break;
        case 11:
            card += "J";
            break;
        case 12:
            card += "Q";
            break;
        case 13:
            card += "K";
            break;
        default:
            QString newCardNum = QString::number(cardnum);
            card += newCardNum;
            break;
    }

    file_path += card;
    file_path += ".png) 0 0 0 0 stretch";
    return file_path;
}
