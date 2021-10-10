// Copyright Raphael Grimm 2021
// Uebungsblatt 5 SS 2018 Programmieren in C++
// Bei Frau Prof. Dr Hannah Bast
//

#include<stdio.h>
#include "./GameOfLifeFigures.h"

// ________________________________________________________________________>
const int GameOfLifeFigures::_glider[MAX_FIG_SIZE][2] = {
  {1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2} };

const int GameOfLifeFigures::_bofrog[MAX_FIG_SIZE][2] = {
  {0, 0}, {1, 0}, {2, 0}, {0, 1}, {2, 1}, {0, 2}, {1, 2}, {2, 2} };


const int GameOfLifeFigures::_gliderfactory[MAX_FIG_SIZE][2] = {
  {24, 0},
  {22, 1}, {24, 1},
  {12, 2}, {13, 2}, {20, 2}, {21, 2}, {34, 2}, {35, 2},
  {11, 3}, {15, 3}, {20, 3}, {21, 3}, {34, 3}, {35, 3},
  {0, 4}, {1, 4}, {10, 4}, {16, 4}, {20, 4}, {21, 4},
  {0, 5}, {1, 5}, {10, 5}, {14, 5}, {16, 5}, {17, 5}, {22, 5}, {24, 5},
  {10, 6}, {16, 6}, {24, 6},
  {11, 7}, {15, 7},
  {12, 8}, {13, 8}
};



GameOfLifeFigures::GameOfLifeFigures() {
  _length = 0;
  _cells = NULL;
}


void GameOfLifeFigures::select(int kind) {
  switch (kind) {
    // No 0 = glider
    case 0:
      _cells = &GameOfLifeFigures::_glider;
      _length = 5;
     break;
    // No 1 = bofrog
    case 1:
      _cells = &GameOfLifeFigures::_bofrog;
      _length = 8;
     break;
    // No 2 = glider_factory
    case 2:
      _cells = &GameOfLifeFigures::_gliderfactory;
      _length = 36;
      break;
  }
  return;
}

int GameOfLifeFigures::getNumberOfCells() {
    return _length;
}

int GameOfLifeFigures:: getRelativeX(int i) {
  return (*_cells)[i][0];
}

int GameOfLifeFigures::getRelativeY(int i) {
  return (*_cells)[i][1];
}
