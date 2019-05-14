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
            const std::string&, const std::string&,
            int, int, int, int, int, int, bool, bool);

  const sf::Sprite* GetSprite() const;
  double GetX() const;
  double GetY() const;

  std::string GetText() const;
  std::string GetTask() const;
  bool IsQuestReady() const;
  bool IsHeroExist() const;
  bool IsExpGiven() const;

  int GiveReward();

  void SetQuestReady();

  int GetPassedQuest() const;

 private:
  const sf::Vector2f coor_;

  std::string image_file_;
  std::string file_for_quest_;
  std::string file_after_quest_;
  std::string file_for_quest_text_;

  int reward_exp_;

  sf::Vector2i coor_for_img_;
  sf::Vector2i size_for_img_;

  sf::Image* image_ = new sf::Image;
  sf::Texture* texture_ = new sf::Texture;
  sf::Sprite* sprite_ = new sf::Sprite;

  std::string text_for_quest_ = "";
  std::string text_after_quest_ = "";
  std::string task_text_ = "";

  bool is_quest_ready_ = false;
  bool is_exp_given_ = false;

  //  хранит номер квеста, который завершает данный герой
  //  если таковой имеется
  int passed_quest_;
  
  //  нужно ли менять картинку после выполнения квеста
  bool is_change_img_;
  //  файл с новыми координатами для новой картинки
  std::string file_new_coor_ = "newcoor.txt";
  //  нужно ли пропасть после окончания квеста
  bool is_need_to_disappear_;
  bool is_exist_ = true;
};

#endif //PROJECT228_QUEST_HERO_H
