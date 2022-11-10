#pragma once

#include <cstdint>

class Location {
 public:
  Location(uint8_t x = 0, uint8_t y = 0) : x(x), y(y){};
  
  void add(Location delta) {
    x += delta.x;
    y += delta.y;
  }

  uint8_t x;
  uint8_t y;
};
