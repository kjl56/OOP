//create and maintain each player's deck of cards
#include "card.hpp"
#include <vector>
#include <algorithm>
#pragma once

class Deck
{
  public:
    Deck(std::vector<Card> stdDeck); //constructor
    void deckShuffle();
    Card cardReveal();
  private:
    int availableCards;
    std::vector<Card> playerDeck;
};
