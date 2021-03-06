/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for counttutorial               *
 *                                              *
 ************************************************/

#ifndef COUNTTUTORIAL_H
#define COUNTTUTORIAL_H

#include <QWidget>
#include <vector>
#include <QLabel>
#include "blackjack.h"

namespace Ui {
class CountTutorial;
}

class CountTutorial : public QWidget
{
    Q_OBJECT

public:
    explicit CountTutorial(QWidget *parent = nullptr);
    ~CountTutorial();
    Ui::CountTutorial *ui;
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
    void checkCardCount();
    void dealToDealer();
    QString getCardPath(Blackjack::card);


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
    Blackjack::action action;
    QString correctMove;
    int handCount;
};

#endif // COUNTTUTORIAL_H
