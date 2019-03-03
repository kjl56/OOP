#include <SFML/Graphics.hpp>
//#include <time.h>
#include "grid.hpp"
#include "piece.hpp"
using namespace sf;

int ts = 54; //tile size
Vector2i offset(48,24);

int main()
{
  Grid grid(10, 10);

  //srand(time(0));

  RenderWindow app(VideoMode(740,480), "Match-3 Game!");
  app.setFramerateLimit(60);

  Texture t1,t2;
  t1.loadFromFile("images/background.png");
  t2.loadFromFile("images/gems.png");

  Sprite background(t1), gems(t2);

  grid.fillGrid(ts);
	/*for (int i=1;i<=8;i++)
    for (int j=1;j<=8;j++)
    {
      grid[i][j].kind=rand()%3;
      grid[i][j].col=j;
      grid[i][j].row=i;
      grid[i][j].x = j*ts;
      grid[i][j].y = i*ts;
    }*/

  int x0,y0,x,y; int click=0; Vector2i pos;
  bool isSwap=false, isMoving=false;

  while (app.isOpen())
  {
    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed)
        app.close();
			   	
			if (e.type == Event::MouseButtonPressed)
				if (e.mouseButton.button == Mouse::Left)
				{
				  if (!isSwap && !isMoving) click++;
				  pos = Mouse::getPosition(app)-offset;
        }
    }
	
    // mouse click
    if (click==1)
    {
      x0=pos.x/ts+1;
      y0=pos.y/ts+1;
    }
    if (click==2)
    {
      x=pos.x/ts+1;
      y=pos.y/ts+1;
      if (abs(x-x0)+abs(y-y0)==1)
      {
        grid.swap(grid.returnPiece(y0, x0), grid.returnPiece(y, x));
        //swap(grid[y0][x0],grid[y][x]);
        isSwap=1; click=0;
      }
      else click=1;
    }

    //Match finding
    for(int i=1;i<=8;i++)
      for(int j=1;j<=8;j++)
      {
        if (grid.returnPiece(i, j) == grid.returnPiece(i+1, j))
        {
          if (grid.returnPiece(i, j) == grid.returnPiece(i-1, j))
          {
            for (int n = -1; n <= 1; n++)
            {
              piece &tempPiece = grid.returnPiece(i+n, j);
              tempPiece.match++;
            }
          }
        }
        if (grid.returnPiece(i, j) == grid.returnPiece(i, j+1))
        {
          if (grid.returnPiece(i, j) == grid.returnPiece(i, j-1))
          {
            for (int n = -1; n <= 1; n++)
            {
              piece &tempPiece = grid.returnPiece(i, j+n);
              tempPiece.match++;
            }
          }
        }

      /*if (grid[i][j].kind==grid[i+1][j].kind)
          if (grid[i][j].kind==grid[i-1][j].kind)
            for(int n=-1;n<=1;n++) 
              grid[i+n][j].match++;

        if (grid[i][j].kind==grid[i][j+1].kind)
          if (grid[i][j].kind==grid[i][j-1].kind)
            for(int n=-1;n<=1;n++) 
              grid[i][j+n].match++;*/
      }

    //Moving animation
    isMoving=false;
    for (int i=1;i<=8;i++)
      for (int j=1;j<=8;j++)
      {
        piece &p = grid.returnPiece(i, j);
        //piece &p = grid[i][j];
        int dx,dy;
        for(int n=0;n<4;n++)   // 4 - speed
        {
          dx = p.x-p.col*ts;
          dy = p.y-p.row*ts;
          if (dx) 
            p.x-=dx/abs(dx);
          if (dy) 
            p.y-=dy/abs(dy);
        }
        if (dx||dy) 
          isMoving=1;
      }

    //Deleting amimation
    if (!isMoving)
      for (int i=1;i<=8;i++)
      {
        for (int j=1;j<=8;j++)
        {
          piece &tempPiece = grid.returnPiece(i, j);
          if (tempPiece.match)
          {
            if (tempPiece.alpha > 10)
            {
              tempPiece.alpha -= 10;
              isMoving = true;
            }
          }
          /*if (grid[i][j].match) 
              if (grid[i][j].alpha>10) 
              {
                grid[i][j].alpha-=10; 
                isMoving=true;
              }*/
        }
      }

    //Get score
    int score=0;
    for (int i=1;i<=8;i++)
    {
      for (int j=1;j<=8;j++)
      {
        piece &tempPiece = grid.returnPiece(i, j);
        score += tempPiece.match;
        //score+=grid[i][j].match;
      }
    }

    //Second swap if no match
    if (isSwap && !isMoving)
    {
      if (!score) 
      {
        grid.swap(grid.returnPiece(y0, x0), grid.returnPiece(y, x));
        //swap(grid[y0][x0],grid[y][x]);
      }
      isSwap=0;
    }

    //Update grid
    if (!isMoving)
    {
      for(int i = 8; i > 0; i--)
      {
        for(int j = 1; j <= 8; j++)
        {
          piece &tempPiece = grid.returnPiece(i, j);
          if (tempPiece.match)
          //if (grid[i][j].match)
          {
            for(int n = i; n > 0; n--)
            {
              if (!tempPiece.match)
              //if (!grid[n][j].match) 
              {
                grid.swap(grid.returnPiece(n, j), grid.returnPiece(i, j));
                //swap(grid[n][j],grid[i][j]); 
                break;
              };
            }
          }
        }
      }

      for(int j = 1; j <= 8; j++)
      {
        for(int i = 8, n = 0; i > 0; i--)
        {
          piece &tempPiece = grid.returnPiece(i, j);
          if (tempPiece.match)
          //if (grid[i][j].match)
          {
            tempPiece.kind = rand()%7;
            //grid[i][j].kind = rand()%7;
            tempPiece.y = -ts*n++;
            //grid[i][j].y = -ts*n++;
            tempPiece.match = 0;
            //grid[i][j].match=0;
            tempPiece.alpha = 255;
            //grid[i][j].alpha = 255;
          }
        }
      }
    }


    //////draw///////
    app.draw(background);

	  for (int i=1;i<=8;i++)
      for (int j=1;j<=8;j++)
      {
        piece &p = grid.returnPiece(i, j);
        //piece p = grid[i][j];
        gems.setTextureRect( IntRect(p.kind*49,0,49,49));
        gems.setColor(Color(255,255,255,p.alpha));
        gems.setPosition(p.x,p.y);
        gems.move(offset.x-ts,offset.y-ts);
        app.draw(gems);
      }

    app.display();
  }
  return 0;
}
