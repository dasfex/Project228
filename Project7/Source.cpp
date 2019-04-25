#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include "main_headers.h"
#include "player.h"
#include "functions.h"
#include "quest_hero.h"

using std::vector;

int main() {
  vector<vector<int>> map_tiles(MAP_HEIGHT, vector<int>(MAP_WIDTH));
  vector<TileInfo> tiles(TILES_CNT);
  vector<QuestHero> quest_heroes;
  sf::Font text_font;
  GetAllInformation(map_tiles, tiles, quest_heroes, &text_font);
  sf::Text text("", text_font, 25);

  std::pair<bool, std::string> is_text(false, "");

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

  Player player("img/hulk.png", 1900, 1900, 100, 100, 100);

  sf::Clock timer_for_animation_;

  while (main_window.isOpen()) {
    auto time = timer_for_animation_.getElapsedTime().asMilliseconds();
    timer_for_animation_.restart();

    sf::Event event{};
    vector<sf::Keyboard::Key> pressed_keys; // for cheats
    while (main_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        main_window.close();
      }
      if (player.IsAlive()) {
        KeyboardTreatment(&player, quest_heroes, &is_text, &text);
      }
      player.Move(time, map_tiles, quest_heroes);
    }

    view.setCenter(player.GetX(), player.GetY());
    main_window.setView(view);
    text.setPosition(view.getCenter().x - 500, view.getCenter().y + 300);

    main_window.clear(sf::Color(255, 255, 255));

    DrawMap(&main_window, map_tiles, tiles, map_sprite);
    DrawHeroes(&main_window, quest_heroes);

    main_window.draw(*player.GetSprite());
    main_window.draw(text);

    main_window.display();
  }

  return 0;
}
