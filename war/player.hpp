//player class
#include "deck.hpp"
#pragma once

class player
{
  public:
    player(Deck);//constructor
    void shuffleDeck();//shuffles players deck
    bool moveCardToHand();//returns true if successful, false if else
    Card cardReveal();//returns top card in players hand to be compared with opponents
    void addCardToDeck(Card);//adds card to player's deck
    Card giveCardAway();//returns top card in player's hand
    bool isHandEmpty();//returns true if playerHand is empty, false if else
  private:
    Deck playerDeck;
    std::vector<Card> playerHand;
};