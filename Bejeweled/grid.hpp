//class representing the grid
#pragma once
#include "piece.hpp"
#include <vector>

class Grid
{
  public:
    Grid(int ,int); //creates empty grid with inputted dimensions
    void fillGrid(int); //fills entire grid with random pieces
    void swap(piece, piece); //swaps two pieces on the grid
    piece& returnPiece(int, int); //returns reference to selected piece

  private:
    std::vector< std::vector<piece> > pieceGrid;
};