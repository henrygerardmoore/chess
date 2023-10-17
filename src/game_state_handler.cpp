#include <spdlog/spdlog.h>

#include "game_state_handler.hpp"

GameStateHandler::GameStateHandler(std::shared_ptr<Board> board, std::shared_ptr<sf::RenderWindow> window) : board_(board), window_(window) {

}

void GameStateHandler::handleEvent(sf::Event event) {
  switch (event.type)
  {
  case sf::Event::Closed:
    window_->close();
    break;
  
  case sf::Event::MouseButtonPressed:
    {
      auto pos = sf::Mouse::getPosition(*window_);
      if (board_->coordinateOnBoard(pos)) {
        auto const& piece = board_->getClickedPiece(pos);
        spdlog::debug("Clicked on {}",  pieceToString(piece));
        // TODO (henrygerardmoore): piece handling
      }
    }
  default:
  break;
  }
}

void GameStateHandler::draw() {

}