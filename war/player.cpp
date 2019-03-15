#include "player.hpp"
//default constructor
player::player(Deck stdDeck)
{
  playerDeck = stdDeck;
}

//shuffles the player's deck
void player::shuffleDeck()
{
  playerDeck.deckShuffle();
}

//checks if the player's deck is empty; if so, returns false
//else, takes the top card of the player's deck, puts it into their hand, and then returns true
bool player::moveCardToHand()
{
  if( playerDeck.isDeckEmpty() )
  {
    shuffleDeck();
    if ( playerDeck.isDeckEmpty() )
      return false;
  }
  playerHand.push_back(playerDeck.getTopCard());
  return true;
}

//returns a reference to the last card in the player's hand
Card player::cardReveal()
{
  return playerHand.back();
}

//adds card to the player's deck
void player::addCardToDeck(Card cardToAdd)
{
  playerDeck.addCard(cardToAdd);
}

//returns a copy of the player's top card in their hand and then deletes it
Card player::giveCardAway()
{
  Card tempCard = playerHand.back();
  playerHand.pop_back();
  return tempCard;
}

//returns true if playerHand is empty, false if else
bool player::isHandEmpty()
{
  if (playerHand.empty())
    return true;
  return false;
}