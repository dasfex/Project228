//
// Created by pmetl on 06.05.2019.
//

#include "attack.h"
#include "iostream"
Bullet::Bullet(Player* player) : attack_value(player->Attack()), lifetime_(5),
                                 direction(player->GetDirection()),
                                 player_(player) {
  bullet_image_.loadFromFile("img/bullet.png");
  bullet_image_.createMaskFromColor(sf::Color(0, 0, 0));
  sprite_ = new sf::Sprite;
}
void Bullet::hit(Player* player) {
  player->SetHealth(-attack_value + player->GetDefense() / 2);
  delete this;
}
sf::Sprite* Bullet::GetSprite() {
  return sprite_;
}
Bullet::Bullet(Player player) : attack_value(player.Attack()), lifetime_(5),
                                direction(player.GetDirection()) {
  bullet_image_.loadFromFile("img/bullet.png");
  bullet_image_.createMaskFromColor(sf::Color(0, 0, 0));
  sprite_ = new sf::Sprite;
  player_ = &player;
}
Bullet::~Bullet() {
  player_->SetBullet();
  std::cout <<"delete bullert"<< std::endl;
};


