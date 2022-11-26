#pragma once
#include "Board.h"
#include "Direction.h"
#include "Location.h"

class Snake {
 public:
  Snake(Location const& l) : _location(l) {
    _segments.emplace_back(Segment{{(uint8_t)(l.x - 1), l.y}, _tailColor});
    _segments.emplace_back(Segment{{(uint8_t)(l.x - 2), l.y}, _tailColor});
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

  static constexpr Color _headColor = Colors::Green;
  static constexpr Color _tailColor = Colors::Yellow;
};