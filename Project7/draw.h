#ifndef NEWPROJECT228_DRAW_H
#define NEWPROJECT228_DRAW_H

#include "constants.h"
#include "enemy.h"
#include "main_headers.h"
#include "functions.h"
#include "quest_hero.h"
#include "player.h"
#include <vector>

void DrawHeroes(sf::RenderWindow* window,
                const std::vector<QuestHero>& heroes) {
  for (const auto& hero : heroes) {
    if (!hero.IsHeroExist()) {
      continue;
    }
    window->draw(*hero.GetSprite());
  }
}

void DrawBullet(sf::RenderWindow* window, Player* player, bool& is_show_bullet) {
  static int dif = 0;
  sf::Vector2f new_coor = player->GetBullet()->GetNewCoor(
      player->GetCoor(),
      player->GetLastDirection(),
      dif);
  player->GetBullet()->GetSprite()->setPosition(new_coor);
  ++dif;
  if (dif == 200) {
    dif = 0;
    is_show_bullet = false;
  }
  window->draw(*player->GetBullet()->GetSprite());
}

void DrawMap(sf::RenderWindow* window,
             const std::vector<std::vector<int>>& map_types,
             const std::vector<TileInfo>& tiles, sf::Sprite& map) {
  for (int i = 0; i < MAP_HEIGHT; ++i) {
    for (int j = 0; j < MAP_WIDTH; ++j) {
      int num = map_types[i][j] - 1;
      map.setTextureRect(sf::IntRect(tiles[num].x, tiles[num].y,
                                     tiles[num].width, tiles[num].height));

      map.setPosition(j * TILE_SIZE, i * TILE_SIZE);
      window->draw(map);
    }
  }
}

void DrawMainInfo(sf::RenderWindow* window,
                  Player* player,
                  const sf::Font& font) {
  sf::Text health("Health: " + std::to_string(player->GetHealth()), font, 50);
  sf::Text exp("Exp: " + std::to_string(player->GetExp()), font, 50);
  health.setFillColor(sf::Color::Black);
  exp.setFillColor(sf::Color::Black);
  health.setPosition(player->GetCoor() - sf::Vector2f(700, 450));
  exp.setPosition(player->GetCoor() - sf::Vector2f(400, 450));
  window->draw(health);
  window->draw(exp);
}

void DrawMissions(sf::RenderWindow* window, Player& player,
                  sf::Sprite& quests_background,
                  const sf::Font& font, bool is_show_missions) {
  std::vector<std::string> active_quests = player.GetActiveQuests();
  std::vector<sf::Text> quests(active_quests.size(), sf::Text("", font, 20));
  for (int i = 0; i < quests.size(); ++i) {
    sf::Text& text = quests[i];
    text.setString("");
    if (is_show_missions) {
      text.setString(active_quests[i]);
      text.setFillColor(sf::Color::Black);
    }
  }
  quests_background.setPosition(player.GetCoor() - sf::Vector2f(600, 300));
  window->draw(quests_background);
  sf::Text quests_text("QUESTS", font, 35);
  quests_text.setFillColor(sf::Color::Black);
  sf::Vector2f coor = player.GetCoor() - sf::Vector2f(580, 270);
  quests_text.setPosition(coor + sf::Vector2f(100, -20));
  coor += sf::Vector2f(0, 23);
  window->draw(quests_text);
  for (int i = 0; i < quests.size(); ++i, coor.y += 23) {
    quests[i].setPosition(coor);
    window->draw(quests[i]);
  }
}

void DrawExp(sf::RenderWindow* window, Player& player,
             std::pair<bool, sf::Text>* get_exp_text) {
  static int draw_cnt = 0;
  ++draw_cnt;
  static int dif = 20;
  get_exp_text->second.setPosition(player.GetCoor() - sf::Vector2f(0, dif));
  dif += 1;
  if (draw_cnt == 200) {
    draw_cnt = 0;
    dif = 20;
    get_exp_text->first = false;
  }
  window->draw(get_exp_text->second);
}

void DrawEnemies(sf::RenderWindow* window,
                 const std::vector<Enemy>& enemies) {
  for (const auto& enemy : enemies) {
    window->draw(*enemy.GetSprite());
  }
}

void DrawBuff(sf::RenderWindow* window, Player& player) {
  sf::Image level_up;
  level_up.loadFromFile("img/level.png");
  sf::Texture level_texture;
  level_texture.loadFromImage(level_up);
  sf::Sprite level_sprite;
  level_sprite.setTexture(level_texture);
  level_sprite.setPosition(player.GetCoor() - sf::Vector2f(600, 200));
  window->draw(level_sprite);
}


#endif //NEWPROJECT228_DRAW_H
