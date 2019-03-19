#include "headers//herosprite.h"

HeroSprite::HeroSprite(QObject* parent)
    : QObject(parent)
    , timer_(new QTimer)
    , sprite_image_(new QPixmap("img/hulk.png")) {

}

void HeroSprite::NextFrame(Direction new_dir) {
    if (previous_direction_ == new_dir) {
        ++current_frame_;
        current_frame_ %= 4;

    } else {
        previous_direction_ = new_dir;
        current_frame_ = 0;
    }
}
