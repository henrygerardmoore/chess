#include <algorithm>

#include <spdlog/spdlog.h>

#include "board.hpp"

Board::Board(std::shared_ptr<sf::RenderWindow> window) : window_(window) {
  for (std::size_t i = 0; i < 32; ++i) {
    black_squares_.emplace_back();
  }

  for (Piece piece_type : pieceIterator()) {
    if (piece_type == Piece::empty) {
      continue;
    }
    sf::Texture t;
    std::string filename = "./piece_images/" + pieceToString(piece_type) + ".png";
    if (!t.loadFromFile(filename)) {
      throw std::runtime_error("Unable to load " + pieceToString(piece_type) + " image. Check that " + filename + " exists and is readable.");
    }
    assert(t.getSize().x == t.getSize().y && "Piece textures must be square");
    piece_textures_[piece_type] =  t;
  }


  // set up pieces
  board_state_[0][0] = Piece::b_rook;
  board_state_[0][7] = Piece::b_rook;
  board_state_[7][0] = Piece::w_rook;
  board_state_[7][7] = Piece::w_rook;

  board_state_[0][1] = Piece::b_knight;
  board_state_[0][6] = Piece::b_knight;
  board_state_[7][1] = Piece::w_knight;
  board_state_[7][6] = Piece::w_knight;

  board_state_[0][2] = Piece::b_bishop;
  board_state_[0][5] = Piece::b_bishop;
  board_state_[7][2] = Piece::w_bishop;
  board_state_[7][5] = Piece::w_bishop;
  
  board_state_[0][3] = Piece::b_queen;
  board_state_[0][4] = Piece::b_king;
  board_state_[7][3] = Piece::w_queen;
  board_state_[7][4] = Piece::w_king;

  // set up pawns
  for (std::size_t i = 0; i < 8; ++i) {
    board_state_[1][i] = Piece::b_pawn;
    board_state_[6][i] = Piece::w_pawn;
  }
}

void Board::draw() {
  // draw background
  window_->clear(background_color_);

  // resize window view
  auto const dims = window_->getSize();
  window_->setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(dims.x), static_cast<float>(dims.y))));

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
  white_squares_.setPosition(static_cast<float>(x_offset), static_cast<float>(y_offset));
  window_->draw(white_squares_);

  // set each black square location and size and draw pieces
  for (std::size_t i = 0; i < 8; ++i) {
    for (std::size_t j = 0; j < 8; ++j) {
      sf::Vector2f cur_square_position;
      cur_square_position.y = static_cast<float>(i * square_edge + y_offset);
      cur_square_position.x = static_cast<float>(j * square_edge + x_offset);
      if ((i + j) % 2 == 1) {
        auto & cur_square = black_squares_.at(i * 4 + j / 2);

        cur_square.setPosition(cur_square_position);
        window_->draw(cur_square);
      }
      auto const piece = board_state_[i][j];
      if (piece != Piece::empty) {
        auto const& cur_texture = piece_textures_[piece];
        auto const texture_size = cur_texture.getSize(); // all our textures are square
        sf::Sprite piece_sprite;
        piece_sprite.setTexture(cur_texture);
        piece_sprite.setPosition(cur_square_position);
        piece_sprite.setScale(static_cast<float>(square_edge) / static_cast<float>(texture_size.x), static_cast<float>(square_edge) / static_cast<float>(texture_size.y));
        window_->draw(piece_sprite);
      }

    }
  }

  // TODO(henrygerardmoore): display pieces
}

std::vector<Move> Board::getValidMoves() {
  // TODO(henrygerardmoore): implement returning vector of valid moves at a given board state
  return {};
}

void Board::makeMove(Move /**/) {
  // TODO(henrygerardmoore): implement making a move
}

Piece Board::getClickedPiece(sf::Vector2i mouse_point) {
  auto const pos_rel_top_left = mouse_point - sf::Vector2i(white_squares_.getPosition());
  auto const square_edge = static_cast<int>(black_squares_[0].getSize().x);
  sf::Vector2i const index = {pos_rel_top_left.x / square_edge, pos_rel_top_left.y / square_edge};
  spdlog::debug("Clicked on square {}", indexToSquareName(index));
  spdlog::debug("Clicked on index ({},{})", index.x, index.y);
  try {
    return board_state_[static_cast<std::size_t>(index.y)][static_cast<std::size_t>(index.x)];
  } catch(std::out_of_range const& e) {
    throw std::domain_error("Mouse position not on chess board");
  }
}

std::string Board::indexToSquareName(sf::Vector2i index) {
  std::string square_name;
  char file = static_cast<char>(97 + index.x); // a is character 97, and we count columns from the left
  char rank = static_cast<char>(56 - index.y); // 8 is character 56, we count rows opposite order from chess
  square_name += file;
  square_name += rank;
  return square_name;
}

bool Board::coordinateOnBoard(sf::Vector2i point) {
  sf::Vector2i minPoint{static_cast<int>(white_squares_.getPosition().x), static_cast<int>(white_squares_.getPosition().y)};
  sf::Vector2i maxPoint = minPoint + sf::Vector2i{static_cast<int>(white_squares_.getSize().x), static_cast<int>(white_squares_.getSize().y)};
  return (point.x >= minPoint.x && point.x <= maxPoint.x && point.y >= minPoint.y && point.y <= maxPoint.y);
}