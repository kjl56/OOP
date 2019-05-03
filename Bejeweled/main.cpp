#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "piece.hpp"
using namespace sf;

int ts = 54; //tile size
Vector2i offset(48,24);

struct game_state 
{
  int ts = 54; //tile size
  Vector2i offset(int i= 48,int j= 24);
  int x0,y0,x,y; int click=0; Vector2i pos;
  bool isSwap=false, isMoving=false;
};

struct event_listener {
    virtual void on_close(RenderWindow& w) { w.close(); }
    virtual void on_mouse_press_left(game_state& state) {
      if (!state.isSwap && !state.isMoving) state.click++;
      state.pos = Mouse::getPosition(window) - state.offset;
    }
};

struct event_source 
{
  event_source (RenderWindow& w)
    : window(w) {
  }

  void listen(event_listener& l)
  {
    listeners.push_back(&l);
  }

  template<typename F>
  void notify(F fn)
  {
    for (event_listener* l : listeners)
      fn(l);    
  }

  void process (Event const& e, game_state& state)
  {
    switch (e.type)
    {
      case Event::Closed :
        return notify( [e] (event_listener* l) { l->on_close(window); } );
        //window.close();
        //break;
      case Event::MouseButtonPressed :
        if (e.mouseButton.button == Mouse::Left)
        {
          return notify( [e] (event_listener* l) { l->on_mouse_press_left(state); } );
          //if (!state.isSwap && !state.isMoving) state.click++;
          //state.pos = Mouse::getPosition(window) - state.offset;
        }
        //break;
      default :
        break;
    }

    /*if (e.type == Event::Closed)
      app.close();
        
    if (e.type == Event::MouseButtonPressed)
      if (e.mouseButton.button == Mouse::Left)
      {
        if (!isSwap && !isMoving) click++;
        pos = Mouse::getPosition(app)-offset;
      }*/
  }
  
  void poll (game_state& state)
  {
    Event e;
    while (window.pollEvent(e))
    {
      process(e, state);
    }
  }

  RenderWindow& window;
  std::vector<event_listener*> listeners;
};

int main()
{
  int gridX = 10, gridY = 10;
  Grid grid(gridX, gridY);

  RenderWindow app(VideoMode(740,480), "Match-3 Game!");
  app.setFramerateLimit(60);

  event_source events(app);
  event_listener list;
  events.listen(list);

  game_state state;

  Texture t1,t2,t3;
  t1.loadFromFile("images/background.png");
  t2.loadFromFile("images/gems.png");
  t3.loadFromFile("images/cursor.png");

  Sprite background(t1), gems(t2), cursor(t3);
  cursor.setColor(Color::Transparent);

  grid.fillGrid(ts);
  
  //game will keep track of which pieces are matched instead of the pieces themselves
  //std::vector<std::pair<int, int>> matchingPieces;

  int x0,y0,x,y; int click=0; Vector2i pos;
  bool isSwap=false, isMoving=false;

  while (app.isOpen())
  {
    //makes adjustments so resizing window doesnt mess up clicking
    Vector2u windowSize = app.getSize();
    ts *= windowSize.y/480;

    events.poll(state);
    /*Event e;
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
    }*/
	
    // mouse click
    if (click==1)
    {
      x0=pos.x/ts+1;
      y0=pos.y/ts+1;
      cursor.setPosition(x0*ts + offset.x-ts, y0*ts + offset.y-ts);
      cursor.setColor(Color::White);
    }
    if (click==2)
    {
      x=pos.x/ts+1;
      y=pos.y/ts+1;
      if (abs(x-x0)+abs(y-y0)==0)//if piece was double clicked
      {
        click = 1;
        piece &p = grid.returnPiece(y0, x0);
        if ( p.kind == 6)//check if it is a bomb
        {
          for (int n = -1; n <= 1; ++n)
            for (int x = -1; x <= 1; ++x)
            {
              piece &tempPiece = grid.returnPiece(y0+n, x0+x);
              tempPiece.match++;
            }
          click = 0;
          cursor.setColor(Color::Transparent);
        }
      }
      else if (abs(x-x0)+abs(y-y0)==1)
      {
        cursor.setColor(Color::Transparent);
        grid.swap(grid.returnPiece(y0, x0), grid.returnPiece(y, x));
        isSwap=1; click=0;
      }
      else click=1;
    }

    //Match finding
    for(int i=1;i<=8;i++)
      for(int j=1;j<=8;j++)
      {
        //idea: make stack, put matched pieces on stack, pop them off when removed from game
        if (grid.returnPiece(i, j) == grid.returnPiece(i+1, j))
          if (grid.returnPiece(i, j) == grid.returnPiece(i-1, j))
            for (int n = -1; n <= 1; n++)
            {
              piece &tempPiece = grid.returnPiece(i+n, j);
              tempPiece.match++;
            }
        if (grid.returnPiece(i, j) == grid.returnPiece(i, j+1))
          if (grid.returnPiece(i, j) == grid.returnPiece(i, j-1))
            for (int n = -1; n <= 1; n++)
            {
              piece &tempPiece = grid.returnPiece(i, j+n);
              tempPiece.match++;
            }
      }

    //Moving animation
    isMoving=false;
    for (int i=1;i<=8;i++)
      for (int j=1;j<=8;j++)
      {
        piece &p = grid.returnPiece(i, j);
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

    //Deleting animation
    if (!isMoving)
      for (int i=1;i<=8;i++)
        for (int j=1;j<=8;j++)
        {
          piece &tempPiece = grid.returnPiece(i, j);
          if (tempPiece.match)
            if (tempPiece.alpha > 10)
            {
              tempPiece.alpha -= 10;
              isMoving = true;
            }
        }

    //Get score
    int score=0;
    for (int i=1;i<=8;i++)
      for (int j=1;j<=8;j++)
      {
        piece &tempPiece = grid.returnPiece(i, j);
        score += tempPiece.match;
      }

    //Second swap if no match
    if (isSwap && !isMoving)
    {
      if (!score) 
        grid.swap(grid.returnPiece(y0, x0), grid.returnPiece(y, x));
      isSwap = 0;
    }

    //Update grid
    if (!isMoving)
    {
      grid.updateGrid(ts);
    }

    //////draw///////
    app.draw(background);

	  for (int i = 1; i <= 8; i++)
      for (int j = 1; j <= 8; j++)
      {
        piece &p = grid.returnPiece(i, j);
        gems.setTextureRect(IntRect(p.kind*49, 0, 49, 49));
        gems.setColor(Color(255, 255, 255, p.alpha));
        gems.setPosition(p.x, p.y);
        gems.move(offset.x-ts, offset.y-ts);
        app.draw(gems);
      }

    app.draw(cursor);

    app.display();
  }
  return 0;
}

/*
stuff to do
-make custom grids
-game should keep track of matches, not the pieces themselves
-grid should exclusively keep track of where pieces are, not the pieces themselves
-fix out of bounds bug that crashes game when you click to switch a piece to the right of the board
-fix window resize bug (pieces cant be properly clicked when window is resized)
*/