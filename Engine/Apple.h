#ifndef APPLE_H
#define APPLE_H

#include "Location.h"
#include "Board.h"
#include "Colors.h"

class Apple {
 public:
  Apple(Location const& loc) : _location(loc){};

  void draw(Board& brd) const noexcept {
    brd.drawCell(_location, _color);
  }

  Location const& location() const noexcept { return _location; }

 private:
  Location _location;
  static constexpr Color _color = Colors::Red;
};

#endif // APPLE_H
