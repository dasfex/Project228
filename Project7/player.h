#ifndef PROJECT228_PLAYER_H
#define PROJECT228_PLAYER_H

#include "bullet.h"
#include "enemy.h"
#include "quest_hero.h"
#include "main_headers.h"
#include "useful.h"
#include <algorithm>
#include <cmath>
#include <utility>

class Player {
 public:
  Player(const sf::String&, double, double, int, int, int);

  bool IsAlive() const;

  void SetDirection(Direction);

  void Move(int, const std::vector<std::vector<int>>&,
            const std::vector<QuestHero>&, const std::vector<Enemy>&);

  const sf::Sprite* GetSprite() const;

  sf::Vector2f GetCoor() const;

  std::vector<std::string> GetActiveQuests() const;
  void AddNewQuest(const std::string&);
  void DeleteQuest(const std::string&);

  int GetExp() const;
  int GetHealth() const;
  int Attack() const;
  int GetDefense() const;
  Bullet* GetBullet();

  void SetHealth(int);
  Direction GetDirection() const;
  Direction GetLastDirection() const;

  void AddExp(int);

  ~Player();

 private:

  int exp_ = 0;
  int health_;
  bool is_alive_ = true;

  sf::Vector2f coor_;
  sf::Vector2f direct_speed_ = {0, 0};
  double speed_ = 0;

  Direction dir_ = Direction::kStay;
  Direction last_dir_ = Direction::kStay;

  int attack_;
  int defense_;

  sf::String file_;
  sf::Image* image_ = new sf::Image;
  sf::Texture* texture_ = new sf::Texture;
  sf::Sprite* sprite_ = new sf::Sprite;

  sf::IntRect last_rect_;

  double cur_frame_ = 0.0;

  std::vector<std::string> active_quests_= {};

  Bullet* bullet_ = new Bullet;

  bool IsCantGo(int) const;
  void CheckMap(double, double, double, int, int,
                const std::vector<std::vector<int>>&,
                const std::vector<QuestHero>&,
                const std::vector<Enemy>&);
};

#endif //PROJECT228_PLAYER_H