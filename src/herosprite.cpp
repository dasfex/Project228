#include "headers//herosprite.h"

HeroSprite::HeroSprite(QGraphicsItem* parent)
    : QGraphicsItem(parent)
    , timer_(new QTimer)
    , sprite_image_(new QPixmap("img/hulk.png")) {

}

int HeroSprite::TransformDirectionToInt(Direction direction) const {
    return static_cast<int>(direction);
}

QRectF HeroSprite::boundingRect() const {
    hero_coordinate coordinate = sprite_coordinate[TransformDirectionToInt(previous_direction_)][current_frame_];
    return QRectF(coordinate.x, coordinate.y, coordinate.width, coordinate.height);
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
