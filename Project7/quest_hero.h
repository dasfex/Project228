// этот класс предназначен для персонажей, которые дают квесты нашему герою

#ifndef PROJECT228_QUEST_HERO_H
#define PROJECT228_QUEST_HERO_H

#include <string>
#include <utility>
#include "main_headers.h"
#include "useful.h"

class QuestHero {
 public:
  QuestHero(double, double, const sf::String&, const sf::String&,
            const sf::String&, int, int, int, int, int);

  double GetX() const;
  double GetY() const;

 private:
  Coordinate coor_;

  sf::String image_file_;
  sf::String file_for_quest_;
  sf::String file_after_quest_;

  int reward_exp_;

  std::pair<int, int> coor_for_img_;
  std::pair<int, int> size_for_img_;

  sf::Image* image_ = new sf::Image;
  sf::Texture* texture_ = new sf::Texture;
  sf::Sprite* sprite_ = new sf::Sprite;

  std::string text_for_quest_ = "";
  std::string text_after_quest_ = "";

  bool is_quest_ready = false;
};

#endif //PROJECT228_QUEST_HERO_H
