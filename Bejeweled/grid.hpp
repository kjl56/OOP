//class representing the grid
#pragma once
#include "piece.hpp"
#include <vector>

class Grid
{
  public:
    Grid(int ,int);
    void fillGrid(int);
    void swap(piece, piece);
    piece returnPiece(int, int);

  private:
    std::vector< std::vector<piece> > pieceGrid;
}