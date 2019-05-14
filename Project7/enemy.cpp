//
// Created by Vanya Khodor on 14.05.2019.
//

#include "enemy.h"
#include "constants.h"
Enemy::Enemy(
    double x, double y,
    const std::string& file_img,
    int reward, int x_img, int y_img,
    int width_img, int height_img,
    int health, int defense, int attack,
    int passed_quest)
    : coor_(x, y)
    , image_file_(file_img)
    , reward_exp_(reward)
    , coor_for_img_(x_img, y_img)
    , size_for_img_(width_img, height_img)
    , health_(health)
    , defense_(defense)
    , attack_(attack)
    , passed_quest_(passed_quest)
    , coor_map_tile_left_(ceil(x) / TILE_SIZE - 5, ceil(y) / TILE_SIZE - 5)
    , coor_map_tile_right_(ceil(x) / TILE_SIZE + 5, ceil(y) / TILE_SIZE + 5) {

  image_->loadFromFile(image_file_);
  image_->createMaskFromColor(sf::Color(255, 255, 255));
  texture_->loadFromImage(*image_);
  sprite_->setTexture(*texture_);
  sf::IntRect rect(coor_for_img_, size_for_img_);
  sprite_->setTextureRect(rect);
  sprite_->setPosition(x, y);
}

Direction Enemy::GetLastDirection() const {
  return last_dir_;
}

const sf::Sprite* Enemy::GetSprite() const {
  return sprite_;
}

double Enemy::GetX() const {
  return coor_.x;
}

double Enemy::GetY() const {
  return coor_.y;
}

int Enemy::GiveReward() {
  return reward_exp_;
}

void Enemy::Move(int time, const std::vector<std::vector<int>>& map) {
  float speed = 0.06;  // 0.06
  cur_frame_ += 0.009 * time;
  if (cur_frame_ > 4) {
    cur_frame_ -= 4;
  }

  sf::IntRect rectangle;
  switch (dir_) {
    case Direction::kNorth: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 168, 36, 54);
      direct_speed_ = sf::Vector2f(0, -speed);
      last_dir_ = Direction::kNorth;
      break;
    }
    case Direction::kSouth: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 1, 36, 54);
      direct_speed_ = sf::Vector2f(0, speed);
      last_dir_ = Direction::kSouth;
      break;
    }
    case Direction::kEast: {
      rectangle = sf::IntRect(7 + 40 * int(cur_frame_), 111, 22, 54);
      direct_speed_ = sf::Vector2f(speed, 0);
      last_dir_ = Direction::kEast;
      break;
    }
    case Direction::kWest: {
      rectangle = sf::IntRect(9 + 40 * int(cur_frame_), 56, 22, 54);
      direct_speed_ = sf::Vector2f(-speed, 0);
      last_dir_ = Direction::kWest;
      break;
    }
    case Direction::kStay: {
      rectangle = last_rect_;
      direct_speed_ = sf::Vector2f(0, 0);
      return;
    }
  }
  coor_ += sf::Vector2f(direct_speed_.x * time, direct_speed_.y * time);

  int h = 54, w = 30;  // 36?
  CheckMap(time, coor_.x, coor_.y, h, w, map);

  sprite_->setPosition(coor_);
  sprite_->setTextureRect(rectangle);
  last_rect_ = rectangle;
}

bool Enemy::IsCantGo(int type) const {
  return type >= 31 && type <= 43;
}

void Enemy::CheckMap(double time, double x, double y, int h, int w,
                     const std::vector<std::vector<int>>& map) {
  x = ceil(x);
  y = ceil(y);
  int left_i = y / TILE_SIZE;
  int right_i = (y + h) / TILE_SIZE;
  int left_j = x / TILE_SIZE;
  int right_j = (x + w) / TILE_SIZE;
  for (int i = left_i; i <= right_i; ++i) {
    for (int j = left_j; j <= right_j; ++j) {
      if (!IsCantGo(map[i][j])) continue;
      coor_ -= sf::Vector2f(direct_speed_.x * time, direct_speed_.y * time);
      return;
    }
  }
}

bool Enemy::IsOnBound() const {
  int h = 54, w = 30;
  double x = ceil(coor_.x);
  double y = ceil(coor_.y);
  int left_i = x / TILE_SIZE;
  int right_i = (y + h) / TILE_SIZE;
  int left_j = x / TILE_SIZE;
  int right_j = (x + w) / TILE_SIZE;
  return left_i == coor_map_tile_left_.x ||
      left_j == coor_map_tile_left_.y ||
      right_i == coor_map_tile_right_.x ||
      right_j == coor_map_tile_right_.y;
}

void Enemy::ChangeDir() {
  static std::mt19937 rand(static_cast<unsigned int>(time(nullptr)));
  int h = 54, w = 30;
  double x = ceil(coor_.x);
  double y = ceil(coor_.y);
  int new_dir = rand() % 3;
  switch (last_dir_) {
    case Direction::kStay: {
      dir_ = Direction::kEast;
      break;
    }
    case Direction::kNorth: {
      dir_ = Direction::kWest;
      break;
    }
    case Direction::kEast: {
      dir_ = Direction::kNorth;
      break;
    }
    case Direction::kWest: {
      dir_ = Direction::kSouth;
      break;
    }
    case Direction::kSouth: {
      dir_ = Direction::kEast;
      break;
    }
  }
}
