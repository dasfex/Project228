#include "quest_hero.h"

QuestHero::QuestHero(
    double x, double y,
    const std::string& file_img,
    const std::string& file_for_quest,
    const std::string& file_after_quest,
    int reward, int x_img, int y_img,
    int width_img, int height_img)
    : image_file_(file_img)
    , file_for_quest_(file_for_quest)
    , file_after_quest_(file_after_quest)
    , reward_exp_(reward)
    , coor_for_img_(x_img, y_img)
    , size_for_img_(width_img, height_img) {

  image_->loadFromFile(image_file_);
  image_->createMaskFromColor(sf::Color(255, 255, 255));
  texture_->loadFromImage(*image_);
  sprite_->setTexture(*texture_);
  sf::IntRect rect(coor_for_img_.first, coor_for_img_.second, size_for_img_.first, size_for_img_.second);
  sprite_->setTextureRect(rect);
  sprite_->setPosition(x, y);

  std::ifstream get_text_for_quest(file_for_quest_);
  getline(get_text_for_quest, text_for_quest_);
  std::ifstream get_text_after_quest(file_after_quest_);
  getline(get_text_after_quest, text_after_quest_);
}

const sf::Sprite* QuestHero::GetSprite() const {
  return sprite_;
}

const std::string& QuestHero::GetText() {
  if (!is_quest_ready) {
    return text_for_quest_;
  } else {
    ++treatment_cnt_;
    return text_after_quest_;
  }
}

int QuestHero::GetTreatment() const {
  return treatment_cnt_;
}

int QuestHero::GetReward() const {
  return reward_exp_;
}
