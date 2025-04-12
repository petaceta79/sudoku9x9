#ifndef SUDOKU_HH
#define SUDOKU_HH

#include <vector>
#include <set>
#include <map>

using namespace std;

/**
 * @class Sudoku
 * @brief Clase que representa un tablero de Sudoku y sus métodos de resolución.
 */
class Sudoku {
public:
    /**
     * @brief Constructor por defecto. Inicializa un tablero vacío.
     */
    Sudoku();

    /**
     * @brief Constructor que inicializa el tablero con una matriz dada.
     * @param tablero Matriz de enteros representando el tablero inicial de Sudoku.
     */
    Sudoku(vector<vector<int>> &tablero);

    /**
     * @brief Resuelve el Sudoku.
     * @pre Debe ser un tablero valido
     */
    void resolver();

    /**
     * @brief Intenta resolver la posición (i, j) del tablero.
     * @param i Fila de la celda.
     * @param j Columna de la celda.
     * @return true si fue posible resolver la celda, false en caso contrario.
     */
    bool resolverPos(int i, int j);

    /**
     * @brief Devuelve los valores faltantes posibles en la posición (i, j).
     * @param i Fila de la celda.
     * @param j Columna de la celda.
     * @return Conjunto de enteros con los valores faltantes.
     */
    set<int> DevolverLosFaltantesPos(int i, int j);

    /**
     * @brief Verifica si el Sudoku está completamente resuelto.
     * @return true si todas las celdas están completas y correctas, false en caso contrario.
     */
    bool estaResulto();

    /**
     * @brief Asigna un valor a una celda del tablero.
     * @param i Fila de la celda.
     * @param j Columna de la celda.
     * @param val Valor a asignar.
     */
    void setPos(int i, int j, int val);

    /**
     * @brief Lee el tablero desde la entrada estándar.
     */
    void leerTablero();

    /**
     * @brief Obtiene el valor de una celda del tablero.
     * @param i Fila de la celda.
     * @param j Columna de la celda.
     * @return Valor entero de la celda.
     */
    int getPos(int i, int j) const;

    /**
     * @brief Obtiene una matriz del tablero 9x9
     */
    vector<vector<int>> getTablero() const;

    /**
     * @brief Imprime el tablero actual por la salida estándar.
     */
    void imprimirTablero() const;

private:
    /**
     * @brief Estructura del tablero de Sudoku (9x9).
     */
    vector<vector<int>> Tablero;

    /**
     * @brief Resuelve el Sudoku utilizando un mapa de posibles valores por celda.
     * @param prop Mapa con posibles valores por celda.
     * @return true si se resuelve correctamente, false en caso contrario.
     */
    bool resolverConProp(map<pair<int, int>, set<int>>& prop);

    /**
     * @brief Realiza una resolución parcial, con las soluciones "obvias".
     */
    void resolverParcial();

    /**
     * @brief Realiza una resolución parcial usando Backtracking.
     */
    void resolverParcialProb();

    /**
     * @brief Obtiene los valores presentes en la subcuadrícula 3x3 correspondiente a (i, j).
     * @param i Fila de la celda.
     * @param j Columna de la celda.
     * @param s Conjunto donde se insertan los valores encontrados.
     */
    void obtener3x3(int i, int j, set<int> &s);

    /**
     * @brief Obtiene los valores presentes en la fila y columna de la celda (i, j).
     * @param i Fila de la celda.
     * @param j Columna de la celda.
     * @param s Conjunto donde se insertan los valores encontrados.
     */
    void obtenerLineas(int i, int j, set<int> &s);      
};

#endif
