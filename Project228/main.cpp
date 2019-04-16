#include <iostream>
#include <vector>
#include <fstream>
#include "main_headers.h"
#include "player.h"
#include "functions.h"

using std::vector;

int main() {
  vector<vector<int>> map_tiles(MAP_HEIGHT_FIRST, vector<int>(MAP_WIDTH_FIRST));
  vector<TileInfo> tiles(TILES_CNT);
  GetAllInformation(map_tiles, tiles);

  sf::Image map_image;
  map_image.loadFromFile("img/map.png");
  sf::Texture map_texture;
  map_texture.loadFromImage(map_image);
  sf::Sprite map_sprite;
  map_sprite.setTexture(map_texture);

  int width = 2176, height = 1536;
  sf::View view;
  sf::RenderWindow main_window(sf::VideoMode(static_cast<unsigned int>(width),
                                     static_cast<unsigned int>(height)), "Project228");
  view.reset(sf::FloatRect(0, 0, width, height));

  Player player("hulk.png", 1700, 1900, 100, 100, 100);

  sf::Clock timer_for_animation_;

  while (main_window.isOpen()) {
    double time = timer_for_animation_.getElapsedTime().asMicroseconds();
    timer_for_animation_.restart();

    sf::Event event;
    while (main_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        main_window.close();
      }

      if (player.IsAlive()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
          player.SetDirection(Direction::N);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
          player.SetDirection(Direction::W);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
          player.SetDirection(Direction::S);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
          player.SetDirection(Direction::E);
        } else {
          player.SetDirection(Direction::STAY);
        }
      }
      player.Move(time / 1000, map_tiles);
    }

    view.setCenter(player.GetX(), player.GetY());
    main_window.setView(view);

    main_window.clear(sf::Color(255, 255, 255));

    DrawMap(&main_window, map_tiles, tiles, map_sprite);

    main_window.draw(*player.GetSprite());
    main_window.display();
  }

  return 0;
}
