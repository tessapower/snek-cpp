#ifndef SNAKE_H
#define SNAKE_H

#include "Board.h"
#include "Direction.h"
#include "Location.h"
#include <vector>

class Snake {
 public:
  /**
   * @brief Snek! Looks kinda hungry, better feed it an Apple.
  */
  Snake(Location const& l)
      : _location(l), _rng(_rd()), _randomTailColor(0, kNumTailColors - 1) {
    // Add first two segments of snek
    _segments.emplace_back(
        Segment{{l.x - 1, l.y}, kTailColors[_randomTailColor(_rng)]});
    _segments.emplace_back(
        Segment{{l.x - 2, l.y}, kTailColors[_randomTailColor(_rng)]});
  }

  /**
   * @brief Draw this Snake to the Board.
   * @param brd 
  */
  void draw(Board& brd) const noexcept;

  /**
   * @brief Move this Snake in the given Direction. Does not make any
   *   guarantees that its Location after moving in this Direction is within
   *   the Board.
  */
  void move(Direction const dir) noexcept;

  /**
   * @brief Move this Snake in the given Direction and grow by 1x tail segment.
   *   Like move(), doesn't make guarantees that its location after moving in
   *   this Direction is within the Board.
  */
  void moveAndGrow(Direction const dir) noexcept;

  /**
   * @brief Whether any part of Snake is located on the given location.
  */
  bool isOnLocation(Location const& l) const noexcept;

  /**
   * @brief I bet you know what this is! Go on, take a guess.
  */
  Location const& location() const noexcept { return _location; }

 private:
  Location _location;

  class Segment {
   public:
    /**
     * @brief A piece of the Snake's tail.
    */
    Segment(const Color c) : _location({0, 0}), _color(c) {}
    Segment(Location const& l, const Color c) : _location(l), _color(c) {}

    /**
     * @brief Draw this Segment to the given Board.
    */
    void draw(Board& brd) const noexcept;

    Location const& location() const noexcept { return _location; }

    /**
     * @brief Updates the Location of this Segment to follow the given Segment.
     * Should only be used working from the end of the tail towards the head.
    */
    void follow(Location const& next) { _location = next; }

   private:
    Location _location;
    Color _color;
  };

  static constexpr int kMaxSegments = 20;
  std::vector<Segment> _segments;

  // Pretty colors
  static constexpr Color kHeadColor = Colors::MakeRGB(119u, 167u, 117u);
  static constexpr int kNumTailColors = 4;
  static constexpr Color kTailColors[kNumTailColors] = {
      Colors::MakeRGB(96u, 149u, 102u), Colors::MakeRGB(60u, 108u, 70u),
      Colors::MakeRGB(44u, 78u, 51u), Colors::MakeRGB(60u, 108u, 70u)};

  // Used for generating random colors for each Segment in the tail.
  std::random_device _rd;
  std::mt19937 _rng;
  std::uniform_int_distribution<int> _randomTailColor;
};

#endif // SNAKE_H
