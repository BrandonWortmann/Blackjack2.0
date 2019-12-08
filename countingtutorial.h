#ifndef COUNTINGTUTORIAL_H
#define COUNTINGTUTORIAL_H

#include <QMainWindow>
#include <QLabel>
#include "blackjack.h"

namespace Ui {
class CountingTutorial;
}

class CountingTutorial : public QMainWindow
{
    Q_OBJECT

public:
    explicit CountingTutorial(QWidget *parent = nullptr);
    ~CountingTutorial();
    Ui::CountingTutorial *ui;
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
    void cheatSheet();
};

#endif // COUNTTUTORIAL_H
