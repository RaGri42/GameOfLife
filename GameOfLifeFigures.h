// Copyright Raphael Grimm 2021
// Uebungsblatt 5 SS 2018 Programmieren in C++
// Bei Frau Prof. Dr Hannah Bast
//


// ___________________________________________________
#ifndef GAMEOFLIFEFIGURES_H_
#define GAMEOFLIFEFIGURES_H_

// Maximum Size of figure
const int MAX_FIG_SIZE = 36;

class GameOfLifeFigures {
 public:
    // Constructor
    GameOfLifeFigures();

    void select(int kind);

    // Anzahl der Elemente zurückgeben
    int getNumberOfCells();

    // x-Werte zurückgeben
    int getRelativeX(int i);

    // y-Werte zurückgeben
    int getRelativeY(int i);

 private:
    // Länge der ausgewählten Figur
    int _length;

    // Pointer auf das ausgewählte Array
    const int (*_cells)[MAX_FIG_SIZE][2];

    // Array für den Glider
    static const int _glider[MAX_FIG_SIZE][2];

    // Array für BoFrog
    static const int _bofrog[MAX_FIG_SIZE][2];

    // Array für Gliderfactory
    static const int _gliderfactory[MAX_FIG_SIZE][2];
};

#endif  //  GAMEOFLIFEFIGURES_H_
