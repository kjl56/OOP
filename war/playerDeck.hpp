//create and maintain each player's deck of cards
#include "card.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#pragma once

class playerDeck
{
  public:
    playerDeck(std::vector<Card>);
    void deckShuffle();
    Card cardReveal();
    void addCard(Card);
    bool removeCard();
  private:
    int availableCards;
    std::vector<Card> Deck;
};
