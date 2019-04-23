#include <iostream>
#include <vector>
#include <fstream>
#include "main_headers.h"
#include "player.h"
#include "functions.h"
#include "quest_hero.h"

using std::vector;

int main() {
  vector<vector<int>> map_tiles(MAP_HEIGHT, vector<int>(MAP_WIDTH));
  vector<TileInfo> tiles(TILES_CNT);
  vector<QuestHero> quest_heroes;
  GetAllInformation(map_tiles, tiles, quest_heroes);

  sf::Image map_image;
  map_image.loadFromFile("img/map.png");
  sf::Texture map_texture;
  map_texture.loadFromImage(map_image);
  sf::Sprite map_sprite;
  map_sprite.setTexture(map_texture);

  int width = 2176, height = 1536;
  sf::View view;
  sf::RenderWindow main_window(sf::VideoMode(width, height), "Project228");
  view.reset(sf::FloatRect(0, 0, width, height));

  Player player("img/hulk.png", 1700, 1900, 100, 100, 100);

  sf::Clock timer_for_animation_;

  while (main_window.isOpen()) {
    auto time = timer_for_animation_.getElapsedTime().asMilliseconds();
    timer_for_animation_.restart();

    sf::Event event;
    vector<sf::Keyboard::Key> pressed_keys;  // for cheats
    while (main_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        main_window.close();
      }
      if (player.IsAlive()) {
        KeyboardTreatment(&player);
      }
      player.Move(time, map_tiles);
    }

    view.setCenter(player.GetX(), player.GetY());
    main_window.setView(view);

    main_window.clear(sf::Color(255, 255, 255));

    DrawMap(&main_window, map_tiles, tiles, map_sprite);
    DrawHeroes(&main_window, quest_heroes);

    main_window.draw(*player.GetSprite());
    main_window.display();
  }

  return 0;
}
