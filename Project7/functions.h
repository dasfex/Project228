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

void GetAllInformation(std::vector<std::vector<int>>& map_tiles,
                       std::vector<TileInfo>& tiles,
                       std::vector<QuestHero>& quest_heroes) {
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

void KeyboardTreatment(Player* player) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    player->SetDirection(Direction::N);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    player->SetDirection(Direction::W);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    player->SetDirection(Direction::S);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    player->SetDirection(Direction::E);
  } else {
    player->SetDirection(Direction::STAY);
  }
}

void DrawHeroes(sf::RenderWindow* window, const std::vector<QuestHero>& heroes) {
  for (const auto& hero : heroes) {
    window->draw(*hero.GetSprite());
  }
}

#endif  // PROJECT228_FUNCTIONS_H
