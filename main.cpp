#include "Usuarios.h"

#include <iostream>
#include <string>
using namespace std;

int main() {


    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    tJuego juego;
    string id;
    tListaUsuarios listaU;
    tListaJuegos listaJ;
    int posBuscar;




    cargar(listaU);
  
    do {
        cout << "Introduce el Id de Usuario (FIN para salir): ";
        cin >> id;
        posBuscar = buscar(listaU, id);
        if (posBuscar == -1) {
            int pasos;
            posBuscar = listaU.contador;
            inicializar(listaJ);

            nuevoUsuario(listaU, id);
            int posJ = listaJ.contador;
            listaU.usuarios[posBuscar]->lista = listaJ;



            cout << "No existe el usuario, se generaran tableros aleatoriamente, introduce el numero de pasos: ";
            cin >> pasos;

            int pos2 = buscar(listaU, id);
            generar(juego, pasos);
            insertar(listaU.usuarios[pos2]->lista, juego);
            

            mostrar(juego);
            jugar(juego);

            guardar(listaU);


        }
        else {
            int pos = buscar(listaU, id);
            cout << "El Usuario " << id << " ha sido encontrado" << endl;

           

            cout << "Juegos sin terminar del Usuario: " << listaU.usuarios[pos]->id << endl;


            int pos1 = 0;
            pos1 = eligeJuego(listaU.usuarios[pos]->lista);
            
            cout << endl;

            jugar(listaU.usuarios[pos]->lista.juegos[pos1]);
            if (!hayMovimientos(listaU.usuarios[pos]->lista.juegos[pos1])) {
                eliminarJuegoUsuario(listaU, pos, pos1);
            }
            if (listaU.usuarios[pos]->lista.contador == 0) {
                eliminar(listaU, pos);
            }
            guardar(listaU);
        }
        

        
    } while (id != "FIN");

    liberar(listaJ);
    liberar(listaU);

    return 0;
}

/*

int main() {

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    tJuego juego;
    string id;
    tListaUsuarios listaU;
    tListaJuegos listaJ;
    cargar(listaU);
    cout << "Id de Usuario (FIN para salir): ";
    cin >> id;

    if (buscar(listaU, id) == -1) {
        int pasos;
        cout << "No existe el usuario, se generaran tableros aleatoriamente, introduce el numero de pasos: ";
        cin >> pasos;
        generar(juego, pasos);
        mostrar(juego);
    }
    else {
        int pos = buscar(listaU, id);
        cout << "El usuario existe." << endl;
        cout << "El valor del contador de listaU es" << listaU.contador << endl;
        cout << "El valor del contador de ListaJ es" << listaJ.contador << endl;
        cout << endl;

        cout << "JUEGOS sin terminar del Usuario: " << listaU.usuarios[pos]->id << endl;

        int pos1 = 0;
        pos1 = eligeJuego(listaU.usuarios[pos]->lista);
        cout << endl;
        mostrar(listaU.usuarios[pos]->lista.juegos[pos1]);
        cout << endl;

    }

    return 0;
}
*/