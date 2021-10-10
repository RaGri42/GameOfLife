// Copyright Raphael Grimm 2021
// Uebungsblatt 4 SS2018 Programmieren in C++
// bei Prof. Dr. Hannah Bast

// _____________________________________________________
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "./GameOfLife.h"
#include "./GameOfLifeFigures.h"
// _____________________________________________________
GameOfLife::GameOfLife() {
// Grids füllen
for (int x = 0; x < _MAX_GRID_SIZE; ++x) {
  for (int y = 0; y < _MAX_GRID_SIZE; ++y) {
    _grid1[x][y] = false;
    _grid2[x][y] = false;
  }
  }
// Hier werden die Variablen gesetzt
// Declare Cell-Size
_cellSizeX = 2;
_cellSizeY = 1;

// Programmkontrolle
_running = false;
_livingCells = 0;
_steps = 0;

// Mouse Coordinates
_lastClickedX = -1;
_lastClickedY = -1;

// Pointer zuweisen
_oldGrid = &_grid1;
_newGrid = &_grid2;
}

void GameOfLife::initialize() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  mousemask(ALL_MOUSE_EVENTS, NULL);
}
void GameOfLife::showState() {
    for (int x = 0; x < _MAX_GRID_SIZE ; ++x) {
      for (int y = 0; y < _MAX_GRID_SIZE; ++y) {
        attroff(A_REVERSE);
     if ((*_newGrid)[x][y] == true) {attron(A_REVERSE);
     }
     for (int dx = 0; dx < _cellSizeX ; ++dx) {
       for (int dy = 0; dy < _cellSizeY; ++dy) {
         mvprintw(y * _cellSizeY + dy, x * _cellSizeX + dx, " ");
       }
     }
      }
    }
    attroff(A_REVERSE);
    mvprintw(0, 0, "Step: %9d Cells alive: %4d Running: %d", _steps,
    _livingCells, _running);
    }

int GameOfLife::aliveNeighbours(int x, int y) {
  int n = 0;
  for (int a = -1; a <= 1; a++) {
    for (int b = -1; b <= 1; b++) {
           if (a == 0 && b == 0) {continue;}
           if (x + a >= 0 && x + a < _MAX_GRID_SIZE &&
              y + b >= 0 && y + b < _MAX_GRID_SIZE) {
               n += (*_oldGrid)[x+a][y+b];
           }
         }
       }
       return n;
}

void GameOfLife::updateState() {
  int n = 0;
  _livingCells = 0;
  // Das Gesamte Feld durchlaufen
  for (int x = 0; x < _MAX_GRID_SIZE; ++x) {
     for (int y = 0; y < _MAX_GRID_SIZE; ++y) {
       // lebendige Nachbarn zählen
       n = aliveNeighbours(x, y);
      (*_newGrid)[x][y] = false;
  // Entscheidung ob Zelle lebt oder tot ist
  if (((*_oldGrid)[x][y] == false)&&(n == 3)) {
      (*_newGrid)[x][y] = true;
  } else if (((*_oldGrid)[x][y]) && ((n > 1) && (n < 4))) {
      (*_newGrid)[x][y] = true;
  }
  _livingCells += (*_newGrid)[x][y];
     }
  }
}

void GameOfLife::insertFigure(int x, int y, GameOfLifeFigures figure) {
  (*_newGrid)[x][y] = false;
  for (int i = 0; i < figure.getNumberOfCells(); ++i) {
    (*_newGrid)[x + figure.getRelativeX(i)][y + figure.getRelativeY(i)] = true;
  }
}

int GameOfLife::processUserInput(int key) {
  MEVENT event;
  GameOfLifeFigures figure;
  switch (key) {
    case 27 :
      // Exit
    return -1;
    case ' ':
    // Run or Stop
    return 1;
    case 's':
    // Einzelschritt durchführen
    return 2;
    // Glieder erzeugen
    case 'g' :
    if (_lastClickedX != -1 && _lastClickedY != -1) {
    figure.select(0);
    insertFigure(_lastClickedX, _lastClickedY, figure);
    }
    break;
    // Bofrog erzeugen
    case 'b' :
    if (_lastClickedX != -1 && _lastClickedY != -1) {
    figure.select(1);
    insertFigure(_lastClickedX, _lastClickedY, figure);
    }
    break;
    // Gliderfabrik bauen
    case 'G' :
    if (_lastClickedX != -1 && _lastClickedY != -1) {
    figure.select(2);
    insertFigure(_lastClickedX, _lastClickedY, figure);
    }
    break;
    // init randomly
    case 'r' :
    for (int x=0; x < _MAX_GRID_SIZE; ++x) {
       for (int y=0; y < _MAX_GRID_SIZE; ++y) {
        (*_newGrid)[x][y] = drand48() > 0.8;
       }
    }
    break;
    case KEY_MOUSE:
    if (getmouse(&event) == OK) {
      if (event.bstate & BUTTON1_CLICKED) {
           _lastClickedX = event.x/ _cellSizeX;
           _lastClickedY =  event.y / _cellSizeY;
           (*_newGrid)[_lastClickedX][_lastClickedY] =
             !(*_newGrid)[_lastClickedX][_lastClickedY];
      }
    }
    break;
  }
  return 0;
}

void GameOfLife::play() {
  while (true) {
    int key = getch();
    int mode = processUserInput(key);
    if (mode == -1) {
      printf("dhddhd");
      break;
    }
    if (mode == 1) {
     _running = !_running;
    }
    if (_running || mode == 2) {
      bool (*tempGrid)[_MAX_GRID_SIZE][_MAX_GRID_SIZE] = _newGrid;
      _newGrid = _oldGrid;
      _oldGrid = tempGrid;
      updateState();
      _steps++;
    }
  showState();
  usleep(10*1000);
  }
}

GameOfLife::~GameOfLife() {
  endwin();  // End Screen
}
