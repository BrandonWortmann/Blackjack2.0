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

private:
    QStack<card> deck;
    int count;
    QList<card> dealerHand;
    QList<hand> playerHand;
    int currentHand;

    void shuffle();
    bool isBlackjack(QList<card> hand);
    card dealCard();
};

#endif // BLACKJACK_H
