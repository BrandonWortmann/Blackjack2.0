/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  tutorial.cpp                                *
 *  widget that holds modified gameUI, used     *
 *  for practicing hit/stay strategies.         *
 *                                              *
 ************************************************/

#include "tutorial.h"
#include "ui_tutorial.h"
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>
#include <unistd.h>
#include <iostream>

TutorialUI::TutorialUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TutorialUI)
{
    ui->setupUi(this);
    srand((unsigned int) time(nullptr));
    ui->hitButton->hide();
    ui->standButton->hide();
    ui->doubleButton->hide();
    ui->splitButton->hide();

    ui->backgroundLabel->setStyleSheet("border-image: url(:/new/images/Resources/green-felt.jpg) 0 0 0 0 stretch");
    index = 0;
    cards.push_back(ui->card1);
    cards.push_back(ui->card2);
    dealerCards.push_back(ui->dealerCard1);
    dealerCards.push_back(ui->dealerCard2);
    startGame();

    connect(ui->hitButton, &QPushButton::pressed,
            this, &TutorialUI::hitMe);
    connect(ui->standButton, &QPushButton::pressed,
            this, &TutorialUI::stand);
    connect(ui->doubleButton, &QPushButton::pressed,
            this, &TutorialUI::doubleDown);
    connect(ui->splitButton, &QPushButton::pressed,
            this, &TutorialUI::split);
}

TutorialUI::~TutorialUI()
{
    delete ui;
}

void TutorialUI::startGame() {
    ui->hitButton->hide();
    ui->doubleButton->hide();
    ui->splitButton->hide();
    ui->standButton->hide();
    ui->card1->hide();
    ui->card2->hide();
    ui->dealerCard1->hide();
    ui->dealerCard2->hide();
    ui->bustLabel->hide();
    index = 0;
    beginDealing();
}

void TutorialUI::beginDealing() {

    bool isBlackjack = game.bet(0);
    action = game.correctMove();
    switch(action) {
     case(Blackjack::_stand):
        correctMove = "Stand";
        break;
     case(Blackjack::_hit):
        correctMove = "Hit";
        break;
     case(Blackjack::_split):
        correctMove = "Split";
        break;
     case(Blackjack::_doubledown):
        correctMove = "Double Down";
        break;
    }
    ui->standButton->show();
    ui->doubleButton->show();
    ui->hitButton->show();
    dealUserCard(game.getPlayerHand()[0].hand[0]);
    dealUserCard(game.getPlayerHand()[0].hand[1]);
    if((game.getPlayerHand()[0].hand[0].number == game.getPlayerHand()[0].hand[1].number) || (game.getPlayerHand()[0].hand[0].number >= 10 && game.getPlayerHand()[0].hand[1].number >= 10))
    {
        ui->splitButton->show();
    }
    index = 1;
    ui->dealerCard1->setStyleSheet("border-image: url(:/new/images/Resources/cardBack.png) 0 0 0 0 stretch");
    ui->dealerCard1->show();
    dealDealerCard(game.getDealerHand()[1]);
    if(isBlackjack)
    {
        startGame();
    }

}

void TutorialUI::dealUserCard(Blackjack::card userCard) {
    if(index == 8) {
        index = 0;
    }

    QString file_path = getCardPath(userCard);
    cards[index]->setStyleSheet(file_path);
    cards[index]->show();
    index++;
}

void TutorialUI::dealDealerCard(Blackjack::card dealerCard) {
    if(index == 8) {
        index = 0;
    }
    QString file_path = getCardPath(dealerCard);
    dealerCards[index]->setStyleSheet(file_path);
    dealerCards[index]->show();
    index++;
}

void TutorialUI::stand()
{
    if(action == Blackjack::_stand) {
        ui->bustLabel->setText("Correct Move!");
    }
    else {
        ui->bustLabel->setText("Incorrect!\n Optimal Move: " + correctMove);
    }
    ui->hitButton->hide();
    ui->doubleButton->hide();
    ui->splitButton->hide();
    ui->standButton->hide();
    ui->bustLabel->show();
    QTimer::singleShot(2000, this, &TutorialUI::startGame);
}

void TutorialUI::hitMe()
{
    if(action == Blackjack::_hit) {
        ui->bustLabel->setText("Correct Move!");
    }
    else {
        ui->bustLabel->setText("Incorrect!\n Optimal Move: " + correctMove);
    }

    ui->hitButton->hide();
    ui->doubleButton->hide();
    ui->splitButton->hide();
    ui->standButton->hide();
    ui->bustLabel->show();
    QTimer::singleShot(2000, this, &TutorialUI::startGame);
}

void TutorialUI::doubleDown()
{
    if(action == Blackjack::_doubledown) {
        ui->bustLabel->setText("Correct Move!");
    }
    else {
        ui->bustLabel->setText("Incorrect!\n Optimal Move: \n" + correctMove);
    }

    ui->hitButton->hide();
    ui->doubleButton->hide();
    ui->splitButton->hide();
    ui->standButton->hide();
    ui->bustLabel->show();
    QTimer::singleShot(2000, this, &TutorialUI::startGame);
}

void TutorialUI::split()
{
    if(action == Blackjack::_split) {
        ui->bustLabel->setText("Correct Move!");
    }
    else {
        ui->bustLabel->setText("Incorrect!\n Optimal Move: " + correctMove);
    }

    ui->hitButton->hide();
    ui->doubleButton->hide();
    ui->splitButton->hide();
    ui->standButton->hide();
    ui->bustLabel->show();
    QTimer::singleShot(2000, this, &TutorialUI::startGame);
}

QString TutorialUI::getCardPath(Blackjack::card inputCard)
{

    QString file_path = "border-image: url(:/new/images/Resources/";
    QString card = "card";

    switch(inputCard.suit) {
        case Blackjack::spade:
            card += "Spades";
            break;
        case Blackjack::heart:
            card += "Hearts";
            break;
        case Blackjack::club:
            card += "Clubs";
            break;
        case Blackjack::diamond:
            card += "Diamonds";
            break;
        default:
            return NULL;
    }

    switch(inputCard.number) {
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
            QString newCardNum = QString::number(inputCard.number);
            card += newCardNum;
            break;
    }

    file_path += card;
    file_path += ".png) 0 0 0 0 stretch";
    return file_path;
}
