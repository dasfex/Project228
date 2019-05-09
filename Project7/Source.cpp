#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include "draw.h"
#include "main_headers.h"
#include "player.h"
#include "functions.h"
#include "quest_hero.h"
#include "attack.h"
using std::vector;

int main() {
  vector<vector<int>> map_tiles(MAP_HEIGHT, vector<int>(MAP_WIDTH));
  vector<TileInfo> tiles(TILES_CNT);
  vector<QuestHero> quest_heroes;
  sf::Font text_font;
  GetAllInformation(map_tiles, tiles, quest_heroes, &text_font);
  sf::Text text("", text_font, 25);
  std::pair<bool, sf::Text> get_exp_text =
      std::make_pair(false, sf::Text("", text_font, 25));

  std::pair<bool, std::string> is_text(false, "");
  bool is_show_missions = false;
  bool is_show_bullet = false;
  sf::Sprite map_sprite;
  sf::Sprite quests_background;
  //  я честно пытался обернуть нижний блок в функцию,
  //  но sfml не любит, когда создают указатели на sf::Sprite,
  //  а по ссылке передавать просто ничего не работает,
  //  так что просто оставим так.
  sf::Image map_img;
  map_img.loadFromFile("img/map.png");
  sf::Texture map_texture;
  map_texture.loadFromImage(map_img);
  map_sprite.setTexture(map_texture);
  map_img.loadFromFile("img/missions.png");
  sf::Texture quests_background_texture;
  quests_background_texture.loadFromImage(map_img);
  quests_background.setTexture(quests_background_texture);
  quests_background.setTextureRect(sf::IntRect(0, 0, 340, 510));
  //  конец стрёмного блока

  int width = 2176, height = 1536;
  sf::View view;
  sf::RenderWindow main_window(sf::VideoMode(width, height), "Project228");
  view.reset(sf::FloatRect(0, 0, width, height));

  Player player("img/hulk.png", 1600, 2500, 100, 100, 100); //  1600 2500

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
        KeyboardTreatment(&player, quest_heroes, &is_text,
                          &text, &get_exp_text,
                          is_show_missions, is_show_bullet);
      }
      player.Move(time, map_tiles, quest_heroes);
    }

    view.setCenter(player.GetCoor());
    main_window.setView(view);
    text.setPosition(view.getCenter() + sf::Vector2f(-700, 300));

    main_window.clear(sf::Color(255, 255, 255));

    DrawMap(&main_window, map_tiles, tiles, map_sprite);
    DrawHeroes(&main_window, quest_heroes);
    DrawMainInfo(&main_window, &player, text_font);
    if (is_show_missions) {
      DrawMissions(&main_window,
                   player,
                   quests_background,
                   text_font,
                   is_show_missions);
    }
    if (get_exp_text.first) {
      DrawExp(&main_window, player, &get_exp_text);
    }
    if (is_show_bullet) {
      DrawBullet(&main_window, &player, is_show_bullet);
    }
    main_window.draw(*player.GetSprite());
    main_window.draw(text);

    main_window.display();
  }

  return 0;
}
