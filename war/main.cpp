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

void createStdDeck(std::vector<Card> stdDeck)
{
  for (int i = 0; i < 52; ++i)
  {
    Rank r = static_cast<Rank>(i % 13);
    Suit s = static_cast<Suit>(i / 13);
    Card stdCard(r, s);
    stdDeck.push_back(stdCard);
  }
  //shuffle the deck so it can be dealt to players
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(std::begin(stdDeck), std::end(stdDeck), std::default_random_engine(seed));
}

int main()
{
  //initialize a standard deck of cards
  std::vector<Card> stdDeck;
  createStdDeck(stdDeck);

  //give each player half of a shuffled deck
  playerDeck p1Deck(stdDeck);
  playerDeck p2Deck(stdDeck);

  //game loop
  bool canPlay = true;
  while (canPlay)
  {
    //have players reveal top card and compare
    Card p1Card = p1Deck.cardReveal();
    Card p2Card = p2Deck.cardReveal();
    //player with higher card value takes both cards and adds to bottom of deck, face up
    if (p1Card.getRank() > p2Card.getRank())//p1 card higher
    {
      p1Deck.addCard(p2Card);
      canPlay = p2Deck.removeCard();
    }
    else if (p1Card.getRank() < p2Card.getRank())//p2 card higher
    {
      canPlay = p1Deck.removeCard();
      p2Deck.addCard(p1Card);
    }
    //if tie, both players add two more cards to field, one face down, one face up
    else//cards have same rank
    {
    //tie resolved from new face up card

    }
    //when a face up card is reached in a player's deck, their deck is shuffled and play is continued

    //game ends when one player runs out of cards

  }
  return 0;
}
