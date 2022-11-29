#include "Board.h"

#include <assert.h>

void Board::drawCell(Location l, Color c) {
  assert(isWithinBoard(l));

  auto screenX = _x + _boardBorder + l.x * _cellSize;
  auto screenY = _y + _boardBorder + l.y * _cellSize;

  // Cell Border
  _gfx.DrawRectDim(screenX, screenY, _cellSize, _cellSize, Colors::Black);
  // Cell Contents
  _gfx.DrawRectDim(screenX + _cellBorder, screenY + _cellBorder, _innerCellSize,
                   _innerCellSize, c);
}

void Board::drawBorder() {
  _gfx.DrawRectDim(_x, _y, _boardWidth, _boardHeight, Colors::LightGray);
  _gfx.DrawRectDim(_x + _boardBorder, _y + _boardBorder,
                   _boardWidth - _boardBorder * 2,
                   _boardHeight - _boardBorder * 2, Colors::Black);
}

bool Board::isWithinBoard(Location l) const {
  return l.x >= 0 && l.x < _numCols && l.y >= 0 && l.y < _numRows;
}
