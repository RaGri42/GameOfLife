// Copyright 2021  grimm-engineering
// info@grimm-engineering.de
// Author: Raphael Grimm

// ____________________________________________________________
#include "./GameOfLife.h"

// PlayGameOfLife

int main(int argc, char**argv) {
  // Deklaration und Erzeugen des Objekts
  GameOfLife game;
  // Bildschirm initialisieren
  game.initialize();
  // Spiel starten
  game.play();
}
