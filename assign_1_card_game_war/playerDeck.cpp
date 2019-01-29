#include "playerDeck.hpp"

//constructor
Deck::Deck(std::vector<Card> stdDeck)
{
  for (int i = 0; i < 26; ++i)
  {
    playerDeck.push_back(stdDeck.back());
    stdDeck.pop_back();
  }
}

//shuffles the player's deck
void Deck::deckShuffle()
{
  std::shuffle(std::begin(playerDeck), std::end(playerDeck));
}

//returns the first card in the player's deck for comparison
Card Deck::cardReveal()
{

}
