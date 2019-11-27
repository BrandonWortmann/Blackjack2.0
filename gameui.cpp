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
    connect(ui->doubleButton, &QPushButton::pressed,
            this, &GameUI::doubleDown);
    connect(ui->splitButton, &QPushButton::pressed,
            this, &GameUI::split);
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
    bool isBlackjack = game.bet(wager);
    ui->wagerLabel->hide();
    ui->wagerEdit->hide();
    ui->startButton->hide();
    ui->standButton->show();
    ui->hitButton->show();
    dealUserCard(game.getPlayerHand()[0].hand[0]);
    dealUserCard(game.getPlayerHand()[0].hand[1]);
    if(money >= (wager << 1))
    {
        ui->doubleButton->show();
        if((game.getPlayerHand()[0].hand[0].number == game.getPlayerHand()[0].hand[1].number) || (game.getPlayerHand()[0].hand[0].number >= 10 && game.getPlayerHand()[0].hand[1].number >= 10))
        {
            ui->splitButton->show();
        }
    }
    index = 1;
    ui->dealerCard1->setStyleSheet("border-image: url(:/new/images/Resources/cardBack.png) 0 0 0 0 stretch");
    ui->dealerCard1->show();
    dealDealerCard(game.getDealerHand()[1]);
    if(isBlackjack)
    {
        stand();
    }

}

void GameUI::dealUserCard(Blackjack::card userCard) {
    if(index == 8) {
        index = 0;
    }

    QString file_path = getCardPath(userCard);
    cards[index]->setStyleSheet(file_path);
    cards[index]->show();
    index++;
}

void GameUI::dealDealerCard(Blackjack::card dealerCard) {
    if(index == 8) {
        index = 0;
    }
    QString file_path = getCardPath(dealerCard);
    dealerCards[index]->setStyleSheet(file_path);
    dealerCards[index]->show();
    index++;
}

void GameUI::stand()
{
    if(game.stay())
    {
        return;
    }
    QString file_path = getCardPath(game.getDealerHand()[0]);
    dealerCards[0]->setStyleSheet(file_path);
    dealerCards[0]->show();
    ui->standButton->hide();
    ui->hitButton->hide();
    ui->splitButton->hide();
    ui->doubleButton->hide();
    index = 2;
    checkDealer();
}

void GameUI::dealToDealer()
{
    Blackjack::card inputCard;
    inputCard = game.dealerStep();
    int currTime = 1000;
    while(inputCard.suit != Blackjack::invalid)
    {
        QTimer::singleShot(currTime, [this, inputCard] () {dealDealerCard(inputCard);});
        inputCard = game.dealerStep();
        currTime += 1000;
    }
    QTimer::singleShot(currTime, this, &GameUI::analyzeResult);
}

void GameUI::checkDealer()
{
    //TODO: Check shuffle
    if(game.getResult().outcome != Blackjack::blackjack)
    {
        dealToDealer();
    }
    else {
        QTimer::singleShot(1000, this, &GameUI::analyzeResult);
    }

}

void GameUI::analyzeResult() {
    Blackjack::result result = game.getResult();

    switch(result.outcome)
    {
    case Blackjack::win:
        ui->winLabel->setText("You Win!\nYou won $" + QString::number(result.netGain));
        ui->winLabel->show();
        money += result.netGain;
        break;

    case Blackjack::lose:
        ui->loseLabel->setText("You Lose\nYou lost $" + QString::number(-result.netGain));
        ui->loseLabel->show();
        money += result.netGain;
        break;

    case Blackjack::push:
        ui->loseLabel->setText("You Tied! You're not broke yet!\n");
        ui->loseLabel->show();
        break;

    case Blackjack::blackjack:
        ui->winLabel->setText("BLACKJACK!!!\nYou won $" + QString::number(result.netGain));
        ui->winLabel->show();
        money += result.netGain;
        break;

    case Blackjack::bust:
        ui->loseLabel->setText("You Bust\nYou lost $" + QString::number(-result.netGain));
        ui->loseLabel->show();
        money += result.netGain;
        break;

    }
    ui->moneyLabel->setText("$" + QString::number(money));
    QTimer::singleShot(5000, this, &GameUI::startGame);
}

void GameUI::hitMe()
{
    ui->splitButton->hide();
    ui->doubleButton->hide();
    bool isBust = false;
    dealUserCard(game.hit(isBust));
    if(isBust)
    {
        stand();
    }
}

void GameUI::doubleDown()
{
    dealUserCard(game.doubleDown());
    stand();
}

void GameUI::split()
{

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

QString GameUI::getCardPath(Blackjack::card inputCard)
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
