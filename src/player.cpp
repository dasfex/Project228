#include "headers//player.h"

double Player::GetX() const {
    return coordinates_.x;
}

double Player::GetY() const {
    return coordinates_.y;
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
    coordinates_.x += dir_speed_.x * time;
    coordinates_.y += dir_speed_.y * time;

    map_speed_ = 0;
    // добавить взаимодействие с картой
    // и перемещение спрайта игрока
}
