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
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License along    *
 * with The Chili DirectX Framework.                                          *
 * If not, see <http://www.gnu.org/licenses/>.                                *
 ******************************************************************************/
#ifndef GAME_H
#define GAME_H

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

/**
 * @brief A class for all the snek game data and logic.
*/
class Game {
public:
  Game(class MainWindow& wnd);
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  void Go();
private:
  void ComposeFrame();
  void UpdateModel();

  /**
   * @brief Handles how snek should move. If snek ate an apple, makes sure
   *   snek grows. If snek dies, then sets gameover.
  */
  void handleSnakeMovement() noexcept;

  /**
   * @brief Used to check if snek's current move results in eating an apple.
  */
  bool willEatApple() const noexcept;

  /**
   * @brief Returns a random location on the Board free from rocks, apples, and
   * snek.
  */
  Location const randomFreeLocation() noexcept;

  /**
   * @brief Call to respond to the player pressing the arrow keys.
  */
  void handlePlayerInput() noexcept;

  /**
   * @brief Updates the pending direction, making sure the player can't turn
   *   snek back on itself.
  */
  void updateNextDirection(Direction const& nextDir) noexcept;

private:
  MainWindow& _wnd;
  Graphics _gfx;

  // Board & game state
  Board _brd;
  bool _hasGameStarted = false;
  bool _isGameOver = false;
  int _frameCount = 0;
  int _score = 0;

  // Snek & movement related things
  Snake _snek;
  Direction _dir = Direction::RIGHT;
  Direction _pendingDir = Direction::NONE;
  static constexpr int kMovePeriod = 8;

  // Random number generation for random locations on the Board
  std::random_device _rd;
  std::mt19937 _rng;
  std::uniform_int_distribution<int> _xDist;
  std::uniform_int_distribution<int> _yDist;

  // The goodies and the baddies
  Apple _apple;
  std::vector<Rock> _rocks{};
};

#endif // GAME_H
