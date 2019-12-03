#ifndef TUTORIALUI_H
#define TUTORIALUI_H

#include <QMainWindow>
#include <vector>
#include <QLabel>
#include "blackjack.h"

namespace Ui {
class TutorialUI;
}

class TutorialUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit TutorialUI(QWidget *parent = nullptr);
    ~TutorialUI();
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
    Ui::TutorialUI *ui;


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
};

#endif // TutorialUI_H
