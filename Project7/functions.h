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

void KeyboardTreatment(Player* player, std::vector<QuestHero>& heroes,
                       std::pair<bool, std::string>* is_text, sf::Text* text) {
  int hero_ind = FindHeroNear(player, heroes);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    player->SetDirection(Direction::N);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    player->SetDirection(Direction::W);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    player->SetDirection(Direction::S);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    player->SetDirection(Direction::E);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
    player->SetDirection(Direction::STAY);
    if (hero_ind < HEROES_CNT) {
      MakeText(is_text, text, true, heroes[hero_ind].GetText());
    }
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

#endif  // PROJECT228_FUNCTIONS_H
