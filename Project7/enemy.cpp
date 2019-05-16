//
// Created by Vanya Khodor on 14.05.2019.
//

#include <iostream>

#include "enemy.h"
#include "constants.h"
#include <cmath>

Enemy::Enemy(
    double x, double y,
    const std::string& file_img,
    int reward, int x_img, int y_img,
    int width_img, int height_img,
    int health, int defense, int attack,
    int passed_quest, bool is_gorizontal)
    : coor_(x, y)
    , image_file_(file_img)
    , reward_exp_(reward)
    , coor_for_img_(x_img, y_img)
    , size_for_img_(width_img, height_img)
    , health_(health)
    , defense_(defense)
    , attack_(attack)
    , passed_quest_(passed_quest)
    , is_gorizonatal_(is_gorizontal) {

  image_->loadFromFile(image_file_);
  image_->createMaskFromColor(sf::Color(255, 255, 255));
  texture_->loadFromImage(*image_);
  sprite_->setTexture(*texture_);
  sf::IntRect rect(coor_for_img_, size_for_img_);
  sprite_->setTextureRect(rect);
  sprite_->setPosition(x, y);
}

const sf::Sprite* Enemy::GetSprite() const {
  return sprite_;
}

sf::Vector2f Enemy::GetCoor() const {
  return coor_;
}

int Enemy::GiveReward() const {
  return reward_exp_;
}

void Enemy::Move(int time, const std::vector<std::vector<int>>& map,
                 sf::Vector2f player_coor, bool bot) {
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
  CheckMap(time, coor_.x, coor_.y, h, w, map, bot, player_coor);

  sprite_->setPosition(coor_);
  sprite_->setTextureRect(rectangle);
  last_rect_ = rectangle;
}

bool Enemy::IsCantGo(int type) const {
  return type >= 31 && type <= 43;
}

void Enemy::CheckMap(double time, double x, double y, int h, int w,
                     const std::vector<std::vector<int>>& map,
                     bool bot, sf::Vector2f player_coor) {
  x = ceil(x);
  y = ceil(y);
  int left_i = y;
  int right_i = (y + h);
  int left_j = x;
  int right_j = (x + w);

  int player_left_i = ceil(player_coor.y);
  // [0, 1] : 0 - width = y
  int player_right_i =
      ceil(player_coor.y + 30);
  int player_left_j = ceil(player_coor.x);
  // [0, 1] : 1 - height = x
  int player_right_j =
      ceil(player_coor.x) + 54;

  bool is_bad_pos = false;
  if (bot) {
    for (int i = left_i; i < right_i; ++i) {
      for (int j = left_j; j < right_j; ++j) {
        is_bad_pos |=
            player_left_i <= i && i <= player_right_i
                && player_left_j <= j && j <= player_right_j;
      }
    }
  }

  left_i /= TILE_SIZE;
  right_i /= TILE_SIZE;
  left_j /= TILE_SIZE;
  right_j /= TILE_SIZE;

  for (int i = left_i; i <= right_i; ++i) {
    for (int j = left_j; j <= right_j; ++j) {
      is_bad_pos |= IsCantGo(map[i][j]);
    }
  }

  if (is_bad_pos) {
    coor_ -= sf::Vector2f(direct_speed_.x * time, direct_speed_.y * time);
  }
}

sf::Vector2i Enemy::GetImgSize() const {
  return size_for_img_;
}

Bullet * Enemy::GetBullet() const
{
	return bullet_;
}

void Enemy::ChangeDir() {
  if (is_gorizonatal_) {
    switch (dir_) {
      case Direction::kEast: {
        dir_ = Direction::kWest;
        break;
      }
      case Direction::kWest: {
        dir_ = Direction::kEast;
        break;
      }
      case Direction::kStay: {
        dir_ = Direction::kEast;
        break;
      }
    }
  } else {
    switch (dir_) {
      case Direction::kNorth: {
        dir_ = Direction::kSouth;
        break;
      }
      case Direction::kSouth: {
        dir_ = Direction::kNorth;
        break;
      }
      case Direction::kStay: {
        dir_ = Direction::kNorth;
        break;
      }
    }
  }
}

int Enemy::GetHealth() const {
  return health_;
}

bool Enemy::SubtractHealth(int attack) {
	health_ -= attack;  // dddd
	if (health_ <= 0) {
		is_exist_ = false;
		return true;
	}
	
	return false;
}

bool Enemy::IsExist() const {
	return is_exist_;
}
