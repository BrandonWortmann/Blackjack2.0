/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for tutorial                    *
 *                                              *
 ************************************************/

#ifndef TUTORIALUI_H
#define TUTORIALUI_H

#include <vector>
#include <QLabel>
#include "blackjack.h"
#include <QMainWindow>

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
    void cheatSheet();
    void dealUserCard(Blackjack::card userCard);
    void dealDealerCard(Blackjack::card dealerCard);
    QString getCardPath(Blackjack::card);
    Ui::TutorialUI *ui;


private:
    int playerNextCardPos;
    int dealerNextCardPos;
    QVector<QLabel*> cards;
    int index;
    QVector<QLabel*> dealerCards;
    Blackjack game;
    Blackjack::action action;
    QString correctMove;
};

#endif // TutorialUI_H
