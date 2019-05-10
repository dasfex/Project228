#ifndef PROJECT228_FUNCTIONS_H
#define PROJECT228_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <cmath>
#include "main_headers.h"
#include "constants.h"
#include "player.h"
#include "quest_hero.h"
#include "attack.h"
#include "draw.h"
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
    if (!heroes[k].IsHeroExist()) {
      continue;
    }
    int hero_x = ceil(heroes[k].GetX()) / TILE_SIZE;
    int hero_y = ceil(heroes[k].GetY()) / TILE_SIZE;
    int player_y = ceil(player->GetCoor().y) / TILE_SIZE;
    int player_x = ceil(player->GetCoor().x) / TILE_SIZE;
    if (abs(player_x - hero_x) <= 1 && abs(player_y - hero_y) <= 1) {
      return k;
    }
  }
  return HEROES_CNT;
}

void MakeText(std::pair<bool, std::string>* is_text, sf::Text* text,
              bool flag = false, std::string str = "") {
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
        after_quest = "files/heroes/" + folder_name + "/after_quest.txt",
        quest_text = "files/heroes/" + folder_name + "/quest_text.txt";
    int reward, x_img, y_img, width, height, passed_quest;
    bool is_change_img, is_disappear;
    get_info >> x >> y >> reward >> x_img >> y_img >>
             width >> height >> passed_quest >> is_change_img >> is_disappear;
    quest_heroes.emplace_back(x, y, img, for_quest, after_quest, quest_text,
                              reward, x_img, y_img, width, height,
                              passed_quest, is_change_img, is_disappear);
  }

  font->loadFromFile("files/Samson.ttf");
}

void KeyboardTreatment(Player* player, std::vector<QuestHero>& heroes,
                       std::pair<bool, std::string>* is_text,
                       sf::Text* text, std::pair<bool, sf::Text>* exp_text,
                       bool& is_show_missions, bool& is_show_bullet) {
  if (is_show_bullet) {
    return;
  }
  int hero_ind = FindHeroNear(player, heroes);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    player->SetDirection(Direction::kNorth);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
    is_show_missions = false;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    player->SetDirection(Direction::kWest);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
    is_show_missions = false;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    player->SetDirection(Direction::kSouth);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
    is_show_missions = false;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    player->SetDirection(Direction::kEast);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
    is_show_missions = false;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
    player->SetDirection(Direction::kStay);
    if (hero_ind < HEROES_CNT) {
      MakeText(is_text, text, true, heroes[hero_ind].GetText());
      std::vector<std::string> active_quests = player->GetActiveQuests();
      if (heroes[hero_ind].IsQuestReady() &&
          heroes[hero_ind].GetPassedQuest() == 0 &&
          !heroes[hero_ind].IsExpGiven()) {
        MakeText(is_text, text, true, heroes[hero_ind].GetText());
        exp_text->first = true;
        int exp = heroes[hero_ind].GiveReward();
        std::cout << exp << std::endl;
        if (exp != 0) {
          exp_text->second.setString(std::to_string(exp));
          player->AddExp(exp);
        } else if (!is_text->first) {
          exp_text->second.setString("");
        }
        player->DeleteQuest(heroes[hero_ind].GetTask());
        return;
      }
      if (heroes[hero_ind].IsQuestReady() &&
          heroes[hero_ind].GetPassedQuest() != 0) {
        MakeText(is_text, text, true, heroes[hero_ind].GetText());
        return;
      }
      if (heroes[hero_ind].GetPassedQuest() == 0 &&
          !heroes[hero_ind].IsExpGiven()) {
        if (!Find(active_quests, heroes[hero_ind].GetTask())) {
          player->AddNewQuest(heroes[hero_ind].GetTask());
        }
      } else {
        heroes[hero_ind].SetQuestReady();
        heroes[heroes[hero_ind].GetPassedQuest() - 1].SetQuestReady();
      }
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    is_show_missions = true;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
    player->SetDirection(Direction::kStay);
    is_show_bullet = true;
  } else {
    player->SetDirection(Direction::kStay);
    if (hero_ind == HEROES_CNT) {
      MakeText(is_text, text);
    }
  }
}

#endif  // PROJECT228_FUNCTIONS_H
