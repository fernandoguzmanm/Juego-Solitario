#pragma once
#ifndef USUARIOS_H
#define USUARIOS_H

#include "ListaJuegos.h"



const int MAX = 5;
struct tUsuario {
	std::string id;
	tListaJuegos lista;
};
typedef tUsuario* tUsuarioPtr;
typedef tUsuarioPtr tArray[MAX];
struct tListaUsuarios { // ordenada crecientemente por id
	const std::string nombreFichero = "juegos.txt";
	tArray usuarios;
	int contador;
};


//Prototipo de funciones
void cargar(tListaUsuarios& lista);
void guardar(const tListaUsuarios& lista);
int buscar(const tListaUsuarios& lista, std::string id);
int nuevoUsuario(tListaUsuarios& lista, std::string id);
void eliminar(tListaUsuarios& lista, int pos);
void liberar(tListaUsuarios& lista);
int eligeJuegoUsuario(const tListaUsuarios& lista, int indUsuario);
tJuego dameJuegoUsuario(const tListaUsuarios& lista, int posUsuario, int posJuego);
void actualizaJuegoUsuario(tListaUsuarios& lista, int posUsuario, int posJuego, tJuego juego);
void eliminarJuegoUsuario(tListaUsuarios& lista, int posUsuario, int posJuego);
void inicializarListaUsuarios(tListaUsuarios& listaUsuarios);




#endif 
#pragma once