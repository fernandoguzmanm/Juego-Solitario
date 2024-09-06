#include "juego.h"
#include "tablero.h"
#include "movimiento.h"




void cargar(tJuego& juego, std::ifstream& fichero) {


    juego.estado = JUGANDO;
    cargar(juego.tablero, fichero);


}
void mostrar(const tJuego& juego) {
    mostrar(juego.tablero);

}

void ejecutarMovimiento(tJuego& juego) {
    int fila, col; // Variables para la fila y columna del movimiento
    tTablero tablero = juego.tablero; // Copia del tablero del juego
    bool ok = false;
    tMovimiento mov = leeMovimiento(tablero, fila, col);
    
        movimientoFicha(juego.tablero, fila, col, mov);
        actualizaEstado(juego);
    
    }
  


void actualizaEstado(tJuego& juego) {
    if (ganador(juego)) {
        juego.estado = GANADOR;
    }

    else if (!hayMovimientos(juego)) {
        juego.estado = BLOQUEO;
        cout << "BLOQUEO";
    }
    else {
        juego.estado = JUGANDO;
    }
}

bool ganador(const tJuego& juego) {
    bool ganador = false;
    int contadorFichas = 0;


    for (int i = 0; i < juego.tablero.num_filas; ++i) {
        for (int j = 0; j < juego.tablero.num_columnas; ++j) {
            // Si la celda contiene una ficha, incrementar el contador
            if (juego.tablero.celdaArray[i][j] == FICHA) {
                contadorFichas++;

            }
        }
    }

    // Comprobar si solo queda una ficha en el tablero y hay una ficha en la casilla de meta
    if (contadorFichas == 1 && juego.tablero.celdaArray[juego.tablero.fila_meta][juego.tablero.columna_meta] == FICHA) {
        ganador = true;
    }

    return ganador;
}

bool hayMovimientos(const tJuego& juego) {
    bool ret = false;
    int fila = 0;
    int col = 0;

    while (fila < juego.tablero.num_filas && !ret) {
        while (col < juego.tablero.num_columnas && !ret) {
            if (esFicha(juego.tablero, fila, col) && !fichaBloqueada(juego.tablero, fila, col)) {
                ret = true;
            }
            col++;
        }
        fila++;
        col = 0;
    }

    return ret;
}

void generar(tJuego& juego, int pasos) {
    juego.estado = JUGANDO;
    tTablero meta;
    int min = 4;
    srand(time(NULL));


    reseteaTablero(juego.tablero, rand() % 6 + 5, rand() % 6 + 5);
    //reseteaTablero(juego.tablero,min+ rand() % (MAX-min+1), min + rand() % (MAX - min + 1));
    juego.tablero.fila_meta = rand() % juego.tablero.num_filas;
    juego.tablero.columna_meta = rand() % juego.tablero.num_columnas;

    ponMeta(juego.tablero, juego.tablero.fila_meta, juego.tablero.columna_meta);
    juego.tablero.celdaArray[juego.tablero.fila_meta][juego.tablero.columna_meta] = FICHA;



    while (pasos > 0 && movimientoInverso(juego)) {
        pasos--;

    }
}


bool movimientoInverso(tJuego& juego) {
    bool ok = false;

    int f, c;
    //aqui devuelve una fila y columna aleatoria
    fichaAleatoria(juego.tablero, f, c);

    tMovimiento mov;
    if (eligeMovimientoInverso(juego.tablero, f, c, mov)) {

        realizaMovimientoInverso(juego.tablero, f, c, mov);

        ok = true;
    }

    return ok;
}





void guardar(const tJuego& juego, std::ofstream& fichero) {
    guardar(juego.tablero, fichero);
}



void jugar(tJuego& juego) {
    bool continuar = true;
    int fila, col;
    tMovimiento move;

    do {
        
            move = leeMovimiento(juego.tablero, fila, col);
            if (fila != -1) {
                movimientoFicha(juego.tablero, fila, col, move);
                mostrar(juego);
                actualizaEstado(juego);
            }
        

        if (juego.estado == GANADOR) {
            cout << "HAS GANADO!!!" << endl;
        }
        else if (juego.estado == BLOQUEO) {
            cout << "NO QUEDAN CELDAS POR MOVER, HAS PERDIDO!!!" << endl;
        }

    } while (fila != -1 && juego.estado == JUGANDO);
    
}
    
    
    
    
    
    /*
    while (continuar) {

        while (juego.estado == JUGANDO) {
            
            ejecutarMovimiento(juego);
      
            
            mostrar(juego);

            actualizaEstado(juego);
        }

        if (juego.estado == GANADOR) {
            cout << " HAS GANADO!!! " << endl;
            char opcion;

            cout << " Quieres jugar de nuevo[S][N]? ";
            cin >> opcion;

            continuar = (opcion == 'S' || opcion == 's');
        }

        else if (juego.estado == BLOQUEO) {
            cout << " NO QUEDAN CELDAS POR MOVER, HAS PERDIDO!!! " << endl;
            char opcion;

            cout << " Quieres jugar de nuevo?[S][N] ";
            cin >> opcion;

            continuar = (opcion == 'S' || opcion == 's');
        }

    }*/
