#pragma once

#include <array>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "move.hpp"
#include "piece.hpp"

class Board
{
private:
  std::array<std::array<Piece, 8>, 8> board_state_;
  std::shared_ptr<sf::RenderWindow> window_;
  bool white_to_move_ = 1;
  sf::RectangleShape white_squares_;
  std::vector<sf::RectangleShape> black_squares_;
  // below default is from http://omgchess.blogspot.com/2015/09/chess-board-color-schemes.html
  sf::Color black_square_color_ = sf::Color(112,102,119);
  sf::Color white_square_color_ = sf::Color(204,183,174);
  sf::Color background_color_ = sf::Color(18, 72, 138); // nice blue color
  std::string indexToSquareName(sf::Vector2i);
  std::unordered_map<Piece, sf::Texture> piece_textures_;
public:
  Board(std::shared_ptr<sf::RenderWindow> window);
  void draw();
  std::vector<Move> getValidMoves();
  void makeMove(Move m);
  Piece getClickedPiece(sf::Vector2i);
  bool coordinateOnBoard(sf::Vector2i);
};