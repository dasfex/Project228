//
// Created by pmetl on 06.05.2019.
//

#ifndef PROJECT228_ATTACK_H
#define PROJECT228_ATTACK_H

#include "player.h"

class Bullet {
 public:

  explicit Bullet(Player* player);
  explicit Bullet(Player player);
  void hit(Player* player);
  sf::Sprite* GetSprite();
  ~Bullet();

 private:

  int attack_value;
  int lifetime_;
  int coordinate_x;
  int coordinate_y;

  const int weight = 16;
  const int height = 16;
  sf::Image bullet_image_;

  const Direction direction;

  sf::Sprite* sprite_;
  Player* player_;
};

#endif //PROJECT228_ATTACK_H
