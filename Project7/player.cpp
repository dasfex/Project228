#include "constants.h"
#include "player.h"
#include <iostream>

Player::Player(
    const sf::String &file,
    double x,
    double y,
    int health,
    int attack,
    int defense)
    : health_(health), coor_(x, y), attack_(attack), defense_(defense), file_(file) {

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

void Player::Move(sf::RenderWindow *window, int time,
                  const std::vector<std::vector<int>> &map,
                  const std::vector<QuestHero> &heroes,
                  std::vector<Enemy> &enemies, std::pair<bool,
    std::pair<int, Direction>> &is_show_bot_bullet) {
  speed_ = 0.27;  // 0.27
  cur_frame_ += 0.009 * time;
  if (cur_frame_ > 4) {
    cur_frame_ -= 4;
  }

  sf::IntRect rectangle;
  switch (dir_) {
    case Direction::kNorth: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 168, 36, 54);
      direct_speed_ = sf::Vector2f(0, -speed_);
      last_dir_ = Direction::kNorth;
      break;
    }
    case Direction::kSouth: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 1, 36, 54);
      direct_speed_ = sf::Vector2f(0, speed_);
      last_dir_ = Direction::kSouth;
      break;
    }
    case Direction::kEast: {
      rectangle = sf::IntRect(7 + 40 * int(cur_frame_), 111, 22, 54);
      direct_speed_ = sf::Vector2f(speed_, 0);
      last_dir_ = Direction::kEast;
      break;
    }
    case Direction::kWest: {
      rectangle = sf::IntRect(9 + 40 * int(cur_frame_), 56, 22, 54);
      direct_speed_ = sf::Vector2f(-speed_, 0);
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

  //enemies[0].DrawBullet(window, Direction::kNorth);



  int h = 54, w = 30;  // 36?
  CheckMap(time, coor_.x, coor_.y, h, w, map, heroes, enemies);

  sprite_->setPosition(coor_);
  sprite_->setTextureRect(rectangle);
  last_rect_ = rectangle;
}

const sf::Sprite *Player::GetSprite() const {
  return sprite_;
}

sf::Vector2f Player::GetCoor() const {
  return coor_;
}

std::vector<std::string> Player::GetActiveQuests() const {
  return active_quests_;
}

void Player::AddNewQuest(const std::string &new_quest) {
  active_quests_.push_back(new_quest);
}

void Player::DeleteQuest(const std::string &quest) {
  auto it = std::find(begin(active_quests_),
                      end(active_quests_), quest);
  if (it != end(active_quests_)) {
    active_quests_.erase(it);
  }
}

int Player::GetExp() const {
  return exp_;
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

void Player::AddExp(int exp) {
  exp_ += exp;
}

bool Player::IsCantGo(int type) const {
  return type >= 31 && type <= 43;
}

void Player::CheckMap(double time, double x, double y, int h, int w,
                      const std::vector<std::vector<int>> &map,
                      const std::vector<QuestHero> &heroes,
                      const std::vector<Enemy> &enemies) {
  x = ceil(x);
  y = ceil(y);
  // left top angle is (0, 0)
  // y - on right
  // x - on down
  int left_i = y;
  int right_i = (y + h);
  int left_j = x;
  int right_j = (x + w);

  bool is_bad_pos = false;
  for (int k = 0; k < HEROES_CNT; ++k) {
    if (!heroes[k].IsHeroExist()) {
      continue;
    }
    int hero_left_i = ceil(heroes[k].GetY());
    // [0, 1] : 0 - width = y
    int hero_right_i = ceil(heroes[k].GetY() + heroes[k].GetImgSize().x);
    int hero_left_j = ceil(heroes[k].GetX());
    // [0, 1] : 1 - height = x
    int hero_right_j = ceil(heroes[k].GetX() + heroes[k].GetImgSize().y);

    for (int i = left_i; i < right_i; ++i) {
      for (int j = left_j; j < right_j; ++j) {
        is_bad_pos |=
            hero_left_i <= i && i <= hero_right_i
                && hero_left_j <= j && j <= hero_right_j;
      }
    }
  }

  for (const auto &enemy : enemies) {
    if (!enemy.IsExist()) continue;
    int enemie_left_i = ceil(enemy.GetCoor().y);
    // [0, 1] : 0 - width = y
    int enemie_right_i =
        ceil(enemy.GetCoor().y + enemy.GetImgSize().x);
    int enemie_left_j = ceil(enemy.GetCoor().x);
    // [0, 1] : 1 - height = x
    int enemie_right_j =
        ceil(enemy.GetCoor().x + enemy.GetImgSize().y);

    for (int i = left_i; i < right_i; ++i) {
      for (int j = left_j; j < right_j; ++j) {
        is_bad_pos |=
            enemie_left_i <= i && i <= enemie_right_i
                && enemie_left_j <= j && j <= enemie_right_j;
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

void Player::SetHealth(int add_health) {
  health_ += add_health;
}

Direction Player::GetDirection() const {
  return dir_;
}

Direction Player::GetLastDirection() const {
  return last_dir_;
}

Player::~Player() {
  delete image_;
  delete texture_;
  delete sprite_;
  delete bullet_;
}

Bullet *Player::GetBullet() {
  return bullet_;
}

void Player::LevelUp() {
  level_++;
  attack_ += 3;
  defense_ += 5;
}

int Player::GetLevel() {
  return level_;
}

void Player::SetAttack(int attack) {
  attack_ += attack;
}
void Player::SetDefense(int defense) {
  defense_ += defense;
}

bool Player::SubtractHealth(int health) {
  health_ -= health;
  if (health_ <= 0) {
    health = 0;
    is_alive_ = false;
  }
  return false;
}