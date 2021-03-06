/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  gameUI.cpp                                  *
 *  blackjack gameUI with wagers.               *
 *                                              *
 ************************************************/

#include "gameui.h"
#include "ui_gameui.h"
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>
#include <QWidget>
#include <QImage>
#include <QDebug>
#include <unistd.h>

/**
 * @brief GameUI::GameUI
 * @param parent
 * Game User Interface
 */
GameUI::GameUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameUI)
{
    // Default setup
    ui->setupUi(this);
    srand((unsigned int) time(nullptr));
    ui->hitButton->hide();
    ui->standButton->hide();
    ui->doubleButton->hide();
    ui->splitButton->hide();

    // Adds the background label
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

    // Splitting UI
    QImage* highlightColor = new QImage(561, 211, QImage::Format_RGBA64);
    highlightColor->fill(*(new QColor(0, 0, 255, 100)));
    ui->firstHighlightLabel->setPixmap(QPixmap::fromImage(*highlightColor));
    ui->secondHighlightLabel->setPixmap(QPixmap::fromImage(*highlightColor));

    // Establish connections
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
    connect(ui->chipWhiteButton, &QPushButton::pressed,
            this, &GameUI::chipWhiteButtonPressed);
    connect(ui->chipRedButton, &QPushButton::pressed,
            this, &GameUI::chipRedButtonPressed);
    connect(ui->chipBlueButton, &QPushButton::pressed,
            this, &GameUI::chipBlueButtonPressed);
    connect(ui->chipGreenButton, &QPushButton::pressed,
            this, &GameUI::chipGreenButtonPressed);
    connect(ui->chipBlackButton, &QPushButton::pressed,
            this, &GameUI::chipBlackButtonPressed);
    connect(ui->clearButton, &QPushButton::pressed,
            ui->wagerEdit, &QLineEdit::clear);
}

/**
 * @brief GameUI::~GameUI
 * Game UI destructor
 */
GameUI::~GameUI()
{
    delete ui;
}

/**
 * @brief GameUI::startGame
 * The Start of the Game Setup
 */
