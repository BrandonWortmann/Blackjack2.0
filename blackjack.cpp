#include "blackjack.h"
#include <stdlib.h>
#include <cmath>

Blackjack::Blackjack()
{
    shuffle();
}

bool Blackjack::bet(unsigned long amount)
{
    currentHand = 0;
    playerHand.clear();
    dealerHand.clear();
    playerHand.push_back({QList<card>(), amount});
    playerHand[currentHand].hand.push_back(dealCard());
    dealerHand.push_back(dealCard());
    playerHand[currentHand].hand.push_back(dealCard());
    dealerHand.push_back(dealCard());
    if (isBlackjack(playerHand[currentHand].hand) || isBlackjack(dealerHand))
    {
        return true;
    }
    return false;
}

Blackjack::card Blackjack::hit(bool& isBust)
{
    playerHand[currentHand].hand.push_back(dealCard());
    if(sumHand(playerHand[currentHand].hand) > 21)
    {
        isBust = true;
    }
    return playerHand[currentHand].hand.back();
}

// returns true if player can still play
bool Blackjack::stay()
{
    currentHand++;
    if(currentHand >= playerHand.size())
    {
        return false;
    }
    return true;
}

void Blackjack::split()
{
    playerHand.insert(currentHand+1, {QList<card>(), playerHand[currentHand].betAmount});
    playerHand[currentHand+1].hand.push_back(playerHand[currentHand].hand.takeLast());
}

Blackjack::card Blackjack::doubleDown()
{
    bool isBust = false;
    playerHand[currentHand].betAmount <<= 1;
    return hit(isBust);
}

Blackjack::card Blackjack::dealerStep()
{
    bool bust = true;
    for(hand hand : playerHand)
    {
        if(sumHand(hand.hand) <= 21)
        {
            bust = false;
        }
    }
    if (bust || sumHand(dealerHand) >= 17)
    {
        return {invalid, 0};
    }
    dealerHand.push_back(dealCard());
    return dealerHand.back();
}

Blackjack::result Blackjack::getResult()
{
    result result;
    result.netGain = 0;
    if(isBlackjack(dealerHand))
    {
        if(isBlackjack(playerHand[0].hand))
        {
            result.outcome = push;
        }
        else
        {
            result.netGain -= playerHand[0].betAmount;
            result.outcome = lose;
        }
    }
    else if(isBlackjack(playerHand[0].hand))
    {
        result.netGain += (int)ceil((double)playerHand[0].betAmount * 1.5);
        result.outcome = blackjack;
    }
    else
    {
        int dealerSum = sumHand(dealerHand);
        if(dealerSum > 21)
        {
            dealerSum = 0;
        }
        int playerSum;
        bool isBust = true;
        for(hand hand : playerHand)
        {
            playerSum = sumHand(hand.hand);
            if(playerSum > 21)
            {
                result.netGain -= hand.betAmount;
            }
            else if(dealerSum > playerSum)
            {
                result.netGain -= hand.betAmount;
                isBust = false;
            }
            else if(dealerSum < playerSum)
            {
                result.netGain += hand.betAmount;
                isBust = false;
            }
            else
            {
                isBust = false;
            }
        }
        if(isBust)
        {
            result.outcome = bust;
        }
        else if(result.netGain < 0 )
        {
            result.outcome = lose;
        }
        else if(result.netGain > 0)
        {
            result.outcome = win;
        }
        else
        {
            result.outcome = push;
        }
    }
    if(deck.size() < 26)
    {
        shuffle();
        result.isShuffled = true;
    }
    else
    {
        result.isShuffled = false;
    }
    return result;
}

bool Blackjack::isBlackjack(QList<card> hand)
{
    return hand.size() == 2 && sumHand(hand) == 21;
}

int Blackjack::sumHand(QList<card> hand)
{
    int sum = 0;
    int aceCount = 0;
    for(card card : hand)
    {
        if(card.number == 1)
        {
            aceCount++;
        }
        else if(card.number >= 10)
        {
            sum += 10;
        }
        else
        {
            sum += card.number;
        }
    }
    sum += aceCount;
    for(int i = 0; i < aceCount; i++)
    {
        if(sum + 10 > 21)
        {
            break;
        }
        sum += 10;
    }
    return sum;
}

int Blackjack::getCount()
{
    return count;
}

QList<Blackjack::card> Blackjack::getDealerHand()
{
    return dealerHand;
}

