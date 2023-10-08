#pragma once

#include <string>

enum class Piece {
  empty,
  pawn,
  knight,
  bishop,
  rook,
  queen,
  king
};


inline std::string pieceToString(Piece piece) {
  switch (piece)
  {
  case Piece::pawn:
    return "pawn";
  case Piece::knight:
    return "knight";
  case Piece::bishop:
    return "bishop";
  case Piece::rook:
    return "rook";
  case Piece::queen:
    return "queen";
  case Piece::king:
    return "king";
  default:
    return "empty square";
  }
}