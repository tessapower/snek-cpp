#ifndef ROCK_H
#define ROCK_H

#include "Board.h"
#include "Colors.h"
#include "Location.h"

class Rock {
 public:
  Rock(Location const& loc) : _location(loc){};

  void draw(Board& brd) const noexcept { brd.drawCell(_location, kColor); }

  Location const& location() const noexcept { return _location; }

 private:
  Location _location;
  static constexpr Color kColor = Colors::Gray;
};

#endif  // ROCK_H
