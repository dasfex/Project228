#include "bullet.h"

Bullet::Bullet() {
  image_->loadFromFile("img/bulllet.png");
  image_->createMaskFromColor(sf::Color(255, 255, 255));
  texture_->loadFromImage(*image_);
  sprite_->setTexture(*texture_);
  sprite_->setTextureRect(sf::IntRect(0, 0, img_size_.x, img_size_.y));
}

sf::Sprite* Bullet::GetSprite() const {
  return sprite_;
}

sf::Vector2f Bullet::GetCoor() const {
  return coor_;
}

Bullet::~Bullet() {
  delete image_;
  delete texture_;
  delete sprite_;
}

sf::Vector2f Bullet::GetNewCoor(sf::Vector2f coor,
                                Direction dir, int dif) const {
  switch (dir) {
    case Direction::kNorth: {
      return coor - sf::Vector2f(-3, dif + 3);
    }
    case Direction::kEast: {
      return coor + sf::Vector2f(dif + 5, 15);
    }
    case Direction::kSouth: {
      return coor + sf::Vector2f(5, dif + 50);
    }
    case Direction::kWest: {
      return coor - sf::Vector2f(dif, -15);
    }
  }
}