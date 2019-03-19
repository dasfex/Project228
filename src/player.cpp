#include "headers//player.h"
#include <QtMath>

Player::Player(int health, int attack, int speed, int defense)
    : health_(health)
    , attack_(attack)
    , speed_(speed)
    , defense_(defense)
    /*, player_image_(new QImage("D:/projects codeblocks/sfml/images/hero.png"))*/
    {}

double Player::GetX() const {
    return coordinates_.x;
}

double Player::GetY() const {
    return coordinates_.y;
}

//QImage Player::GetPlayerImage() const {
//    return *player_image_;
//}

void Player::SetDirection(Direction new_dir) {
    direction_ = new_dir;
}

void Player::SetSpeed(double new_speed) {
    map_speed_ = new_speed;
}

void Player::UpdateSpeed() {
    switch(direction_) {
    case Direction::N: {
        dir_speed_ = Coordinates(0, -map_speed_); // движемся вверх
        break;
    }
    case Direction::E: {
        dir_speed_ = Coordinates(map_speed_, 0); // движемся вправо
        break;
    }
    case Direction::S: {
        dir_speed_ = Coordinates(0, map_speed_); // движемся вниз
        break;
    }
    case Direction::W: {
        dir_speed_ = Coordinates(-map_speed_, 0); // движемся влево
        break;
    }
    }
}

void Player::Move(double time) {
    coordinates_.x += dir_speed_.x * time; // двигаем по x
    coordinates_.y += dir_speed_.y * time; // двигаем по y

    map_speed_ = 0;
    // добавить взаимодействие с картой
    // и перемещение спрайта игрока
}

int Player::GetHealth() const {
    return health_;
}

int Player::GetAttack() const {
    return attack_;
}

int Player::GetDefense() const {
    return defense_;
}

void Player::SetHealth(int buf_health) {
    health_ += buf_health;
    health_ = qMax(0, health_);
}

void Player::SetAttack(int buf_attack) {
    attack_ += buf_attack;
    attack_ = qMax(0, attack_);
}

void Player::SetDefense(int buf_defense) {
    defense_ += buf_defense;
    defense_ = qMax(0, defense_);
}
