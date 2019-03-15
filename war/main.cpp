/*
COPYRIGHT (C) 2019 Kyle Lugo (4148313) All rights reserved.
OOP Practice Assignment
Author. Kyle Lugo
        kjl56@zips.uakron.edu
*/

#include <iostream>
#include "Game.hpp"

int main()
{
  int numOfPlayers = 2;
  Game War(numOfPlayers);

  std::cout << "Game has started." << std::endl;
  
  //game loop
  bool gameContinue = true;
  while (gameContinue)
  {
    if (War.drawCards())
    {
      War.compareCards();
    }
    else
    {
      gameContinue = false;
    }
  }

  std::cout << "Game has ended. Press enter to continue...";
  std::cin.get();

  return 0;
}
