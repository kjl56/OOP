#include "playerDeck.hpp"

//constructor
playerDeck::playerDeck(std::vector<Card> stdDeck)
{
  for (int i = 0; i < 26; ++i)
  {
    Deck.push_back(stdDeck.back());
    stdDeck.pop_back();
  }
  availableCards = 26;
}

//shuffles the player's deck and resets the size of availableCards
void playerDeck::deckShuffle()
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(std::begin(Deck), std::end(Deck), std::default_random_engine(seed));
  availableCards = Deck.size();
}

//returns the top card in the player's deck for comparison
Card playerDeck::cardReveal()
{
  --availableCards;
  return Deck[availableCards];
}

//used when player wins card comparison
//adds a copy of the other players card to this player's deck
void playerDeck::addCard(Card c)
{
  Deck.push_back(c);
}

//used when player loses card comparison
//removes card at availableCards index so it can be added to other players deck without creating duplicates
//then returns false if availableCards is at 0 and the player has no more cards
//otherwise shuffles the deck and returns true
bool playerDeck::removeCard()
{
  Deck.erase(Deck.begin() + availableCards);
  if (availableCards == 0){
    if (Deck.empty()){
      return false;
    }
    else{
      deckShuffle();
      return true;
    }
  }
}
