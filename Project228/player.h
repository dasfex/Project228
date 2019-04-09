//
// Created by Vanya Khodor on 04.04.2019.
//

#ifndef PROJECT228_PLAYER_H
#define PROJECT228_PLAYER_H

#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

enum class Direction {
  N = 0,
  E,
  S,
  W,
  STAY // на месте
};

class Player {
 public:

  Player(const sf::String&, double, double, int, int, int);

  bool IsAlive() const;

  void SetDirection(Direction);

  void Move(double, const std::vector<std::vector<int>>&);

  sf::Sprite* GetSprite() const;

  double GetX() const;
  double GetY() const;

 private:

  struct Coordinate {
    double x;
    double y;

    Coordinate(double x, double y)
        : x(x)
        , y(y) {}
  };

  int exp_ = 0;
  int health_;
  bool is_alive_ = true;

  Coordinate coor_;
  Coordinate direct_speed_ = {0.0, 0.0};
  double speed_ = 0;

  Direction dir_ = Direction::STAY;

  int attack_;
  int defense_;

  sf::String file_;
  sf::Image* image_ = new sf::Image;
  sf::Texture* texture_ = new sf::Texture;
  sf::Sprite* sprite_ = new sf::Sprite;

  sf::IntRect last_rect_;

  double cur_frame_ = 0.0;

  bool IsCantGo(int);
};

#endif //PROJECT228_PLAYER_H
