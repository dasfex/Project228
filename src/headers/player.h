#ifndef PLAYER_H
#define PLAYER_H


class player
{
public:
    player(int health, int attack, int speed, int defense)
    : health_(health)
    , attack_(attack)
    , speed_(speed)
    , defense_(defense) {}

    int GetX() const;
    int GetY() const;


    void Move();

private:
    int health_;
    int attack_;
    int speed_;
    int defense_;
    int coor_x_ = 100;  // для координат надо установить некоторые изначальные значения,
    int coor_y_ = 100;  // которые будут для всех одинаковыми

    enum direction{N = 0, E, S, W};
};

#endif // PLAYER_H
