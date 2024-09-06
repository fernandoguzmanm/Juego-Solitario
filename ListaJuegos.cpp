#include "ListaJuegos.h"


void cargar(tListaJuegos& lista, std::ifstream& file) {
	tJuego juego;
	int numJuegos;
	inicializar(lista);
	file >> numJuegos;

	for (int i = 0; i < numJuegos; i++) {
		cargar(juego, file);
		insertar(lista, juego);
		//mostrar(lista);
		//lista.contador++;
	}
}


void guardar(const tListaJuegos& lista, std::ofstream& file) {
	tJuego juego;
	file << lista.contador << endl;
	for (int i = 0; i < lista.contador; i++) {
		guardar(lista.juegos[i], file);
	}
}


void insertar(tListaJuegos& lista, const tJuego& juego) {

	if (lista.contador >= lista.capacidad) {
		tJuegoPtr aux = nullptr;
		aux = new tJuego[lista.capacidad + DELTA];

		for (int i = 0; i < lista.contador; i++) {
			aux[i] = lista.juegos[i];
		}
		delete[] lista.juegos;
		lista.juegos = aux;
		lista.capacidad = lista.capacidad + DELTA;
		aux = nullptr;
	}
	lista.juegos[lista.contador] = juego;
	lista.contador++;
}

void inicializar(tListaJuegos& lista) {

	lista.juegos = new tJuego[lista.capacidad];


}

void eliminar(tListaJuegos& lista, int pos) {
	if (pos > lista.contador || pos < 0) {
		cout << "Posicion invalida" << endl;
	}
	for (int i = pos; i < lista.contador; i++) {
		lista.juegos[i] = lista.juegos[i + 1];
	}
	lista.contador--;
}

void mostrar(const tListaJuegos& lista) {

	for (int i = 0; i < lista.contador; i++) {
		cout << "JUEGO " << i + 1 << endl;
		mostrar(lista.juegos[i]);
	}
}

int eligeJuego(tListaJuegos& lista) {
	tJuego nuevoJuego;

	int ret;
	int opcion;
	if (lista.contador == 0) {
		nuevoJuego.estado = JUGANDO;
		insertar(lista, nuevoJuego);
		ret = 0;
	}
	else {
		for (int i = 0; i < lista.contador; i++) {
			cout << i + 1 << ". Juego " << i + 1 << endl;
			mostrar(lista.juegos[i]);
		}

		cout << "0. Generar un nuevo juego" << endl;
		cout << "-1. Salir" << endl;

		cout << "Elige un juego: ";
		cin >> opcion;

		while (opcion < 0 || opcion > lista.contador) {
			cout << "Opcion invalida. Elige una opcion valida: ";
			cin >> opcion;
		}
		if (opcion == 0) {
			cout << "Elige el numero de pasos para el juego aleatorio: ";
			int pasos;
			cin >> pasos;
			generar(nuevoJuego, pasos);
			mostrar(nuevoJuego);
			insertar(lista, nuevoJuego);
			opcion = lista.contador;
		}

		ret = opcion - 1;


	}
	return ret;
}
void liberar(tListaJuegos& lista) {
	delete[] lista.juegos;
	lista.juegos = nullptr;
}

tJuego dameJuego(const tListaJuegos& lista, int pos) {
	tJuego ret;
	ret = lista.juegos[pos];
	return ret;
}

void ponJuego(tListaJuegos& lista, int pos, tJuego juego) {
	lista.juegos[pos] = juego;
}