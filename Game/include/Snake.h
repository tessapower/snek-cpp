#ifndef SNAKE_H
#define SNAKE_H

#include "Board.h"
#include "Direction.h"
#include "Location.h"
#include <vector>

class Snake {
 public:
  Snake(Location const& l)
      : _location(l), _rng(_rd()), _randomTailColor(0, kNumTailColors - 1) {
    // Add first two segments of snek
    _segments.emplace_back(
        Segment{{l.x - 1, l.y}, kTailColors[_randomTailColor(_rng)]});
    _segments.emplace_back(
        Segment{{l.x - 2, l.y}, kTailColors[_randomTailColor(_rng)]});
  }
  void draw(Board& brd) const noexcept;
  void move(Direction const dir) noexcept;
  bool isOnTile(Location const& l) const noexcept;
  void moveAndGrow(Direction const dir) noexcept;

  Location const& location() const noexcept { return _location; }

 private:
  Location _location;

  class Segment {
   public:
    Segment(const Color c) : _location({0, 0}), _color(c) {}
    Segment(Location const& l, const Color c) : _location(l), _color(c) {}
    void draw(Board& brd) const noexcept;

    Location const& location() const noexcept { return _location; }

    void follow(Location const& next) { _location = next; }

   private:
    Location _location;
    Color _color;
  };

  static constexpr int kMaxSegments = 20;
  std::vector<Segment> _segments;

  static constexpr Color kHeadColor = Colors::MakeRGB(119u, 167u, 117u);
  static constexpr int kNumTailColors = 4;
  static constexpr Color kTailColors[kNumTailColors] = {
      Colors::MakeRGB(96u, 149u, 102u), Colors::MakeRGB(60u, 108u, 70u),
      Colors::MakeRGB(44u, 78u, 51u), Colors::MakeRGB(60u, 108u, 70u)};

  std::random_device _rd;
  std::mt19937 _rng;
  std::uniform_int_distribution<int> _randomTailColor;
};

#endif // SNAKE_H
