#ifndef PROJECT228_USEFUL_H
#define PROJECT228_USEFUL_H

#include "main_headers.h"

struct Coordinate {
  double x;
  double y;

  Coordinate(double x, double y)
      : x(x)
      , y(y) {}
};

enum class Direction {
  kNorth,
  kEast,
  kSouth,
  kWest,
  kStay // на месте
};

#endif //PROJECT228_USEFUL_H
