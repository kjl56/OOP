//define characteristics of a card
#pragma once

struct Card
{
  enum Suit
  {
    club, diamond, heart, spade
  };

  enum Rank
  {
    two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace
  };
};
