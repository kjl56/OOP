//class definitions
#include "time.h"
#include "stdlib.h"
#include "grid.hpp"

//constructor
//creates a grid of empty pieces with width x and height y
Grid::Grid(int x, int y)
{
  piece tempPiece;
  for (int i = 0; i < x; ++i)
  {
    std::vector<piece> col (y, tempPiece);
    pieceGrid.push_back(col);
  }
}

//fills the entire grid with random pieces
void Grid::fillGrid(int ts)
{
  srand(time(0));
  
  for (int i=1;i<=8;i++)
    for (int j=1;j<=8;j++)
    {
      pieceGrid[i][j].kind=rand()%3;
      pieceGrid[i][j].col=j;
      pieceGrid[i][j].row=i;
      pieceGrid[i][j].x = j*ts;
      pieceGrid[i][j].y = i*ts;
    }
}

//swaps the position of two pieces on the Grid
void Grid::swap(piece p1,piece p2)
{
  std::swap(p1.col,p2.col);
  std::swap(p1.row,p2.row);

  pieceGrid[p1.row][p1.col]=p1;
  pieceGrid[p2.row][p2.col]=p2;
}

//returns a reference to the selected piece
piece& Grid::returnPiece(int x, int y)
{
  return pieceGrid[x][y];
}

//updates grid pieces after matches have been made
void Grid::updateGrid(int ts)
{
  for(int i = 8; i > 0; i--)
    for(int j = 1; j <= 8; j++)
    {
      if (pieceGrid[i][j].match)
        for(int n = i; n > 0; n--)
        {
          if (!pieceGrid[n][j].match)
          {
            swap(pieceGrid[n][j], pieceGrid[i][j]);
            break;
          };
        }
    }

  //makes new random pieces
  for(int j = 1; j <= 8; j++)
    for(int i = 8, n = 0; i > 0; i--)
    {
      if (pieceGrid[i][j].match)
      {
        int randNum = rand()%61;
        if (randNum < 10)//0-9
          pieceGrid[i][j].kind = 0;
        else if (randNum < 20)//10-19
          pieceGrid[i][j].kind = 1;
        else if (randNum < 30)//20-29
          pieceGrid[i][j].kind = 2;
        else if (randNum < 40)//30-39
          pieceGrid[i][j].kind = 3;
        else if (randNum < 50)//40-49
          pieceGrid[i][j].kind = 4;
        else if (randNum < 60)//50-59
          pieceGrid[i][j].kind = 5;
        else//60
          pieceGrid[i][j].kind = 6;//bomb
        
        pieceGrid[i][j].y = -ts*n++;
        pieceGrid[i][j].match = 0;
        pieceGrid[i][j].alpha = 255;
      }
    }
}