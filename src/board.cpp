#include <algorithm>

#include <spdlog/spdlog.h>

#include "board.hpp"

Board::Board(std::shared_ptr<sf::RenderWindow> window) : window_(window) {
  for (std::size_t i = 0; i < 32; ++i) {
    black_squares_.emplace_back();
  }
}

void Board::draw() {
  // draw background
  window_->clear(background_color_);

  // resize window view
  auto const dims = window_->getSize();
  window_->setView(sf::View(sf::FloatRect(0, 0, dims.x, dims.y)));

  // get smaller dimension and use that as the ideal board edge
  auto const ideal_board_edge = dims.x < dims.y ? dims.x : dims.y;
  auto const square_edge = ideal_board_edge / 8; // rounds down implicitly
  auto const board_edge = 8 * square_edge;
  auto const x_offset = (dims.x - board_edge) / 2;
  auto const y_offset = (dims.y - board_edge) / 2;

  // set white square color and size
  white_squares_.setFillColor(white_square_color_);
  white_squares_.setSize({static_cast<float>(board_edge), static_cast<float>(board_edge)});

  // set each black square color and size
  std::for_each(black_squares_.begin(), black_squares_.end(), [&](sf::RectangleShape& square){square.setFillColor(black_square_color_);});
  std::for_each(black_squares_.begin(), black_squares_.end(), [&](sf::RectangleShape& square){square.setSize({static_cast<float>(square_edge), static_cast<float>(square_edge)});});

  // set white square location and size
  white_squares_.setPosition(x_offset, y_offset);
  window_->draw(white_squares_);

  // set each black square location and size
  for (std::size_t i = 0; i < 8; ++i) {
    for (std::size_t j = 0; j < 4; ++j) {
      auto & cur_square = black_squares_.at(i * 4 + j);
      sf::Vector2f cur_square_position;
      cur_square_position.y = i * square_edge + y_offset;
      cur_square_position.x = 2 * j * square_edge + x_offset;

      // every other row of black squares is offset by one square to create the checkerboard
      if (i % 2 == 0) {
        cur_square_position.x += square_edge;
      }
      cur_square.setPosition(cur_square_position);
      window_->draw(cur_square);
    }
  }

  // TODO(henrygerardmoore): display pieces
}

std::vector<Move> Board::getValidMoves() {
  // TODO(henrygerardmoore): implement returning vector of valid moves at a given board state
  return {};
}

void Board::makeMove(Move m) {
  // TODO(henrygerardmoore): implement making a move
}

std::string Board::toString(Move m) {
  return "";
}

Piece Board::getClickedPiece(sf::Vector2i mouse_point) {
  auto const pos_rel_top_left = mouse_point - sf::Vector2i(white_squares_.getPosition());
  auto const square_edge = static_cast<int>(black_squares_[0].getSize().x);
  sf::Vector2i const index = {pos_rel_top_left.x / square_edge, pos_rel_top_left.y / square_edge};
  spdlog::debug("Clicked on square {}", indexToSquareName(index));
  try {
    return board_state_.at(index.y).at(index.x);
  } catch(std::out_of_range const& e) {
    throw std::domain_error("Mouse position not on chess board");
  }
}

std::string Board::indexToSquareName(sf::Vector2i index) {
  std::string square_name;
  char file = 97 + index.x; // a is character 97, and we count columns from the left
  char rank = 56 - index.y; // 8 is character 56, we count rows opposite order from chess
  square_name += file;
  square_name += rank;
  return square_name;
}

bool Board::coordinateOnBoard(sf::Vector2i point) {
  sf::Vector2i minPoint{static_cast<int>(white_squares_.getPosition().x), static_cast<int>(white_squares_.getPosition().y)};
  sf::Vector2i maxPoint = minPoint + sf::Vector2i{static_cast<int>(white_squares_.getSize().x), static_cast<int>(white_squares_.getSize().y)};
  return (point.x >= minPoint.x && point.x <= maxPoint.x && point.y >= minPoint.y && point.y <= maxPoint.y);
}