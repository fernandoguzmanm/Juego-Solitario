#include "usuarios.h"
#include <string>



void cargar(tListaUsuarios& lista) {
	int numUsuarios;
	string nombre, id;
	tJuego juego;

	//nombre = lista.nombreFichero;
	ifstream archivo(lista.nombreFichero);
	tListaJuegos listaJ;
	if (archivo.is_open()) {
		inicializarListaUsuarios(lista);


		archivo >> numUsuarios;
		for (int i = 0; i < numUsuarios; i++) {
			archivo >> id;
			nuevoUsuario(lista, id);
			cargar(lista.usuarios[i]->lista, archivo);



		}
		archivo.close();
	}
	else {
		cout << " No se pudo encontrar el archivo." << endl;
	}


}

void inicializarListaUsuarios(tListaUsuarios& listaUsuarios) {
	listaUsuarios.contador = 0;

	for (int i = 0; i < MAX; ++i) {
		listaUsuarios.usuarios[i] = nullptr;
	}
}

void guardar(const tListaUsuarios& lista) {
	tListaJuegos listaJ;
	std::ofstream archivo(lista.nombreFichero);
	archivo << lista.contador << std::endl;
	for (int i = 0; i < lista.contador; i++) {
		archivo << lista.usuarios[i]->id << endl;
		guardar(lista.usuarios[i]->lista, archivo);
	}
	archivo.close();
}

int buscar(const tListaUsuarios& lista, std::string id) {
	int ini = 0, fin = lista.contador - 1, mitad;
	int pos;
	bool encontrado = false;

	while (ini <= fin and !encontrado) {
		mitad = (ini + fin) / 2;
		if (id == lista.usuarios[mitad]->id) {
			encontrado = true;
		}
		else if (id < lista.usuarios[mitad]->id) {
			fin = mitad - 1;
		}
		else {
			ini = mitad + 1;
		}
	}
	if (encontrado) {
		pos = mitad;
	}
	else {
		pos = -1;
	}
	return pos;

}

int nuevoUsuario(tListaUsuarios& lista, std::string id) {
	int pos = buscar(lista, id);

	if (pos == -1 && lista.contador < MAX) {
		pos = lista.contador;
		for (int i = lista.contador; i > 0; i--) {
			lista.usuarios[i + 1] = lista.usuarios[i];
		}
		lista.usuarios[pos] = new tUsuario;
		lista.usuarios[pos]->id = id;
		lista.contador++;

	}


	return pos;
}

void eliminar(tListaUsuarios& lista, int pos) {
	delete lista.usuarios[pos];
	for (int i = pos; i < lista.contador - 1; i++) {
		lista.usuarios[i] = lista.usuarios[i + 1];
	}
	lista.contador--;
}

void liberar(tListaUsuarios& lista) {
	for (int i = 0; i < MAX; i++) {
		delete lista.usuarios[i];
	}
	delete[] lista.usuarios;
	lista.contador = 0;
}




int eligeJuegoUsuario(const tListaUsuarios& lista, int indUsuario) {
	int ind;

	ind = eligeJuego(lista.usuarios[indUsuario]->lista);
	return ind;

}


tJuego dameJuegoUsuario(const tListaUsuarios& lista, int posUsuario, int posJuego) {
	return lista.usuarios[posUsuario]->lista.juegos[posJuego];
}


void actualizaJuegoUsuario(tListaUsuarios& lista, int posUsuario, int posJuego, tJuego juego) {
	lista.usuarios[posUsuario]->lista.juegos[posJuego] = juego;
}

void eliminarJuegoUsuario(tListaUsuarios& lista, int posUsuario, int posJuego) {
	for (int i = posJuego; i < lista.usuarios[posUsuario]->lista.contador - 1; i++) {
		lista.usuarios[posUsuario]->lista.juegos[i] = lista.usuarios[posUsuario]->lista.juegos[i + 1];
	}
	lista.usuarios[posUsuario]->lista.contador--;
}