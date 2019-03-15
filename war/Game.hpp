/*Game class that encapsulates the execution of the Game of War.*/
#include "player.hpp"
#pragma once

class Game
{
  public:
    Game(int);//constructor
    bool drawCards();//returns true if all players could draw a card, false otherwise
    void compareCards();//players reveal top card and compare. Player with higher card takes all cards.
                        //if tie, each players adds two more cards and then resolves from there.
                        //currently only supports two players
  private:
  std::vector<player> players;
};