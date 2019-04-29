#ifndef NEWPROJECT228_DRAW_H
#define NEWPROJECT228_DRAW_H

#include "constants.h"
#include "main_headers.h"
#include "functions.h"
#include "quest_hero.h"
#include "player.h"
#include <vector>

void DrawHeroes(sf::RenderWindow* window,
                const std::vector<QuestHero>& heroes) {
  for (const auto& hero : heroes) {
    window->draw(*hero.GetSprite());
  }
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
//  sf::Text quests("QUESTS", font, 70);
//  quests.setFillColor(sf::Color::Black);
//  quests.setP
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
  sf::Vector2f coor = player.GetCoor() - sf::Vector2f(580, 270);
  for (int i = 0; i < quests.size(); ++i, coor.y += 23) {
    quests[i].setPosition(coor);
    window->draw(quests[i]);
  }
}

#endif //NEWPROJECT228_DRAW_H
