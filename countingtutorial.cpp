/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  gameUI.cpp                                  *
 *  blackjack gameUI with wagers.               *
 *                                              *
 ************************************************/

#include "countingtutorial.h"
#include "ui_countingtutorial.h"
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>
#include <QWidget>
#include <QImage>
#include <unistd.h>


CountingTutorial::CountingTutorial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CountingTutorial)
{
    ui->setupUi(this);

        srand((unsigned int) time(nullptr));
        ui->hitButton->hide();
        ui->standButton->hide();
        ui->doubleButton->hide();
        ui->splitButton->hide();
        ui->cardCountLabel->hide();
        ui->checkButton->hide();
        ui->returnButton->show();

        ui->backgroundLabel->setStyleSheet("border-image: url(:/new/images/Resources/green-felt.jpg) 0 0 0 0 stretch");
        index = 0;
        money = 500;
        handCount = -1;
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

        QImage* highlightColor = new QImage(561, 211, QImage::Format_RGBA64);
        highlightColor->fill(*(new QColor(0, 0, 255, 100)));
        ui->firstHighlightLabel->setPixmap(QPixmap::fromImage(*highlightColor));
        ui->secondHighlightLabel->setPixmap(QPixmap::fromImage(*highlightColor));

        connect(ui->hitButton, &QPushButton::pressed,
                this, &CountingTutorial::hitMe);
        connect(ui->standButton, &QPushButton::pressed,
                this, &CountingTutorial::stand);
        connect(ui->wagerEdit, &QLineEdit::textChanged,
                this, &CountingTutorial::wagerChanged);
        connect(ui->doubleButton, &QPushButton::pressed,
                this, &CountingTutorial::doubleDown);
        connect(ui->splitButton, &QPushButton::pressed,
                this, &CountingTutorial::split);
        connect(ui->checkButton, &QPushButton::pressed,
                this, &CountingTutorial::checkCardCount);
}

CountingTutorial::~CountingTutorial()
{
    delete ui;
}

void CountingTutorial::checkCardCount() {
    ui->checkButton->hide();
    int cardCount = game.getCount();
    int count = ui->wagerEdit->text().toInt();
    QString num = QString::number(cardCount);

    if(cardCount == count) {
        ui->cardCountLabel->setText("Correct!");
    }
    else {
        ui->cardCountLabel->setText("Incorrect!\nCorrect Num: " + num);
    }

    QTimer::singleShot(2000, this, [this] () {
       ui->cardCountLabel->hide();
       ui->wagerEdit->hide();
    });
    QTimer::singleShot(2000, this, &CountingTutorial::beginDealing);
}

void CountingTutorial::startGame() {
    handCount++;
    ui->cardCountLabel->setText("What is the current\ncard count?");
    ui->wagerEdit->clear();
    ui->cardCountLabel->hide();
    //ui->wagerEdit->show();

    for(int i = 0; i < cards.size(); i++) {
        cards[i]->hide();
    }

    for(int i = 0; i < dealerCards.size(); i++) {
        dealerCards[i]->hide();
    }

    ui->resultLabel->hide();
    ui->firstHighlightLabel->hide();
    ui->secondHighlightLabel->hide();

    if(handCount == 3) {
        handCount = 0;
        ui->cardCountLabel->show();
        ui->checkButton->show();
        ui->wagerEdit->show();
    }
    else {
        QTimer::singleShot(500, this, &CountingTutorial::beginDealing);
    }

    index = 0;

    if(ui->card1->geometry().x() < 200) {
        for(int i = 0; i < 8; i++) {
            cards.removeLast();
        }

        for(int i = 0; i < 8; i++) {
            cards[i]->setGeometry(cards[i]->geometry().x() + 200, cards[i]->geometry().y(), 131, 201);
        }
    }
}

void CountingTutorial::beginDealing() {
    wager = 5;
    money = 500;
    bool isBlackjack = game.bet(wager);
    ui->wagerEdit->hide();
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

void CountingTutorial::dealUserCard(Blackjack::card userCard) {
    if(index == 8) {
        index = 0;
    }

    QString file_path = getCardPath(userCard);
    cards[index]->setStyleSheet(file_path);
    cards[index]->show();
    index++;
}

void CountingTutorial::dealDealerCard(Blackjack::card dealerCard) {
    QString file_path = getCardPath(dealerCard);
    dealerCards[index]->setStyleSheet(file_path);
    dealerCards[index]->show();
    index++;
}

void CountingTutorial::stand()
{
    if(game.stay())
    {
        index = 9;
        ui->secondHighlightLabel->show();
        ui->firstHighlightLabel->hide();
        return;
    }
    ui->secondHighlightLabel->hide();
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

void CountingTutorial::dealToDealer()
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
    QTimer::singleShot(currTime, this, &CountingTutorial::analyzeResult);
}

void CountingTutorial::checkDealer()
{
    //TODO: Check shuffle
    if(game.getResult().outcome != Blackjack::blackjack)
    {
        dealToDealer();
    }
    else {
        QTimer::singleShot(1000, this, &CountingTutorial::analyzeResult);
    }

}

void CountingTutorial::analyzeResult() {
    Blackjack::result result = game.getResult();

    switch(result.outcome)
    {
    case Blackjack::win:
        ui->resultLabel->setText("You Win!");
        break;

    case Blackjack::lose:
        ui->resultLabel->setText("You Lose!");
        break;

    case Blackjack::push:
        ui->resultLabel->setText("You Tied!");
        break;

    case Blackjack::blackjack:
        ui->resultLabel->setText("BLACKJACK!!!");
        break;

    case Blackjack::bust:
        ui->resultLabel->setText("You Bust!");
        break;

    }
    if(result.isShuffled) {
        ui->resultLabel->setText(ui->resultLabel->text() + "\nDeck is being shuffled");
    }
    ui->resultLabel->show();
    QTimer::singleShot(2500, this, &CountingTutorial::startGame);
}

void CountingTutorial::hitMe()
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

void CountingTutorial::doubleDown()
{
    dealUserCard(game.doubleDown());
    stand();
}

void CountingTutorial::split()
{
    ui->splitButton->hide();
    for(int i = 0; i < 8; i++) {

        cards[i]->setGeometry(cards[i]->geometry().x() - 200, cards[i]->geometry().y(), 131, 201);
    }

    game.split();
    ui->splitCard1->setStyleSheet(getCardPath(game.getPlayerHand()[1].hand[0]));
    cards[1]->setStyleSheet("");
    ui->splitCard1->show();
    cards.push_back(ui->splitCard1);
    cards.push_back(ui->splitCard2);
    cards.push_back(ui->splitCard3);
    cards.push_back(ui->splitCard4);
    cards.push_back(ui->splitCard5);
    cards.push_back(ui->splitCard6);
    cards.push_back(ui->splitCard7);
    cards.push_back(ui->splitCard8);
    index = 1;
    ui->firstHighlightLabel->show();
}

void CountingTutorial::wagerChanged() {
    QString val = ui->wagerEdit->text();
    int len = val.length();
    if(len < 1) {
        return;
    }

    QString newVal = val;
    for(int i = 0; i < len; i++) {
        if((i != 0 || val.at(i) != 45) && (val.at(i) < 48 || val.at(i) > 57)) {
            newVal.remove(i, 1);
        }
    }
    ui->wagerEdit->setText(newVal);
}

QString CountingTutorial::getCardPath(Blackjack::card inputCard)
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
