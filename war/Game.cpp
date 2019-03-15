#include "Game.hpp"

//constructor
Game::Game(int numOfPlayers)
{
  //initialize a standard deck of cards
  Deck stdDeck;
  stdDeck.deckShuffle();

  //give each player an equal part of the shuffled deck
  int numOfCards = 52/numOfPlayers;
  for (int i = 0; i < numOfPlayers; ++i)
  {
    Deck tempDeck(stdDeck, numOfCards);
    player tempPlayer(tempDeck);
    players.push_back(tempPlayer);
  }
}

//returns true if all players could draw a card, false otherwise
bool Game::drawCards()
{
  for (int i = 0; i < players.size(); ++i)
  {
    if (!players[i].moveCardToHand())
      return false;
  }
  return true;
}

//players reveal their top cards and compare
//player with highest card takes all cards
//if tie, each player adds two more cards and then resolves from there
void Game::compareCards()
{
  //have players reveal top card and compare
  /*
  int i = players.size();
  for (int j = 0; j < i; ++j)
  {

  }
  */
  Card p1Card = players[0].cardReveal(); 
  Card p2Card = players[1].cardReveal();
  
  //player with higher card value takes both player's hands and adds to their deck
  if (p1Card > p2Card)//p1 card higher
  {
    while (!players[1].isHandEmpty())
    {
      players[0].addCardToDeck(players[1].giveCardAway());
    }
  }
  else if (p1Card < p2Card)//p2 card higher
  {
    while (!players[0].isHandEmpty())
    {
      players[1].addCardToDeck(players[0].giveCardAway());
    }
  }
  else//cards have same rank
  {
    if (drawCards())
      return;
  }
}