#ifndef tablero_h
#define tablero_h



#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int MAX_FILA = 50;
const int MAX_COLUMNA = 50;


typedef enum tCelda { NULA, VACIA, FICHA };

typedef tCelda tCeldaArray[MAX_FILA][MAX_COLUMNA];

struct tTablero {
	tCeldaArray celdaArray;
	int num_filas, num_columnas, columna_meta, fila_meta;
};

void cargar(tTablero& tablero, std::ifstream& file);
bool valida(const tTablero& tablero, int fila, int col);
bool eleccionValida(const tTablero& tablero, int fila, int col);
bool esFicha(const tTablero& tablero, int fila, int col);
bool esVacia(const tTablero& tablero, int fila, int col);
void ponCelda(tTablero& tablero, int fila, int col, tCelda celda);
int numFilas(const tTablero& tablero);
int numColumnas(const tTablero& tablero);
void dameMeta(const tTablero& tablero, int& fila, int& col);
void ponMeta(tTablero& tablero, int fila, int col);
void mostrar(const tTablero& tablero);
void fichaAleatoria(const tTablero& tablero, int& fila, int& columna);
void reseteaTablero(tTablero& tablero, int f, int c);
void guardar(const tTablero& tablero, std::ofstream& file);
void pintaCabecera(int col);
void pintaBordeHorizontal(char left, char cross, int col, char right);
void pintaBordeCelda(const tCeldaArray& matriz, int fila, int coltotal, int filaMeta, int colMeta);
void pintaCentroCelda(const tCeldaArray& matriz, int fila, int coltotal, int filaMeta, int colMeta);

#endif

