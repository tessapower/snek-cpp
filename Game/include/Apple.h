#ifndef APPLE_H
#define APPLE_H

#include "Location.h"
#include "Board.h"
#include "Colors.h"

class Apple {
 public:
  Apple(Location const& loc) : _location(loc){};

  void draw(Board& brd) const noexcept { brd.drawCell(_location, kColor);
  }

  Location const& location() const noexcept { return _location; }
  void location(Location const& loc) noexcept { _location = loc; }

 private:
  Location _location;
  static constexpr Color kColor = Colors::MakeRGB(230u, 82u, 83u);
};

#endif // APPLE_H
