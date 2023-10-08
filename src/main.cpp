#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "board.hpp"
#include "game_state_handler.hpp"

int main() {
  auto const window = std::make_shared<sf::RenderWindow>(
      sf::VideoMode(640, 480), std::string("Chess"), sf::Style::Default);
  window->setFramerateLimit(300);
  auto const board = std::make_shared<Board>(window);
  GameStateHandler state_handler(board, window);

  spdlog::set_level(spdlog::level::debug); // for now
  sf::Event event;
  while (window->isOpen()) {
    while (window->pollEvent(event)) {
      // handle events
      state_handler.handleEvent(event);
    }
    board->draw();
    state_handler.draw();
    window->display();
  }
}
