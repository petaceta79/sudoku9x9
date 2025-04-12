# Sudoku Solver

Este repositorio contiene una implementación en C++ de un solucionador de Sudoku que utiliza una combinación de técnicas de resolución lógica y backtracking para encontrar la solución.

## Clase Sudoku

La clase `Sudoku` representa un tablero de Sudoku 9x9 y proporciona métodos para su resolución.

### Características principales:
- Implementa dos estrategias de resolución: lógica directa y backtracking inteligente
- Verifica la validez del tablero
- Permite cargar tableros manualmente o mediante entrada estándar
- Proporciona métodos para acceder y modificar el tablero

### Métodos públicos principales:

| Método | Descripción |
|--------|-------------|
| `resolver()` | Resuelve el Sudoku completo |
| `resolverPos(i, j)` | Intenta resolver una celda específica |
| `DevolverLosFaltantesPos(i, j)` | Devuelve valores posibles para una celda |
| `estaResulto()` | Verifica si el Sudoku está resuelto |
| `setPos(i, j, val)` | Asigna un valor a una celda |
| `getPos(i, j)` | Obtiene el valor de una celda |
| `imprimirTablero()` | Muestra el tablero actual |

### Métodos privados:
- `resolverConProp()`: Backtracking con mapa de posibles valores
- `resolverParcial()`: Resolución lógica directa
- `resolverParcialProb()`: Prepara datos para backtracking
- `obtener3x3()`: Obtiene valores en subcuadrícula 3x3
- `obtenerLineas()`: Obtiene valores en fila y columna

## Uso básico

```cpp
#include "sudoku.hh"

int main() {
    Sudoku sudoku;
    
    // Cargar tablero (ejemplo con entrada estándar)
    sudoku.leerTablero();
    
    // Resolver el Sudoku
    sudoku.resolver();
    
    // Mostrar resultado
    sudoku.imprimirTablero();
    
    return 0;
}

## 📋 Requisitos
- Compilador C++ compatible con C++11 o superior

## 🔧 Compilación
```bash
g++ -std=c++11 main.cpp sudoku.cpp -o sudoku_solver

Con un make ya configurado

## 🧠 Estrategia de Resolución

El solucionador implementa un enfoque híbrido inteligente:

1. **Fase de Lógica Directa**:
   - Resuelve primero las celdas con solución única evidente
   - Analiza filas, columnas y bloques 3x3 para encontrar valores obligatorios
   - Itera hasta que no pueda encontrar más soluciones directas

2. **Fase de Backtracking Inteligente**:
   - Selecciona siempre la celda con menos posibilidades
   - Utiliza propagación
   - Implementa retroceso (backtracking) cuando detecta contradicciones
   - Mantiene un mapa de posibles valores por celda para optimizar el proceso

## 📝 Notas Importantes

- **Representación**:
  - Celdas vacías se marcan con `-1`
  - El tablero completo es una matriz 9x9 de valores enteros

- **Validación**:
  - Verifica la solución completa antes de aceptarla
  - Comprueba que no haya repeticiones en filas, columnas o bloques 3x3

- **Optimizaciones**:
  - Evita búsquedas redundantes mediante memoización
  - Ordena las celdas por dificultad para resolver primero las más restrictivas

