#include "Board.h"

#include <assert.h>

void Board::drawCell(Location l, Color c) {
  assert(isWithinBoard(l));

  auto screenX = _x + kBoardBorder + l.x * kCellSize;
  auto screenY = _y + kBoardBorder + l.y * kCellSize;

  // Cell Border
  _gfx.DrawRectDim(screenX, screenY, kCellSize, kCellSize, Colors::Black);
  // Cell Contents
  _gfx.DrawRectDim(screenX + kCellBorder, screenY + kCellBorder, kInnerCellSize,
                   kInnerCellSize, c);
}

void Board::drawBorder() {
  _gfx.DrawRectDim(_x, _y, kBoardWidth, kBoardHeight, Colors::LightGray);
  _gfx.DrawRectDim(_x + kBoardBorder, _y + kBoardBorder,
                   kBoardWidth - kBoardBorder * 2,
                   kBoardHeight - kBoardBorder * 2, Colors::Black);
}

bool Board::isWithinBoard(Location l) const {
  return l.x >= 0 && l.x < kNumCols && l.y >= 0 && l.y < kNumRows;
}
