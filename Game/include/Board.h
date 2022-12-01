#ifndef BOARD_H
#define BOARD_H

#include <random>
#include "Graphics.h"
#include "Location.h"

class Board {
 public:
  Board(Graphics &gfx) : _gfx(gfx) {
    _x = (_gfx.ScreenWidth - (kNumCols * kCellSize)) / 2;
    _y = (_gfx.ScreenHeight - (kNumRows * kCellSize)) / 2;
  }

  uint8_t rows() { return kNumRows; }
  
  uint8_t cols() { return kNumCols; }

  bool isWithinBoard(Location l) const;
  void drawCell(Location l, Color c);
  void drawBorder();

 private:
  int _x;
  int _y;
  Graphics& _gfx;

  static constexpr uint8_t kNumCols = 36;
  static constexpr uint8_t kNumRows = 24;
  static constexpr int kCellSize = 20;
  static constexpr int kBoardBorder = 4;
  static constexpr int kCellBorder= 2;
  static constexpr int kInnerCellSize = kCellSize - kBoardBorder;
  static constexpr int kBoardWidth = kNumCols * kCellSize + kBoardBorder * 2;
  static constexpr int kBoardHeight = kNumRows * kCellSize + kBoardBorder * 2;
};

#endif // BOARD_H
