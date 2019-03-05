#include "headers//player.h"

double Player::GetX() const {
    return coor_x_;
}

double Player::GetY() const {
    return coor_y_;
}

void Player::SetDirection(Direction new_dir) {
    direction_ = new_dir;
}

void Player::SetSpeed(double new_speed) {
    map_speed_ = new_speed;
}

void Player::UpdateSpeed() {
    switch(direction_) {
    case Direction::N: {
        speed_x_ = 0;
        speed_y_ = -map_speed_; // движемся вверх
        break;
    }
    case Direction::E: {
        speed_x_ = map_speed_; // движемся вправо
        speed_y_ = 0;
        break;
    }
    case Direction::S: {
        speed_x_ = 0;
        speed_y_ = map_speed_; // движемся вниз
        break;
    }
    case Direction::W: {
        speed_x_ = -map_speed_; // движемся влево
        speed_y_ = 0;
        break;
    }
    case Direction::P: { // иначе стоим на месте
        speed_x_ = 0;
        speed_y_ = 0;
        break;
    }
    }
}

void Player::Move(double time) {
    coor_x_ += speed_x_ * time;
    coor_y_ += speed_y_ * time;

    map_speed_ = 0;
    // добавить взаимодействие с картой
    // и перемещение спрайтв игрока
}
