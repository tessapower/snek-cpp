#ifndef ROCK_H
#define ROCK_H

#include "Board.h"
#include "Colors.h"
#include "Location.h"

class Rock {
 public:
  /**
   * @brief A nasty looking rock, watch out for it.
  */
  Rock(Location const& loc) : _location(loc){};

  /**
   * @brief Draw this Rock on the given Board.
  */
  void draw(Board& brd) const noexcept { brd.drawCell(_location, kColor); }

  /**
   * @brief The Location of this Rock on the Board.
  */
  Location const& location() const noexcept { return _location; }

 private:
  Location _location;
  static constexpr Color kColor = Colors::Gray;
};

#endif  // ROCK_H
