/******************************************************************************
 * Chili DirectX Framework Version 16.07.20                                   *
 * Game.h                                                                     *
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
#pragma once

#include <random>
#include <vector>
#include "Apple.h"
#include "Rock.h"
#include "Board.h"
#include "Graphics.h"
#include "Direction.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Snake.h"

class Game {
public:
  Game(class MainWindow& wnd);
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  void Go();
private:
  void ComposeFrame();
  void UpdateModel();

  /********************************/
  /*  User Functions              */
  void handleSnakeMovement() noexcept;
  bool ateApple() const noexcept;
  Location const randomFreeLocation() noexcept;
  bool checkGameOverConditions() const noexcept;
  void handlePlayerInput() noexcept;
  void updateNextDirection(Direction const& nextDir) noexcept;
  /********************************/
private:
  MainWindow& _wnd;
  Graphics _gfx;

  /********************************/
  /*  User Variables              */
  Board _brd;
  Snake _snek;
  bool _hasGameStarted = false;
  bool _isGameOver = false;
  int _frameCount = 0;
  int _score = 0;

  Direction _dir = Direction::RIGHT;
  Direction _pendingDir = Direction::NONE;
  static constexpr int _movePeriod = 8;

  std::random_device _rd;
  std::mt19937 _rng;
  std::uniform_int_distribution<int> _xDist;
  std::uniform_int_distribution<int> _yDist;

  Apple _apple;
  std::vector<Rock> _rocks{};
  /********************************/
};
