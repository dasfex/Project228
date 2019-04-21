#include "quest_hero.h"

QuestHero::QuestHero(
    double x, double y,
    const sf::String& file_img,
    const sf::String& file_for_quest,
    const sf::String& file_after_quest,
    int reward, int x_img, int y_img,
    int width_img, int height_img)
    : coor_(x, y)
    , image_file_(file_img)
    , file_for_quest_(file_for_quest)
    , file_after_quest_(file_after_quest)
    , reward_exp_(reward)
    , coor_for_img_(x_img, y_img)
    , size_for_img_(width_img, height_img) {

  image_->loadFromFile(image_file_);
  image_->createMaskFromColor(sf::Color(255, 255, 255));
  texture_->loadFromImage(*image_);

  sprite_->setTexture(*texture_);
  sf::IntRect rect(coor_for_img_.first, coor_for_img_.second, size_for_img_.first, size_for_img_.second)
  sprite_->setTextureRect(rect);
  sprite_->setPosition(coor_.x, coor_.y);

  //ifstream get_text_for_quest(fil)
}

double QuestHero::GetX() const {
  return coor_.x;
}

double QuestHero::GetY() const {
  return coor_.y;
}
