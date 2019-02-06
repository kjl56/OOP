//define characteristics of a card
#pragma once

enum Suit{
  club = 0, diamond, heart, spade
};

enum Rank{
  two = 0, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace
};

class Card
{
  public:
    Card(Rank r, Suit s)
      : cardRank(r), cardSuit(s){
    }
    //accessors
    Rank getRank() const {return cardRank;}
    Suit getSuit() const {return cardSuit;}
  //cards do not change after they are made
  private:
    Rank cardRank;
    Suit cardSuit;
};
