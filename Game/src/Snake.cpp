#include "Snake.h"

#include <algorithm>

void Snake::draw(Board& brd) const noexcept {
  // Draw head
  brd.drawCell(_location, kHeadColor);
  // Draw tail segments
  for (auto const& s : _segments) {
    s.draw(brd);
  }
}

void Snake::move(Direction const dir) noexcept {
  Location delta;
  switch (dir) {
    case Direction::UP:
      delta = {0, -1};
      break;
    case Direction::DOWN:
      delta = {0, 1};
      break;
    case Direction::LEFT:
      delta = {-1, 0};
      break;
    case Direction::RIGHT:
      delta = {1, 0};
      break;
    default:
      return;
  }

  // Move segments along starting at end of tail working towards head
  if (!_segments.empty()) {
    for (auto i = _segments.size() - 1; i > 0; --i) {
      _segments[i].follow(_segments[i - 1].location());
    }
    _segments.front().follow(_location);
  }

  _location.add(delta);
}

void Snake::moveAndGrow(Direction const dir) noexcept {
  // Restrict the length to an arbirtrary max length so it doesn't eventually
  // fill up the entire screen
  if (_segments.size() < kMaxSegments) {
    _segments.emplace_back(Segment(kTailColors[_randomTailColor(_rng)]));
  }
  move(dir);
}

bool Snake::isOnLocation(Location const& loc) const noexcept {
  // Is the head on this loc?
  if (_location == loc) return true;

  // Is the tail on this loc?
  if (std::any_of(begin(_segments), end(_segments),
                  [&](Segment const& s) { return s.location() == loc; })) {
    return true;
  }

  return false;
}

void Snake::Segment::draw(Board& brd) const noexcept {
  brd.drawCell(_location, _color);
}
