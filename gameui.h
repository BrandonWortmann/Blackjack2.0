/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for gameUI                      *
 *                                              *
 ************************************************/

#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>
#include <vector>
#include <QLabel>
#include "blackjack.h"

namespace Ui {
class GameUI;
}

class GameUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameUI(QWidget *parent = nullptr);
    ~GameUI();
    void startGame();
    void beginDealing();
    void hitMe();
    void stand();
    void doubleDown();
    void split();
    void checkDealer();
    void analyzeResult();
    void dealUserCard(Blackjack::card userCard);
    void dealDealerCard(Blackjack::card dealerCard);
    void wagerChanged();
    void dealToDealer();
    QString getCardPath(Blackjack::card);
    Ui::GameUI *ui;

    void chipWhiteButtonPressed();
    void chipRedButtonPressed();
    void chipBlueButtonPressed();
    void chipGreenButtonPressed();
    void chipBlackButtonPressed();

private:
    unsigned long money;
    unsigned long wager;
    int userNum;
    int dealerNum;
    int playerNextCardPos;
    int dealerNextCardPos;
    QVector<QLabel*> cards;
    int index;
    QVector<QLabel*> dealerCards;
    Blackjack game;
    bool hasShuffled;
};

#endif // GAMEUI_H
