#include "constants.h"
#include "player.h"

#include <iostream>

Player::Player(
    const sf::String& file,
    double x,
    double y,
    int health,
    int attack,
    int defense)
    : health_(health)
    , coor_(x, y)
    , attack_(attack)
    , defense_(defense)
    , file_(file) {

  image_->loadFromFile(file_);
  image_->createMaskFromColor(sf::Color(255, 255, 255));
  texture_->loadFromImage(*image_);

  sprite_->setTexture(*texture_);
  last_rect_ = sf::IntRect(2, 168, 36, 54);
  sprite_->setTextureRect(last_rect_);
  sprite_->setPosition(x, y);
}

bool Player::IsAlive() const {
  return is_alive_;
}

void Player::SetDirection(Direction new_dir) {
  dir_ = new_dir;
}

void Player::Move(int time, const std::vector<std::vector<int>>& map,
                  const std::vector<QuestHero>& heroes) {
  speed_ = 0.27;  // 0.3
  cur_frame_ += 0.009 * time;
  if (cur_frame_ > 4) {
    cur_frame_ -= 4;
  }

  sf::IntRect rectangle;
  switch (dir_) {
    case Direction::N: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 168, 36, 54);
      direct_speed_.x = 0;
      direct_speed_.y = -speed_;
      break;
    }
    case Direction::S: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 1, 36, 54);
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
      rectangle = last_rect_;
      direct_speed_.x = 0;
      direct_speed_.y = 0;
      return;
    }
  }
  coor_.x += direct_speed_.x * time;
  coor_.y += direct_speed_.y * time;

  int h = 54, w = 30;  // 36?
  CheckMap(time, coor_.x, coor_.y, h, w, map, heroes);

  sprite_->setPosition(coor_.x, coor_.y);
  sprite_->setTextureRect(rectangle);
  last_rect_ = rectangle;
}

const sf::Sprite* Player::GetSprite() const {
  return sprite_;
}

double Player::GetX() const {
  return coor_.x;
}

double Player::GetY() const {
  return coor_.y;
}

std::vector<std::string> Player::GetActiveQuests() const {
  return active_quests_;
}

void Player::AddNewQuest(const std::string& new_quest) {
  active_quests_.push_back(new_quest);
}

int Player::GetExp() const {
  return exp_;
}

int Player::GetHealth() const {
  return health_;
}

int Player::Attack() const {
  return attack_;
}

int Player::GetDefense() const {
  return defense_;
}

bool Player::IsCantGo(int type, const std::vector<QuestHero>& heroes) const {
  if (type >= 31 && type <= 43) {
    return true;
  }
//  for (int i = 0; i < HEROES_CNT; ++i) {
//    int hero_x = ceil(heroes[i].GetX()) / TILE_SIZE;
//    int hero_y = ceil(heroes[i].GetY()) / TILE_SIZE;
//    int player_x = ceil(coor_.x) / TILE_SIZE;
//    int player_y = ceil(coor_.y) / TILE_SIZE;
//    if (hero_x == player_x) {
//      if (hero_y == player_y + 1 ||
//          hero_y == player_y - 1) {
//        return true;
//      }
//    } else if (hero_y == player_y) {
//      if (hero_x == player_x + 1 ||
//          hero_x == player_x - 1) {
//        return true;
//      }
//    }
//  }
  return false;
}
void Player::CheckMap(double time, double x, double y, int h, int w,
                      const std::vector<std::vector<int>>& map,
                      const std::vector<QuestHero>& heroes) {
  x = ceil(x);
  y = ceil(y);
  int left_i = y / TILE_SIZE;
  int right_i = (y + h) / TILE_SIZE;
  int left_j = x / TILE_SIZE;
  int right_j = (x + w) / TILE_SIZE;
  for (int i = left_i; i <= right_i; ++i) {
    for (int j = left_j; j <= right_j; ++j) {
      if (!IsCantGo(map[i][j], heroes)) continue;
      coor_.y -= direct_speed_.y * time;
      coor_.x -= direct_speed_.x * time;
      return;
    }
  }
}
