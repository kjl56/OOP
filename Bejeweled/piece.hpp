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

//operator overloads
inline bool operator<(const piece& p1, const piece& p2)
{
  return p1.kind < p2.kind;
}

inline bool operator>(const piece& p1, const piece& p2)
{
  return p2 < p1;
}

inline bool operator<=(const piece& p1, const piece& p2)
{
  return !(p1 > p2);
}

inline bool operator>=(const piece& p1, const piece& p2)
{
  return !(p1 < p2);
}

inline bool operator==(const piece& p1, const piece& p2)
{
  return p1.kind == p2.kind;
}

inline bool operator!=(const piece& p1, const piece& p2)
{
  return !(p1 == p2);
}