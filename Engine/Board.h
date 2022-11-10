#pragma once

#include <random>
#include "Graphics.h"
#include "Location.h"

class Board {
 public:
  Board(Graphics &gfx) : _gfx(gfx) {
    _x = (_gfx.ScreenWidth - (_numCols * _cellSize)) / 2;
    _y = (_gfx.ScreenHeight - (_numRows * _cellSize)) / 2;
  }

  uint8_t rows() { return _numRows; }
  
  uint8_t cols() { return _numCols; }

  bool isWithinBoard(Location l) const;

  void drawCell(Location l, Color c);

  void drawBorder();

 private:
  int _x;
  int _y;
  Graphics& _gfx;

  static constexpr uint8_t _numCols = 30;
  static constexpr uint8_t _numRows = 20;
  static constexpr int _cellSize = 20;
  static constexpr int _boardBorder = 4;
  static constexpr int _cellBorder= 2;
  static constexpr int _innerCellSize = _cellSize - _boardBorder;
  static constexpr int _boardWidth = _numCols * _cellSize + _boardBorder * 2;
  static constexpr int _boardHeight = _numRows * _cellSize + _boardBorder * 2;
};
