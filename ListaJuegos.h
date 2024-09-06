#ifndef ListaJuegos_h
#define ListaJuegos_h

#include "juego.h"


const int DELTA = 5;
struct tListaJuegos {
	tJuegoPtr juegos = nullptr;
	int contador = 0, capacidad = 5;
};

void cargar(tListaJuegos& lista, std::ifstream& file);
void insertar(tListaJuegos& lista, const tJuego& juego);
void eliminar(tListaJuegos& lista, int pos);
void mostrar(const tListaJuegos& lista);
int eligeJuego(tListaJuegos& lista);
void liberar(tListaJuegos& lista);
tJuego dameJuego(const tListaJuegos& lista, int pos);
void ponJuego(tListaJuegos& lista, int pos, tJuego juego);
void inicializar(tListaJuegos& lista);
void guardar(const tListaJuegos& lista, std::ofstream& file);
#endif // !ListaJuegos_h
