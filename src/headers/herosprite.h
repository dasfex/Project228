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

class HeroSprite : public QGraphicsItem {
    Q_OBJECT

public:
    explicit HeroSprite(QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;

    QPainterPath shape() const override {
       QPainterPath path;
       path.addRect(14, 14, 82, 42);
       return path;
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem * item, QWidget* widget) override {
        painter->drawPixmap(QRectF{0, 0, 1080, 720}, *sprite_image_, boundingRect());
    }

    void NextFrame(Direction);

public slots:

private:

    int TransformDirectionToInt(Direction) const;

    QTimer* timer_;
    QPixmap* sprite_image_;
    Direction previous_direction_;
    int current_frame_ = 0;

    struct hero_coordinate {
        int x;
        int y;
        int height;
        int width;
    };

    QVector<QVector<hero_coordinate>> sprite_coordinate = {{{4, 169, 32, 52}, {43, 170, 34, 51}, {84, 169, 32, 52}, {123, 170, 34, 51}},
                                                               {{3, 1, 33, 52}, {43, 2, 34, 52}, {84, 1, 32, 51}, {123, 2, 34,52}},
                                                               {{9, 112, 20, 53}, {49, 113, 20, 52}, {89, 112, 20, 53}, {127, 113, 22, 52}},
                                                               {{10, 56, 20, 53}, {50, 57, 21, 52}, {90, 56, 20, 53}, {129, 57, 21, 52}}};

};

#endif // HEROSPRITE_H

