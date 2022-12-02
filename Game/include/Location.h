#ifndef LOCATION_H
#define LOCATION_H

#include <cstdint>

#include "Direction.h"

/**
 * @brief Represents a location (x, y) on a 2D game board.
*/
class Location {
 public:
  Location(int x = 0, int y = 0) : x(x), y(y){};

  void add(Location const& delta) {
    x += delta.x;
    y += delta.y;
  }

  Location const next(Direction dir) const noexcept {
    switch (dir) {
      case Direction::UP:
        return Location{x, y - 1};
      case Direction::DOWN:
        return Location{x, y + 1};
      case Direction::LEFT:
        return Location{x - 1, y};
      case Direction::RIGHT:
        return Location{x + 1, y};
      default:
        return Location{x, y};
    };
  };

  int x;
  int y;
};

inline bool operator==(Location const& lhs, Location const& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

#endif // LOCATION_H
