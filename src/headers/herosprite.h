#ifndef HEROSPRITE_H
#define HEROSPRITE_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

enum class Direction {
    N = 0 // север(верх)
    , E   // восток(право)
    , S   // юг(низ)
    , W   // запад(лево)
};

class HeroSprite : public QObject {
    Q_OBJECT

public:
    explicit HeroSprite(QObject* parent = nullptr);

    void NextFrame(Direction);

public slots:

private:

    QTimer* timer_;
    QPixmap* sprite_image_;
    Direction previous_direction_;
    int current_frame_ = 0;

};

#endif // HEROSPRITE_H
