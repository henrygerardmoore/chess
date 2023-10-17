#pragma once

#include <string>

#include <type_traits>

enum class Piece {
  empty,
  b_pawn,
  b_knight,
  b_bishop,
  b_rook,
  b_queen,
  b_king,
  w_pawn,
  w_knight,
  w_bishop,
  w_rook,
  w_queen,
  w_king
};


inline std::string pieceToString(Piece piece) {
  switch (piece)
  {
  case Piece::b_pawn:
    return "black_pawn";
  case Piece::w_pawn:
    return "white_pawn";
  case Piece::b_knight:
    return "black_knight";
  case Piece::w_knight:
    return "white_knight";
  case Piece::b_bishop:
    return "black_bishop";
  case Piece::w_bishop:
    return "white_bishop";
  case Piece::b_rook:
    return "black_rook";
  case Piece::w_rook:
    return "white_rook";
  case Piece::b_queen:
    return "black_queen";
  case Piece::w_queen:
    return "white_queen";
  case Piece::b_king:
    return "black_king";
  case Piece::w_king:
    return "white_king";
  default:
    return "empty square";
  }
}

// https://stackoverflow.com/questions/261963/how-can-i-iterate-over-an-enum
template < typename C, C beginVal, C endVal>
class Iterator {
  typedef typename std::underlying_type<C>::type val_t;
  int val;
public:
  Iterator(const C & f) : val(static_cast<val_t>(f)) {}
  Iterator() : val(static_cast<val_t>(beginVal)) {}
  Iterator operator++() {
    ++val;
    return *this;
  }
  C operator*() { return static_cast<C>(val); }
  Iterator begin() { return *this; }
  Iterator end() {
      static const Iterator endIter=++Iterator(endVal);
      return endIter;
  }
  bool operator!=(const Iterator& i) { return val != i.val; }
};

typedef Iterator<Piece, Piece::empty, Piece::w_king> pieceIterator;
