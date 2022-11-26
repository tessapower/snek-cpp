#pragma once

#include <cstdint>
#include "Direction.h"

class Location {
 public:
  Location(uint8_t x = 0, uint8_t y = 0) : x(x), y(y){};
  
  void add(Location const& delta) {
    x += delta.x;
    y += delta.y;
  }

  Location const& next(Direction dir) const noexcept {
    switch (dir) {
      case Direction::UP:    return {x, (uint8_t)(y - 1)};
      case Direction::DOWN:  return {x, (uint8_t)(y + 1)};
      case Direction::LEFT:  return {(uint8_t)(x - 1), y};
      case Direction::RIGHT: return {(uint8_t)(x + 1), y};
      default:               return {x, y};
    };
  };

  uint8_t x;
  uint8_t y;
};

inline bool operator==(Location const& lhs, Location const& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}