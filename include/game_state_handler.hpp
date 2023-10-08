#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "board.hpp"

class GameStateHandler
{
private:
  std::shared_ptr<Board> board_;
  std::shared_ptr<sf::RenderWindow> window_;
  bool piece_held_ = false;
public:
  GameStateHandler(std::shared_ptr<Board> board, std::shared_ptr<sf::RenderWindow> window);
  void handleEvent(sf::Event);
  void draw();
};