#ifndef PROJECT228_FUNCTIONS_H
#define PROJECT228_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include "main_headers.h"
#include "constants.h"
#include "player.h"
#include "quest_hero.h"

struct TileInfo {
  int x;
  int y;
  int width;
  int height;

  friend std::istream& operator>>(std::istream& in, TileInfo& x);
};

std::istream& operator>>(std::istream& in, TileInfo& x) {
  in >> x.x >> x.y >> x.width >> x.height;
  return in;
}

// анонимный namespace, чтобы нельзя было вызвать функцию из другого файла
namespace {
int FindHeroNear(const Player* player,
                 const std::vector<QuestHero>& heroes) {
  int h = 56, w = 30;  // размеры Халка
  for (int k = 0; k < HEROES_CNT; ++k) {
    int hero_x = ceil(heroes[k].GetX()) / TILE_SIZE;
    int hero_y = ceil(heroes[k].GetY()) / TILE_SIZE;
    int player_y = ceil(player->GetY()) / TILE_SIZE;
    int player_x = ceil(player->GetX()) / TILE_SIZE;
    if (abs(player_x - hero_x) <= 1 && abs(player_y - hero_y) <= 1) {
      return k;
    }
  }
  return HEROES_CNT;
}

void MakeText(std::pair<bool, std::string>* is_text, sf::Text* text,
              bool flag = false, std::string str = " ") {
  is_text->first = flag;
  is_text->second = str;
  text->setString(is_text->second);
}

bool Find(const std::vector<std::string>& vec, const std::string& str) {
  for (const auto& x : vec) {
    if (x == str) {
      return true;
    }
  }
  return false;
}

}

void GetAllInformation(std::vector<std::vector<int>>& map_tiles,
                       std::vector<TileInfo>& tiles,
                       std::vector<QuestHero>& quest_heroes,
                       sf::Font* font) {
  std::ifstream get_map("files/main_map.txt");
  for (int i = 0; i < MAP_HEIGHT; ++i) {
    for (int j = 0; j < MAP_WIDTH; ++j) {
      get_map >> map_tiles[i][j];
    }
  }

  std::fstream get_tiles("files/sprite coordinates.txt");
  for (auto& tile : tiles) {
    int nom;
    get_tiles >> nom;
    get_tiles >> tile;
  }

  quest_heroes.reserve(HEROES_CNT);
  for (int i = 0; i < HEROES_CNT; ++i) {
    std::string folder_name(1, char(i + 1 + '0'));
    std::ifstream get_info("files/heroes/" + folder_name + "/main.txt");
//    double x, double y,
//    string file_img,
//    string file_for_quest,
//    string file_after_quest,
//    int reward, int x_img, int y_img,
//    int width_img, int height_img
    double x, y;
    std::string img = "files/heroes/" + folder_name + "/hero.png",
        for_quest = "files/heroes/" + folder_name + "/for_quest.txt",
        after_quest = "files/heroes/" + folder_name + "/after_quest.txt";
    int reward, x_img, y_img, width, height;
    get_info >> x >> y >> reward >> x_img >> y_img >> width >> height;
    quest_heroes.emplace_back(x, y, img, for_quest, after_quest,
                              reward, x_img, y_img, width, height);
  }

  font->loadFromFile("files/Samson.ttf");
}

void KeyboardTreatment(Player* player, std::vector<QuestHero>& heroes,
                       std::pair<bool, std::string>* is_text,
                       sf::Text* text, bool& is_show_missions) {
  int hero_ind = FindHeroNear(player, heroes);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    player->SetDirection(Direction::N);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
    is_show_missions = false;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    player->SetDirection(Direction::W);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
    is_show_missions = false;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    player->SetDirection(Direction::S);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
    is_show_missions = false;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    player->SetDirection(Direction::E);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
    is_show_missions = false;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
    player->SetDirection(Direction::STAY);
    if (hero_ind < HEROES_CNT) {
      MakeText(is_text, text, true, heroes[hero_ind].GetText());
      std::vector<std::string> active_quests = player->GetActiveQuests();
      if (!Find(active_quests, is_text->second)) {
        player->AddNewQuest(is_text->second);
      }
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    is_show_missions = true;
   // player->SetDirection(Direction::STAY);
  } else {
    player->SetDirection(Direction::STAY);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
  }
}

void DrawHeroes(sf::RenderWindow* window, const std::vector<QuestHero>& heroes) {
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

void DrawMainInfo(sf::RenderWindow* window, Player* player, const sf::Font& font) {
  sf::Text health("Health: " + std::to_string(player->GetHealth()), font, 50);
  sf::Text exp("Exp: " + std::to_string(player->GetExp()), font, 50);
  health.setColor(sf::Color::Black);
  exp.setColor(sf::Color::Black);
  health.setPosition(player->GetX() - 700, player->GetY() - 450);
  exp.setPosition(player->GetX() - 400, player->GetY() - 450);
  window->draw(health);
  window->draw(exp);
}

void DrawMissions(sf::RenderWindow* window, Player& player,
                  sf::Sprite& quests_background, const sf::Font& font, bool is_show_missions) {
  std::vector<std::string> active_quests = player.GetActiveQuests();
  std::vector<sf::Text> quests(active_quests.size(), sf::Text("", font, 20));
  for (int i = 0; i < quests.size(); ++i) {
    sf::Text& text = quests[i];
    text.setString("");
    if (is_show_missions) {
      text.setString(active_quests[i]);
      text.setColor(sf::Color::Black);
    }
  }
  quests_background.setPosition(player.GetX() - 600, player.GetY() - 300);
  window->draw(quests_background);
  int x_coor = player.GetX() - 580;
  int y_coor = player.GetY() - 270;
  for (int i = 0; i < quests.size(); ++i, y_coor += 23) {
    quests[i].setPosition(x_coor, y_coor);
    window->draw(quests[i]);
  }
}

#endif  // PROJECT228_FUNCTIONS_H
