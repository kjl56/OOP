/*
COPYRIGHT (C) 2019 Kyle Lugo (4148313) All rights reserved.
OOP Assignment 1
Author.  Kyle Lugo
        kjl56@zips.uakron.edu
Version. 1.00 01.28.2019
*/

#include <iostream>
#include "playerDeck.hpp"
#include "card.hpp"

int main()
{
  //initialize a standard deck of cards
  std::vector<Card> stdDeck;
  Card stdCard;
  for (int i = Card::club; i <= Card::spade; i++)
  {
    for (int j = Card::two; j <= Card::ace; j++)
    {
      stdCard.Suit = i;
      stdCard.Rank = j;
      stdDeck.push_back(stdCard);
    }
  }
  //shuffle the deck before dealing them to the players
  std::shuffle(std::begin(stdDeck), std::end(stdDeck));

  //give each player half of a shuffled deck
  Deck p1Deck(stdDeck);
  Deck p2Deck(stdDeck);

  //game loop
  bool canPlay = true;
  while (canPlay)
  {
    //have players reveal top card and compare
    //player with higher card value takes both cards and adds to bottom of deck, face up
    //if tie, both players add two more cards to field, one face down, one face up
    //tie resolved from new face up card
    //when a face up card is reached in a player's deck, their deck is shuffled and play is continued
    //game ends when one player runs out of cards
  }
  return 0;
}
