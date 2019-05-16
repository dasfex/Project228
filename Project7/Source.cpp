#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include "bullet.h"
#include "draw.h"
#include "enemy.h"
#include "functions.h"
#include "main_headers.h"
#include "menu.h"
#include "player.h"
#include "quest_hero.h"

using std::vector;

int main() {
  vector<vector<int>> map_tiles(MAP_HEIGHT, vector<int>(MAP_WIDTH));
  vector<TileInfo> tiles(TILES_CNT);
  vector<QuestHero> quest_heroes;
  vector<Enemy> enemies;
  sf::Font text_font;
  GetAllInformation(map_tiles, tiles, quest_heroes, enemies, &text_font);
  sf::Text text("", text_font, 25);
  std::pair<bool, sf::Text> get_exp_text =
      std::make_pair(false, sf::Text("", text_font, 25));

  std::pair<bool, std::string> is_text(false, "");
  std::pair<bool, std::pair<int, Direction>> is_show_bot_bullet;
  is_show_bot_bullet.first = false;
  bool is_show_missions = false;
  bool is_show_bullet = false;
  bool is_level_up = false;
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
  sf::Music music, menu_music;
  music.setLoop(true);
  Menu(&main_window, &music, &menu_music);
  view.reset(sf::FloatRect(0, 0, width, height));

  Player player("img/hulk.png", 1600, 2500, 100, 10, 8); //  1600 2500

  sf::Clock timer_for_animation_;

  while (main_window.isOpen()) {
    auto time = timer_for_animation_.getElapsedTime().asMilliseconds();
    timer_for_animation_.restart();

    sf::Event event{};
    while (main_window.pollEvent(event)) {
      bool is_menu = false;
      if (event.type == sf::Event::Closed) {
        main_window.close();
      }
      if (player.IsAlive()) {
        KeyboardTreatment(&player, quest_heroes, &is_text,
                          &text, &get_exp_text,
                          is_show_missions, is_show_bullet, is_level_up,
                          is_menu);
      }
      if (is_menu) {
        music.stop();
        Menu(&main_window,
             &music,
             &menu_music,
             player.GetCoor().x - 1100,
             player.GetCoor().y - 800);
        music.play();
        time = 0;
        timer_for_animation_.restart();
      }
      player.Move(&main_window, time, map_tiles, quest_heroes, enemies,
                  is_show_bot_bullet);
    }

    view.setCenter(player.GetCoor());
    main_window.setView(view);
    text.setPosition(view.getCenter() + sf::Vector2f(-700, 300));

    main_window.clear(sf::Color(255, 255, 255));

    ChangeEnemies(enemies, map_tiles, player.GetCoor(), time,
                  is_show_bot_bullet);

    DrawMap(&main_window, map_tiles, tiles, map_sprite);
    DrawEnemies(&main_window, enemies, text_font);
    DrawHeroes(&main_window, quest_heroes);
    DrawMainInfo(&main_window, &player, text_font);
    if (is_show_missions) {
      DrawMissions(&main_window,
                   player,
                   quests_background,
                   text_font,
                   is_show_missions);
    }
    if (is_show_bullet) {
      DrawBullet(&main_window, &player, is_show_bullet, enemies,
                 quest_heroes, get_exp_text, is_level_up);
    }
    if (is_show_bot_bullet.first) {
      DrawBotBullet(&main_window, is_show_bot_bullet, enemies, &player);
    }
    if (is_level_up) {
      DrawBuff(&main_window, player);
    }
    main_window.draw(*player.GetSprite());
    if (get_exp_text.first) {
      DrawExp(&main_window, player, &get_exp_text);
    }

    if (!player.IsAlive()) {
      GameEnd(&main_window, &music, "files/music/game_over.wav",
              "img/game_over.jpg", player.GetCoor().x - 1000,
              player.GetCoor().y - 600, &timer_for_animation_);
    }

    if (quest_heroes[3].IsQuestReady()) {
      GameEnd(&main_window, &music, "files/music/congratulation.wav",
              "img/congratulation.jpg", player.GetCoor().x - 1000,
              player.GetCoor().y - 600, &timer_for_animation_);
    }

    main_window.draw(text);

    main_window.display();
  }

  return 0;
}
