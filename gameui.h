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


private:
    Ui::GameUI *ui;
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
};

#endif // GAMEUI_H
