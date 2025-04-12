#include <iostream>

#include "sudoku.hh"

using namespace std;



int main() {
    cout << "Sudoku: " << endl;

    Sudoku tablero;

    tablero.leerTablero();
    tablero.imprimirTablero();

    tablero.resolver();

    tablero.imprimirTablero();
}