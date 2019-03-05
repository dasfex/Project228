#ifndef PLAYER_H
#define PLAYER_H

enum class Direction {
    N = 0 // север(верх)
    , E   // восток(право)
    , S   // юг(низ)
    , W   // запад(лево)
    , P   // стоять на одном месте
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
    int health_;
    int attack_;
    int speed_;
    int defense_;
    Direction direction_; // направление движения игрока на карте
    int cur_frame_; // величина, которая нужна, чтобы отрисовывать героя
    double map_speed_ = 0; // скорость, с которой игрок перемещается по карте
    double coor_x_ = 100;  // для координат надо установить некоторые изначальные значения,
    double coor_y_ = 100;  // которые будут для всех одинаковыми
    double speed_x_; // скорости перемещения в ДАННЫЙ МОМЕНТ
    double speed_y_; // на карте по каждой из координат
};

#endif // PLAYER_H
