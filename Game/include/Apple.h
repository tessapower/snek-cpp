#ifndef APPLE_H
#define APPLE_H

#include "Location.h"
#include "Board.h"
#include "Colors.h"

class Apple {
 public:
  /**
   * @brief A delicious Apple! Om nom nom!
  */
  Apple(Location const& loc) : _location(loc){};

  /**
   * @brief Draw this Apple on the given Board.
  */
  void draw(Board& brd) const noexcept { brd.drawCell(_location, kColor); }

  /**
   * @brief The Location of this Apple on the Board.
  */
  Location const& location() const noexcept { return _location; }
  /**
   * @brief Set the location of this Apple on the Board.
  */
  void location(Location const& loc) noexcept { _location = loc; }

 private:
  Location _location;
  static constexpr Color kColor = Colors::MakeRGB(230u, 82u, 83u);
};

#endif // APPLE_H
