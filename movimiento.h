#ifndef Movimiento_h
#define Movimiento_h

#include <iostream>
#include <iomanip>
#include <fstream>
#include "juego.h"


using namespace std;
const int MAX_M = 4;
//Declaracion de Datos

typedef enum tDireccion { ARRIBA, DERECHA, ABAJO, IZQUIERDA };

typedef struct {
	tDireccion direccion;
	int filaSalto;
	int colSalto;
	int filaDestino;
	int colDestino;
}tMovimiento;

typedef tMovimiento tMovimientoArray[MAX_M];
typedef struct tMovimientoLista {
	tMovimientoArray arrayMovimiento;
	int cont = 0;
};




bool fichaBloqueada(const tTablero& tablero, int fila, int col);
tMovimiento moviendo(tDireccion dir, int fila, int col);
tMovimiento leeMovimiento(const tTablero& tablero, int& fila, int& col);
bool movimientosPosibles(const tTablero& tablero, int fila, int col, tMovimientoLista& listaMov);
tMovimiento eligeMovimiento(const tMovimientoLista& listaMov);
void movimientoFicha(tTablero& tablero, int fila, int col, const tMovimiento& mov);
bool eligeMovimientoInverso(const tTablero& tablero, int fila, int col, tMovimiento& mov);
void realizaMovimientoInverso(tTablero& tablero, int fila, int col, const tMovimiento& mov);

#endif