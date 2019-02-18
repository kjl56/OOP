#include "deck.hpp"

//default constructor
//makes a full deck from nothing
Deck::Deck()
{
  for (int i = 0; i < 52; ++i)
  {
    Rank r = static_cast<Rank>(i % 13);
    Suit s = static_cast<Suit>(i / 13);
    Card stdCard(r, s);
    deckOfCards.push_back(stdCard);
  }
  topOfDeck = deckOfCards.size();
}

//secondary constructor
//makes a deck for a player by taking a specified number of cards from a given deck
Deck::Deck(Deck cardDeck, int numOfCards)
{
  for (int i = 0; i < numOfCards; ++i)
  {
    deckOfCards.push_back(cardDeck.getTopCard());
  }
  topOfDeck = deckOfCards.size();
}

//shuffles the deck and resets topOfDeck
void Deck::deckShuffle()
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(std::begin(deckOfCards), std::end(deckOfCards), std::default_random_engine(seed));
  topOfDeck = deckOfCards.size();
}

//checks status of TopOfDeck
bool Deck::isDeckEmpty()
{
  if (topOfDeck == 0)
    return true;
  return false;
}

//removes the top card from the deck and returns it
Card Deck::getTopCard()
{
  Card tempCard = deckOfCards[topOfDeck];
  deckOfCards.erase(deckOfCards.begin()+topOfDeck);
  --topOfDeck;
  return tempCard;
}

//adds a card to the deck
void Deck::addCard(Card c)
{
  deckOfCards.push_back(c);
}