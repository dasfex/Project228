#ifndef PLAYER_H
#define PLAYER_H

enum class Direction {
    N = 0 // север(верх)
    , E   // восток(право)
    , S   // юг(низ)
    , W   // запад(лево)
};

class Player
{
public:
    Player(int health, int attack, int speed, int defense)
    : health_(health)
    , attack_(attack)
    , speed_(speed)
    , defense_(defense) {}

    double GetX() const;
    double GetY() const;

    void SetDirection(Direction); // устанавливаем направление движения
    void SetSpeed(double);        // устанавливаем скорость движения по карте
    void UpdateSpeed();           // изменяем скорости по координатам
    void Move(double);            // движемся

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
    int cur_frame_; // величина, которая нужна, чтобы отрисовывать героя
    double map_speed_ = 0; // скорость, с которой игрок перемещается по карте
    Coordinates coordinates_ = {100, 100};  // для координат надо установить некоторые изначальные значения,
                                           //которые будут для всех одинаковыми
    Coordinates dir_speed_ = {0, 0}; // скорости перемещения в ДАННЫЙ МОМЕНТ
                     // на карте по каждой из координат


};

#endif // PLAYER_H
