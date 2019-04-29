#ifndef PROJECT228_PLAYER_H
#define PROJECT228_PLAYER_H

#include "quest_hero.h"
#include "main_headers.h"
#include "useful.h"
#include <algorithm>
#include <utility>

enum class Direction {
  kNorth,
  kEast,
  kSouth,
  kWest,
  kStay // на месте
};

class Player {
 public:
  Player(const sf::String&, double, double, int, int, int);

  bool IsAlive() const;

  void SetDirection(Direction);

  void Move(int, const std::vector<std::vector<int>>&,
            const std::vector<QuestHero>&);

  const sf::Sprite* GetSprite() const;

  double GetX() const;
  double GetY() const;

  std::vector<std::string> GetActiveQuests() const;
  void AddNewQuest(const std::string&);
  void DeleteQuest(const std::string&);

  int GetExp() const;
  int GetHealth() const;
  int Attack() const;
  int GetDefense() const;

  void AddExp(int);

 private:

  int exp_ = 0;
  int health_;
  bool is_alive_ = true;

  Coordinate coor_;
  Coordinate direct_speed_ = {0, 0};
  double speed_ = 0;

  Direction dir_ = Direction::kStay;

  int attack_;
  int defense_;

  sf::String file_;
  sf::Image* image_ = new sf::Image;
  sf::Texture* texture_ = new sf::Texture;
  sf::Sprite* sprite_ = new sf::Sprite;

  sf::IntRect last_rect_;

  double cur_frame_ = 0.0;

  std::vector<std::string> active_quests_= {};

  bool IsCantGo(int, const std::vector<QuestHero>&) const;
  void CheckMap(double, double, double, int, int,
                const std::vector<std::vector<int>>&,
                const std::vector<QuestHero>&);
};

#endif //PROJECT228_PLAYER_H