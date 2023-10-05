#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "board.hpp"

int main() {
  auto const window = std::make_shared<sf::RenderWindow>(
      sf::VideoMode(640, 480), std::string("Chess"),
      sf::Style::Resize);
  window->setFramerateLimit(300);
  Board board(window);
  while (window->isOpen()) {
    window->clear();
    board.draw();
  }
}
