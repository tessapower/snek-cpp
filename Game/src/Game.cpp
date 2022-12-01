/******************************************************************************
 * Chili DirectX Framework Version 16.07.20                                   *
 * Game.cpp                                                                   *
 * Copyright 2016 PlanetChili <http://www.planetchili.net>                    *
 *                                                                            *
 * This file is part of The Chili DirectX Framework.                          *
 *                                                                            *
 * The Chili DirectX Framework is free software: you can redistribute it      *
 * and/or modify it under the terms of the GNU General Public License as      *
 * published by the Free Software Foundation, either version 3 of the         *
 * License, or (at your option) any later version.                            *
 *                                                                            *
 * The Chili DirectX Framework is distributed in the hope that it will be     *
 * useful,but WITHOUT ANY WARRANTY; without even the implied warranty of      *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License along    *
 * with The Chili DirectX Framework.                                          *
 * If not, see <http://www.gnu.org/licenses/>.                                *
 ******************************************************************************/
#include "Game.h"

#include <algorithm>
#include <iterator>

#include "MainWindow.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
    : _wnd(wnd),
      _gfx(wnd),
      _brd(_gfx),
      _rng(_rd()),
      _xDist(0, _brd.cols() - 1),
      _yDist(0, _brd.rows() - 1),
      _snek({3, 3}),
      _apple({0, 0}) {
  // We always create an apple at location (0, 0) and then immediately move it
  // to a random location on the board
  _apple.location(randomFreeLocation());
}

void Game::Go() {
  _gfx.BeginFrame();
  UpdateModel();
  ComposeFrame();
  _gfx.EndFrame();
}

void Game::UpdateModel() {
  if (!_hasGameStarted && _wnd.kbd.KeyIsPressed(VK_RETURN)) {
    _hasGameStarted = true;
  }

  if (_hasGameStarted && !_isGameOver) {
    if (_frameCount++ % kMovePeriod == 0) {
      handleSnakeMovement();
    }
    handlePlayerInput();
  }
}

void Game::handleSnakeMovement() noexcept {
  if (_pendingDir != Direction::NONE) {
    _dir = _pendingDir;
    _pendingDir = Direction::NONE;
  }

  const auto& nextLoc = _snek.location().next(_dir);

  if (!_brd.isWithinBoard(nextLoc) || _snek.isOnTile(nextLoc)
    || std::any_of(begin(_rocks), end(_rocks), [&](Rock const& r) {
        return r.location() == nextLoc;
      })) {
    _isGameOver = true;

    return;
  }

  if (ateApple()) {
    _snek.moveAndGrow(_dir);
    _score++;

    _apple.location(randomFreeLocation());
    if (_rng() % 100 > 30) _rocks.emplace_back(Rock{randomFreeLocation()});
  } else {
    _snek.move(_dir);
  }
}

bool Game::ateApple() const noexcept {
  const auto& nextLoc = _snek.location().next(_dir);

  return _apple.location() == nextLoc;
}

Location const Game::randomFreeLocation() noexcept {
  auto isTileFree = [&](Location const& loc) {
    return !_snek.isOnTile(loc) && _apple.location() != loc &&
           std::none_of(begin(_rocks), end(_rocks),
                        [&](Rock const r) { return r.location() == loc; });
  };

  Location randomLoc;
  do {
    randomLoc = {(uint8_t)_xDist(_rng), (uint8_t)_yDist(_rng)};
  } while (!isTileFree(randomLoc));

  return randomLoc;
}

void Game::handlePlayerInput() noexcept {
  if (_wnd.kbd.KeyIsPressed(VK_UP)) {
    updateNextDirection(Direction::UP);
  } else if (_wnd.kbd.KeyIsPressed(VK_DOWN)) {
    updateNextDirection(Direction::DOWN);
  } else if (_wnd.kbd.KeyIsPressed(VK_LEFT)) {
    updateNextDirection(Direction::LEFT);
  } else if (_wnd.kbd.KeyIsPressed(VK_RIGHT)) {
    updateNextDirection(Direction::RIGHT);
  }
}

void Game::updateNextDirection(Direction const& nextDir) noexcept {
  // Don't do anything if we're already going (or planning to go) in this
  // direction
  if (_dir == nextDir || _pendingDir == nextDir) return;

  // Make sure we can't go in the exact opposite direction
  switch (nextDir) {
    case Direction::UP:
      if (_dir == Direction::DOWN) return;
      break;
    case Direction::DOWN:
      if (_dir == Direction::UP) return;
      break;
    case Direction::LEFT:
      if (_dir == Direction::RIGHT) return;
      break;
    case Direction::RIGHT:
      if (_dir == Direction::LEFT) return;
      break;
  }

  _pendingDir = nextDir;
}

void Game::ComposeFrame() {
  if (!_hasGameStarted) {
    SpriteCodex::drawTitle(_gfx);

    return;
  }

  _brd.drawBorder();
  _snek.draw(_brd);
  _apple.draw(_brd);
  std::ranges::for_each(begin(_rocks), end(_rocks),
                        [&](Rock const r) { r.draw(_brd); });

  if (_isGameOver) {
    SpriteCodex::drawGameOver(_gfx);
  }
}
