// этот класс предназначен для персонажей, которые дают квесты нашему герою

#ifndef PROJECT228_QUEST_HERO_H
#define PROJECT228_QUEST_HERO_H

#include <fstream>
#include <string>
#include <utility>
#include "main_headers.h"
#include "useful.h"

class QuestHero {
 public:
  QuestHero(double, double,
            const std::string&, const std::string&,
            const std::string&, int, int, int, int, int);

  const sf::Sprite* GetSprite() const;
  double GetX() const;
  double GetY() const;

  std::string GetText();
  int GetTreatment() const;
  int GetReward() const;

 private:
  const Coordinate coor_;

  std::string image_file_;
  std::string file_for_quest_;
  std::string file_after_quest_;

  int reward_exp_;

  std::pair<int, int> coor_for_img_;
  std::pair<int, int> size_for_img_;

  sf::Image* image_ = new sf::Image;
  sf::Texture* texture_ = new sf::Texture;
  sf::Sprite* sprite_ = new sf::Sprite;

  std::string text_for_quest_ = "";
  std::string text_after_quest_ = "";

  bool is_quest_ready = false;

  int treatment_cnt_ = 0;
};

#endif //PROJECT228_QUEST_HERO_H
