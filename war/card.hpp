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

inline bool operator<(const Card& c1, const Card& c2)
{
  return c1.getRank() < c2.getRank();
}

inline bool operator>(const Card& c1, const Card& c2)
{
  return c2 < c1;
}

inline bool operator<=(const Card& c1, const Card& c2)
{
  return !(c1 > c2);
}

inline bool operator>=(const Card& c1, const Card& c2)
{
  return !(c1 < c2);
}

inline bool operator==(const Card& c1, const Card& c2)
{
  return c1.getRank() == c2.getRank();
}

inline bool operator!=(const Card& c1, const Card& c2)
{
  return !(c1 == c2);
}