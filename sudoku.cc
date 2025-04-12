#include "sudoku.hh"

#include <iostream>
using namespace std;
#include <map>

// Constructores 
Sudoku::Sudoku() 
: Tablero(9, vector<int>(9, -1))
{

}

Sudoku::Sudoku(vector<vector<int>> &tablero) 
: Tablero(9, vector<int>(9))
{   
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            Tablero[i][j] = tablero[i][j];
        }
    }
}

// Metodos
void Sudoku::resolver() {
    this->resolverParcial();
    this->resolverParcialProb();
}

bool esGrupoValido(const vector<int>& grupo) {
    set<int> numeros;
    for (int num : grupo) {
        if (num < 1 || num > 9) return false; // número inválido o vacío (-1)
        if (numeros.count(num)) return false; // número repetido
        numeros.insert(num);
    }
    return true;
}
bool Sudoku::estaResulto() {
    // Verificar filas
    for (int i = 0; i < 9; ++i) {
        if (!esGrupoValido(Tablero[i])) return false;
    }

    // Verificar columnas
    for (int j = 0; j < 9; ++j) {
        vector<int> columna;
        for (int i = 0; i < 9; ++i) {
            columna.push_back(Tablero[i][j]);
        }
        if (!esGrupoValido(columna)) return false;
    }

    // Verificar subcuadros 3x3
    for (int fila = 0; fila < 9; fila += 3) {
        for (int col = 0; col < 9; col += 3) {
            vector<int> bloque;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    bloque.push_back(Tablero[fila + i][col + j]);
                }
            }
            if (!esGrupoValido(bloque)) return false;
        }
    }

    return true;
}

void Sudoku::resolverParcial() {
    bool change = true;
    while (change) {
        change = false;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                change = resolverPos(i, j) || change;
            }
        }
    }
}

void Sudoku::resolverParcialProb() {
    map<pair<int, int>, set<int>> prop;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (Tablero[i][j] == -1) {
                prop.insert({{i, j}, DevolverLosFaltantesPos(i, j)});
            }
        }
    }

    resolverConProp(prop);
    
}

bool Sudoku::resolverConProp(map<pair<int, int>, set<int>>& prop) {
    if (estaResulto()) return true;

    // Buscar la celda vacía con menos opciones
    pair<int, int> mejorPos = {-1, -1};
    size_t menorTam = 10;
    for (const auto& p : prop) {
        if (Tablero[p.first.first][p.first.second] == -1 && p.second.size() < menorTam) {
            menorTam = p.second.size();
            mejorPos = p.first;
        }
    }

    if (mejorPos.first == -1) return false;

    int i = mejorPos.first;
    int j = mejorPos.second;

    set<int> posibles = prop[{i, j}];

    for (int val : posibles) {
        setPos(i, j, val);
        auto respaldo = prop;

        // Actualizar opciones
        for (auto& kv : prop) {
            if (Tablero[kv.first.first][kv.first.second] == -1) {
                kv.second = DevolverLosFaltantesPos(kv.first.first, kv.first.second);
            }
        }

        if (resolverConProp(prop)) return true;

        // Backtrack
        Tablero[i][j] = -1;
        prop = respaldo;
    }

    return false;
}

set<int> invertirConjunto9(set<int> s) {
    set<int> sout;
    for (int i = 1; i <= 9; ++i) {
        if (!s.count(i)) sout.insert(i);
    }

    return sout;
}

bool Sudoku::resolverPos(int i, int j) {
    if (Tablero[i][j] != -1) return false;

    set<int> numUsados;
    obtener3x3(i, j, numUsados);
    obtenerLineas(i, j, numUsados);

    numUsados = invertirConjunto9(numUsados);

    bool change = false;
    if (numUsados.size() == 1) {
        Tablero[i][j] = *numUsados.begin();
        change = true;
    }

    return change;
}

set<int> Sudoku::DevolverLosFaltantesPos(int i, int j) {
    set<int> numUsados;
    obtener3x3(i, j, numUsados);
    obtenerLineas(i, j, numUsados);

    numUsados = invertirConjunto9(numUsados);

    return numUsados;
}

void Sudoku::obtener3x3(int i, int j, set<int> &s) {
    
    i = (i / 3) * 3;
    j = (j / 3) * 3;

    for (int ii = 0; ii < 3; ++ii) {
        for (int jj = 0; jj < 3; ++jj) {
            if (Tablero[ii + i][jj + j] != -1) s.insert(Tablero[ii + i][jj + j]);
        }
    }
}
void Sudoku::obtenerLineas(int i, int j, set<int> &s) {
    for (int x = 0; x < 9; ++x) {
        if (Tablero[x][j] != -1) s.insert(Tablero[x][j]);
        if (Tablero[i][x] != -1) s.insert(Tablero[i][x]);
    }
}


// Seter
void Sudoku::setPos(int i, int j, int val) {
    Tablero[i][j] = val;
}

void Sudoku::leerTablero() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cin >> Tablero[i][j];
        }
    }
}

// Consultores
int Sudoku::getPos(int i, int j) const {
    return Tablero[i][j];
}

vector<vector<int>> Sudoku::getTablero() const {
    return Tablero;
}

void Sudoku::imprimirTablero() const {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (Tablero[i][j] != -1) cout << ' ';
            cout << " " << Tablero[i][j];
        }
        cout << endl;
    }
    cout << endl;
}