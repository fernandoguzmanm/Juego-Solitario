#ifndef JUEGO_H
#define JUEGO_H


#include <string>
#include <fstream>
#include "tablero.h"
#include "movimiento.h"

using namespace std;

typedef enum tEstado { JUGANDO, GANADOR, BLOQUEO };
struct tJuego {
	tTablero tablero;
	tEstado estado;
};

typedef struct tJuego* tJuegoPtr;

void cargar(tJuego& juego, std::ifstream& fichero);
void mostrar(const tJuego& juego);
void ejecutarMovimiento(tJuego& juego);
void actualizaEstado(tJuego& juego);
bool ganador(const tJuego& juego);
bool hayMovimientos(const tJuego& juego);
void generar(tJuego& juego, int pasos);
bool movimientoInverso(tJuego& juego);
void guardar(const tJuego& juego, std::ofstream& fichero);
void jugar(tJuego& juego);
#endif