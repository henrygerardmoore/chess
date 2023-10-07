#include "board.hpp"

#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

int main() {
  auto const window = std::make_shared<sf::RenderWindow>(
      sf::VideoMode(640, 480), std::string("Chess"), sf::Style::Default);
  window->setFramerateLimit(300);
  Board board(window);

  sf::Event event;
  while (window->isOpen()) {
    while (window->pollEvent(event)) {
      // handle events
      if (event.type == sf::Event::Closed) {
        window->close();
      }
    }
    board.draw();
  }
}