void GameUI::startGame() {
    // Hides old UI stuff
    for(int i = 0; i < cards.size(); i++) {
        cards[i]->hide();
    }

    for(int i = 0; i < dealerCards.size(); i++) {
        dealerCards[i]->hide();
    }

    hasShuffled = false;
    ui->resultLabel->hide();
    ui->firstHighlightLabel->hide();
    ui->secondHighlightLabel->hide();
    ui->wagerLabel->show();
    ui->wagerEdit->show();
    ui->startButton->show();
    ui->chipWhiteButton->show();
    ui->chipRedButton->show();
    ui->chipBlueButton->show();
    ui->chipGreenButton->show();
    ui->chipBlackButton->show();
    ui->clearButton->show();
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

/**
 * @brief GameUI::beginDealing
 * Gets the users wager and deals the cards
 */
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
    ui->chipWhiteButton->hide();
    ui->chipRedButton->hide();
    ui->chipBlueButton->hide();
    ui->chipGreenButton->hide();
    ui->chipBlackButton->hide();
    ui->clearButton->hide();
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

/**
 * @brief GameUI::dealUserCard
 * @param userCard
 * Deals the User cards
 */
void GameUI::dealUserCard(Blackjack::card userCard) {
    if(index == 8) {
        index = 0;
    }

    QString file_path = getCardPath(userCard);
    cards[index]->setStyleSheet(file_path);
    cards[index]->show();
    index++;
}

/**
 * @brief GameUI::dealDealerCard
 * @param dealerCard
 * Helper to deal the Dealers card
 */
void GameUI::dealDealerCard(Blackjack::card dealerCard) {
    QString file_path = getCardPath(dealerCard);
    dealerCards[index]->setStyleSheet(file_path);
    dealerCards[index]->show();
    index++;
}

/**
 * @brief GameUI::stand
 * User chooses to stand round
 */
void GameUI::stand()
{
    if(game.stay())
    {
        if(money >= (wager << 1))
        {
            ui->doubleButton->hide();
        }
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

/**
 * @brief GameUI::dealToDealer
 * Deals the Dealers card
 */
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

/**
 * @brief GameUI::checkDealer
 * Checks if the dealer has won the round
 */
void GameUI::checkDealer()
{
    Blackjack::result res = game.getResult();
    hasShuffled = res.isShuffled;
    if(game.getResult().outcome != Blackjack::blackjack)
    {
        dealToDealer();
    }
    else {
        QTimer::singleShot(1000, this, &GameUI::analyzeResult);
    }

}

/**
 * @brief GameUI::analyzeResult
 * Notifies users of round result
 */
void GameUI::analyzeResult() {
    Blackjack::result result = game.getResult();

    switch(result.outcome)
    {
    case Blackjack::win:
        ui->resultLabel->setText("You Win!\nYou won $" + QString::number(result.netGain));
        money += result.netGain;
        break;

    case Blackjack::lose:
        ui->resultLabel->setText("You Lose!\nYou lost $" + QString::number(-result.netGain));
        money += result.netGain;
        break;

    case Blackjack::push:
        ui->resultLabel->setText("You Push!\nYou're not broke yet!");
        break;

    case Blackjack::blackjack:
        ui->resultLabel->setText("BLACKJACK!!!\nYou won $" + QString::number(result.netGain));
        money += result.netGain;
        break;

    case Blackjack::bust:
        ui->resultLabel->setText("You Bust!\nYou lost $" + QString::number(-result.netGain));
        money += result.netGain;
        break;

    }
    if(result.isShuffled || hasShuffled) {
        ui->resultLabel->setText(ui->resultLabel->text() + "\nDeck is being shuffled");
    }
    ui->resultLabel->show();
    ui->moneyLabel->setText("$" + QString::number(money));
    QTimer::singleShot(2500, this, &GameUI::startGame);
}

/**
 * @brief GameUI::hitMe
 * User selects Hit
 */
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

/**
 * @brief GameUI::doubleDown
 * User Selects double down
 */
void GameUI::doubleDown()
{
    dealUserCard(game.doubleDown());
    stand();
}

/**
 * @brief GameUI::split
 * User selects to split
 */
void GameUI::split()
{
    ui->splitButton->hide();
    for(int i = 0; i < 8; i++) {

        cards[i]->setGeometry(cards[i]->geometry().x() - 200, cards[i]->geometry().y(), 131, 201);
    }
    if(money >= (wager << 1))
    {
        ui->doubleButton->hide();
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

/**
 * @brief GameUI::wagerChanged
 * New Wager from the user
 */
void GameUI::wagerChanged() {
    QString val = ui->wagerEdit->text();
    int len = val.length();
    if(len < 1) {
        return;
    }

    QString newVal = val;
    for(int i = 0; i < len; i++) {
        if(val.at(i) < 48 || val.at(i) > 57) {
            newVal.remove(i, 1);
        }
    }
    ui->wagerEdit->setText(newVal);
}

/**
 * @brief GameUI::getCardPath
 * @param inputCard
 * Gets the file path of a card
 */
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

/**
 * @brief GameUI::chipWhiteButtonPressed
 * User selects the white chip for wagering
 */
void GameUI::chipWhiteButtonPressed() {
    QString val = ui->wagerEdit->text();
    int num;
    if(val == "") {
        num = 0;
    }
    else {
        num = val.toInt();
    }

    ui->wagerEdit->setText(QString::number(num + 1));
}

/**
 * @brief GameUI::chipRedButtonPressed
 * User seleccts the red chip for wagering
 */
void GameUI::chipRedButtonPressed() {
    QString val = ui->wagerEdit->text();
    int num;
    if(val == "") {
        num = 0;
    }
    else {
        num = val.toInt();
    }

    ui->wagerEdit->setText(QString::number(num + 5));
}

/**
 * @brief GameUI::chipBlueButtonPressed
 * User selects the blue chip for wagering
 */
void GameUI::chipBlueButtonPressed() {
    QString val = ui->wagerEdit->text();
    int num;
    if(val == "") {
        num = 0;
    }
    else {
        num = val.toInt();
    }

    ui->wagerEdit->setText(QString::number(num + 25));
}

/**
 * @brief GameUI::chipGreenButtonPressed
 * User selects the green chip for wagering
 */
void GameUI::chipGreenButtonPressed() {
    QString val = ui->wagerEdit->text();
    int num;
    if(val == "") {
        num = 0;
    }
    else {
        num = val.toInt();
    }

    ui->wagerEdit->setText(QString::number(num + 100));
}

/**
 * @brief GameUI::chipBlackButtonPressed
 * User selects the blackchip for wagering
 */
void GameUI::chipBlackButtonPressed() {
    QString val = ui->wagerEdit->text();
    int num;
    if(val == "") {
        num = 0;
    }
    else {
        num = val.toInt();
    }

    ui->wagerEdit->setText(QString::number(num + 500));
}
