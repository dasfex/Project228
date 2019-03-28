#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPainter>
#include <QImage>
#include <QPicture>

enum class Direction {
    N = 0,
    E,
    S,
    W
};

class Player : public QObject {
    Q_OBJECT
public:
    Player(int, int, int, int);

    double GetX() const;
    double GetY() const;

    void SetDirection(Direction); // устанавливаем направление движения

    void SetSpeed(double);        // устанавливаем скорость движения по карте
    void UpdateSpeed();           // изменяем скорости по координатам
    void Move(double);

    void SetDirectionForFrame(Direction);

    int GetHealth() const;
    int GetAttack() const;
    int GetDefense() const;

    void SetHealth(int);
    void SetAttack(int);
    void SetDefense(int);

    ~Player() {}

public slots:

signals:

private:

    class Coordinates {
    public:
        double x;
        double y;

        Coordinates(double x, double y)
        : x(x)
        , y(y) {}

        Coordinates& operator=(const Coordinates& other) {
            x = other.x;
            y = other.y;
            return *this;
        }
    };

    int health_;
    int attack_;
    int speed_;
    int defense_;
    Direction direction_; // направление движения игрока на карте
    double map_speed_ = 0; // скорость, с которой игрок перемещается по карте
    Coordinates coordinates_ = {100, 100};  // для координат надо установить некоторые изначальные значения,
                                           //которые будут для всех одинаковыми
    Coordinates dir_speed_ = {0, 0}; // скорости перемещения в ДАННЫЙ МОМЕНТ
                                     // на карте по каждой из координат
};

#endif // PLAYER_H
