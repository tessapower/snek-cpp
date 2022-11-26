#include "Snake.h"
#include <algorithm>

void Snake::draw(Board& brd) const noexcept {
  // Draw head
  brd.drawCell(_location, _headColor);
  // Draw Tail
  for (auto const& s : _segments) {
    s.draw(brd);
  }
}

void Snake::move(Direction const dir) noexcept {
  Location delta;
  switch (dir) {
    case Direction::UP:    delta = {0, (uint8_t)-1}; break;
    case Direction::DOWN:  delta = {0, (uint8_t)1}; break;
    case Direction::LEFT:  delta = {(uint8_t)-1, 0}; break;
    case Direction::RIGHT: delta = {(uint8_t)1, 0}; break;
    default: return;
  }

  if (!_segments.empty()) {
    for (auto i = _segments.size() - 1; i > 0; --i) {
      _segments[i].follow(_segments[i - 1].location());
    }
    _segments.front().follow(_location);
  }

  _location.add(delta);
}

bool Snake::isCollidingWithSelf() const noexcept {
  for (auto const& s : _segments) {
    if (s.location() == _location) return true;
  }

  return false;
}

bool Snake::isOnTile(Location const& loc) const noexcept {
  if (_location == loc) return true;

  if (std::any_of(begin(_segments), end(_segments),
                  [&](Segment const& s) { return s.location() == loc; })) {
      return true;
  }

  return false;
}

void Snake::moveAndGrow(Direction const dir) noexcept {
  _segments.emplace_back(Segment(_tailColor));
  move(dir);
}

void Snake::Segment::draw(Board& brd) const noexcept {
  // TODO!
  // Select random color from list of colors
  brd.drawCell(_location, _color);
}
