#ifndef PROJECT228_ATTACK_H
#define PROJECT228_ATTACK_H

#include "main_headers.h"
#include "useful.h"

class Bullet {
 public:

  Bullet();

  sf::Sprite* GetSprite() const;
  sf::Vector2f GetCoor() const;
  sf::Vector2f GetNewCoor(sf::Vector2f, Direction, int) const;
  sf::Music* GetSound() const;

  ~Bullet();

 private:

  int attack_value;
  int lifetime_;
  sf::Vector2f coor_ = sf::Vector2f(0, 0);

  const sf::Vector2i img_size_ = sf::Vector2i(16, 16);

  sf::Image* image_ = new sf::Image;
  sf::Texture* texture_ = new sf::Texture;
  sf::Sprite* sprite_ = new sf::Sprite;

  sf::Music* sound_ = new sf::Music;

  Direction direction;
};

#endif //PROJECT228_ATTACK_H
