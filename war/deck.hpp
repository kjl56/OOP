//creates a deck of cards
#include "card.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#pragma once

class Deck
{
  public:
    Deck();
    Deck(Deck, int);
    void deckShuffle();//shuffles deck and resets topOfDeck
    bool isDeckEmpty();//returns true if topOfDeck is 0, false if else
    Card getTopCard();//removes the card from the deck and returns it
    void addCard(Card);//adds card to deck
  private:
    int topOfDeck;
    std::vector<Card> deckOfCards;
};
