//parameters for a piece
#pragma once
struct piece
{
  int x, y, col, row, kind, match, alpha;
  piece()
  {
    match=0; 
    alpha=255;
  }
};