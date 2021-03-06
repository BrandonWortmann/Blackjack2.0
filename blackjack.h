/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for blackjack                   *
 *                                              *
 ************************************************/

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <QStack>
#include <QList>

class Blackjack
{
public:
    Blackjack();

    enum _outcome
    {
        win, lose, push, blackjack, bust
    };
    struct result
    {
        _outcome outcome;
        long netGain;
        bool isShuffled;
    };

    enum _suit
    {
        spade, heart, club, diamond, invalid
    };
    struct card
    {
        _suit suit;
        int number;
    };

    struct hand
    {
        QList<card> hand;
        unsigned long betAmount;
    };

    enum action
    {
        _hit, _stand, _doubledown, _split
    };

    bool bet(unsigned long amount);
    card hit(bool& isBust);
    bool stay();
    void split();
    card doubleDown();
    card dealerStep();
    result getResult();
    int sumHand(QList<card> hand);

    int getCount();
    QList<card> getDealerHand();
    QList<hand> getPlayerHand();
    int getCurrentHand();
    action correctMove();

private:
    QStack<card> deck;
    int count;
    QList<card> dealerHand;
    QList<hand> playerHand;
    int currentHand;

    bool isBlackjack(QList<card> hand);
    card dealCard();
    bool sameCard(QList<card> hand);
    void shuffle();
};

#endif // BLACKJACK_H