QList<Blackjack::hand> Blackjack::getPlayerHand()
{
    return playerHand;
}

int Blackjack::getCurrentHand()
{
    return currentHand;
}

void Blackjack::shuffle()
{
    srand(time(NULL));
    count = 0;
    QList<card> cards;
    for(int i = 0; i < 2; i++)
    {
        for(int j= 1; j <= 13; j++)
        {
            cards.push_back({spade, j});
            cards.push_back({heart, j});
            cards.push_back({club, j});
            cards.push_back({diamond, j});
        }
    }
    int random = 0;
    deck.clear();
    for(int i = cards.size(); i > 0; i--)
    {
        random = rand() % i;
        deck.push(cards[random]);
        cards.removeAt(random);
    }
}

Blackjack::card Blackjack::dealCard()
{
    card card = deck.pop();
    if(card.number >= 2 && card.number <= 6)
    {
        count++;
    }
    else if(card.number >= 10 || card.number == 1)
    {
        count--;
    }
    return card;
}

Blackjack::action Blackjack::correctMove()
{
    int dealerValue = dealerHand[1].number;
    if(dealerValue > 10)
    {
        dealerValue = 10;
    }
    int player1 = playerHand[currentHand].hand[0].number;
    if(player1 > 10)
    {
        player1 = 10;
    }
    int player2 = playerHand[currentHand].hand[0].number;
    if(player2 > 10)
    {
        player2 = 10;
    }
    if(player1 == player2)
    {
        switch (player1)
        {
        case 1:
            return _split;
        case 2:
            if (dealerValue >= 2 && dealerValue <= 7)
            {
                return _split;
            }
            return _hit;
        case 3:
            if (dealerValue >= 2 && dealerValue <= 7)
            {
                return _split;
            }
            return _hit;
        case 4:
            if (dealerValue == 5 || dealerValue == 6)
            {
                return _split;
            }
            return _hit;
        case 5:
            if (dealerValue == 1 || dealerValue == 10)
            {
                return _hit;
            }
            return _doubledown;
        case 6:
            if (dealerValue >= 2 && dealerValue <= 6)
            {
                return _split;
            }
            return _hit;
        case 7:
            if (dealerValue >= 2 && dealerValue <= 7)
            {
                return _split;
            }
            return _hit;
        case 8:
            return _split;
        case 9:
            if (dealerValue == 1 || dealerValue == 7 || dealerValue == 10)
            {
                return _stand;
            }
            return _split;
        case 10:
            return _stand;
        }
    }
    if (player1 == 1 || player2 == 1)
    {
        if (player1 == 1)
        {
            player1 = player2;
        }
        switch (player1)
        {
        case 2:
            if (dealerValue == 5 || dealerValue == 6)
            {
                return _doubledown;
            }
            return _hit;
        case 3:
            if (dealerValue == 5 || dealerValue == 6)
            {
                return _doubledown;
            }
            return _hit;
        case 4:
            if (dealerValue >= 4 && dealerValue <= 6)
            {
                return _doubledown;
            }
            return _hit;
        case 5:
            if (dealerValue >= 4 && dealerValue <= 6)
            {
                return _doubledown;
            }
            return _hit;
        case 6:
            if (dealerValue >= 3 && dealerValue <= 6)
            {
                return _doubledown;
            }
            return _hit;
        case 7:
            if (dealerValue >= 3 && dealerValue <= 6)
            {
                return _doubledown;
            }
            if (dealerValue == 2 || dealerValue == 7 || dealerValue == 8)
            {
                return _stand;
            }
            return _hit;
        default:
            return _stand;
        }
    }
    int sum = player1 + player2;
    if (sum <= 8)
    {
        return _hit;
    }
    switch (sum)
    {
    case 9:
        if (dealerValue >= 3 && dealerValue <= 6)
        {
            return _doubledown;
        }
        return _hit;
    case 10:
        if (dealerValue == 1 || dealerValue == 10)
        {
            return _hit;
        }
        return _doubledown;
    case 11:
        if (dealerValue == 1)
        {
            return _hit;
        }
        return _doubledown;
    case 12:
        if (dealerValue >= 4 && dealerValue <= 6)
        {
            return _stand;
        }
        return _hit;
    default:
        break;
    }
    if (sum <= 16)
    {
        if (dealerValue >= 2 && dealerValue <= 6)
        {
            return _stand;
        }
        return _hit;
    }
    return _stand;
}
