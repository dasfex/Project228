#include "bullet.h"

Bullet::Bullet()
    : lifetime_(5) {
  image_->loadFromFile("img/bulllet.png");
  image_->createMaskFromColor(sf::Color(255, 255, 255));
  texture_->loadFromImage(*image_);
  sprite_->setTexture(*texture_);
  sprite_->setTextureRect(sf::IntRect(0, 0, img_size_.x, img_size_.y));

  sound_->openFromFile("files/bulletsound.wav");
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
  delete sound_;
}

sf::Music* Bullet::GetSound() const {
  return sound_;
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