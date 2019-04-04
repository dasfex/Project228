//
// Created by Vanya Khodor on 04.04.2019.
//

#include "player.h"

Player::Player(const sf::String& file,
               double x,
               double y,
               double width,
               double height,
               int health,
               int attack,
               int defense)
    : health_(health)
    , coor_(Coordinate(x, y))
    , size_(std::make_pair(width, height))
    , attack_(attack)
    , defense_(defense)
    , file_(file) {
  image_->loadFromFile("img/" + file_);
  image_->createMaskFromColor(sf::Color(255, 255, 255));
  texture_->loadFromImage(*image_);

  sprite_->setTexture(*texture_);
  sprite_->setTextureRect(sf::IntRect(2, 168, 34, 54));
  sprite_->setPosition(x, y);
}

bool Player::IsAlive() const {
  return is_alive_;
}

void Player::SetDirection(Direction new_dir) {
  dir_ = new_dir;
}

void Player::Move(double time) {
  speed_ = 0.3;
  cur_frame_ += 0.02 * time;
  if (cur_frame_ > 4) {
    cur_frame_ -= 4;
  }
  sf::IntRect rectangle;
  switch (dir_) {
    case Direction::N: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 168, 34, 54);
      direct_speed_.x = 0;
      direct_speed_.y = -speed_;
      break;
    }
    case Direction::S: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 1, 34, 54);
      direct_speed_.x = 0;
      direct_speed_.y = speed_;
      break;
    }
    case Direction::E: {
      rectangle = sf::IntRect(7 + 40 * int(cur_frame_), 111, 22, 54);
      direct_speed_.x = speed_;
      direct_speed_.y = 0;
      break;
    }
    case Direction::W: {
      rectangle = sf::IntRect(9 + 40 * int(cur_frame_), 56, 22, 54);
      direct_speed_.x = -speed_;
      direct_speed_.y = 0;
      break;
    }
    case Direction::STAY: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 1, 34, 54);
      direct_speed_.x = 0;
      direct_speed_.y = 0;
      break;
    }
  }

  coor_.x += direct_speed_.x * time;
  coor_.y += direct_speed_.y * time;
  direct_speed_ = {0, 0};
  speed_ = 0;

  sprite_->setPosition(static_cast<float>(coor_.x), static_cast<float>(coor_.y));

  sprite_->setTextureRect(rectangle);
}

sf::Sprite* Player::GetSprite() const {
  return sprite_;
}
