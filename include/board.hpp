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
public:
  Board(std::shared_ptr<sf::RenderWindow> window);
  void draw();
  std::vector<Move> getValidMoves();
  void makeMove(Move m);
  std::string toString(Move m);
  Piece get_clicked_piece(int x, int y);
};