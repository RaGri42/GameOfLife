// Copyright 2021  grimm-engineering
// info@grimm-engineering.de
// Author: Raphael Grimm

// Class for GameOfLife

#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include "./GameOfLifeFigures.h"

// Size of Display
const int _MAX_GRID_SIZE = 1000;

class GameOfLife {
 public:
    // Constructor
    GameOfLife();
    // Start the Game
    void play();
    // initialize Game
    void initialize();
    // Destructor
    ~GameOfLife();  // Destructor

 private:
  // Declare 2 Grids
  bool _grid1[_MAX_GRID_SIZE][_MAX_GRID_SIZE];
  bool _grid2[_MAX_GRID_SIZE][_MAX_GRID_SIZE];
  // Pointers for the Grids
  bool (*_oldGrid)[_MAX_GRID_SIZE][_MAX_GRID_SIZE];
  bool (*_newGrid)[_MAX_GRID_SIZE][_MAX_GRID_SIZE];
  // Coordinates of the last clicked Position
  int _lastClickedX;
  int _lastClickedY;
  // Gamemode
  bool _running = false;
  // Living cells
  int _livingCells;
  // Dimension of Cells
  int _cellSizeX;
  int _cellSizeY;
  // Steps
  int _steps;
  // __________________________________________________________

  // show state
  void showState();

  void updateState();

  int aliveNeighbours(int x, int y);

  int processUserInput(int key);

  void insertFigure(int x, int y, GameOfLifeFigures figure);
};
#endif  // GAMEOFLIFE_H_
