#pragma once
#include "Board.h"
#include "Direction.h"
#include "Location.h"

class Snake {
 public:
  Snake(Location const& l)
      : _location(l), _rng(_rd()), _randomTailColor(0, _numTailColors - 1)
  {
    _segments.emplace_back(
      Segment{
        {l.x - 1, l.y},
        _tailColors[_randomTailColor(_rng)]
      }
    );
    _segments.emplace_back(
      Segment{
        {l.x - 2, l.y},
        _tailColors[_randomTailColor(_rng)]
      }
    );
  }
  void draw(Board& brd) const noexcept;
  void move(Direction const dir) noexcept;
  bool isCollidingWithSelf() const noexcept;
  bool isOnTile(Location const& l) const noexcept;
  void moveAndGrow(Direction const dir) noexcept;

  Location const& location() const noexcept { return _location; }
   
 private:
  Location _location;

  class Segment {
   public:
    Segment(const Color c) : _location({0, 0}), _color(c){}
    Segment(Location const& l, const Color c) : _location(l), _color(c){}
    void draw(Board& brd) const noexcept;
    
    Location const& location() const noexcept { return _location; }

    void follow(Location const& next) { _location = next; }
    
   private:
    Location _location;
    Color _color;
  };

  std::vector<Segment> _segments{};

  static constexpr Color _headColor = Colors::MakeRGB(236u, 243u, 158u);
  static constexpr int _numTailColors = 4;
  static constexpr Color _tailColors[_numTailColors] = {
    Colors::MakeRGB(44u, 99u, 44u),
    Colors::MakeRGB(79u, 119u, 45u),
    Colors::MakeRGB(144u, 169u, 85u),
    Colors::MakeRGB(49u, 87u, 44u)
  };

  std::random_device _rd;
  std::mt19937 _rng;
  std::uniform_int_distribution<int> _randomTailColor;
};