#include "tablero.h" 
#include "movimiento.h"


// Subprograma para generar un presunto movimiento en una dirección específica
tMovimiento moviendo(tDireccion dir, int fila, int col) {
    tMovimiento mov;
    mov.direccion = dir;
    // mov.filaSalto = fila;
    // mov.colSalto = col;

    switch (dir) {
    case ARRIBA:

        //Al moverse hacia arriba, solo cambia la fila de valor
        mov.filaDestino = fila - 2;
        mov.filaSalto = fila - 1;
        mov.colDestino = col;
        mov.colSalto = col;
        break;

    case ABAJO:

        //Al moverse hacia abajo, solo cambia la fila de valor
        mov.filaDestino = fila + 2;
        mov.filaSalto = fila + 1;
        mov.colDestino = col;
        mov.colSalto = col;
        break;

    case IZQUIERDA:

        //Al moverse hacia la izquierda, solo cambia la columna de valor
        mov.filaDestino = fila;
        mov.filaSalto = fila;
        mov.colDestino = col - 2;
        mov.colSalto = col - 1;
        break;

    case DERECHA:

        //Al moverse hacia la derecha, solo cambia la columna de valor
        mov.filaDestino = fila;
        mov.filaSalto = fila;
        mov.colDestino = col + 2;
        mov.colSalto = col + 1;

        break;

    }

    return mov;

}

// Función para verificar si una ficha está bloqueada en la posición indicada
bool fichaBloqueada(const tTablero& tablero, int fila, int col) {
    bool ret = false;
    tMovimientoLista listaMov;
    if (!movimientosPosibles(tablero, fila, col, listaMov)) {
        ret = true;
    }
    return ret;
}

// Función para verificar si hay movimientos posibles para una ficha en una posición dada

bool movimientosPosibles(const tTablero& tablero, int fila, int col, tMovimientoLista& listaMov) {
    listaMov.cont = 0; // Inicializar el contador de movimientos en la lista a cero


    for (tDireccion dir = ARRIBA; dir <= IZQUIERDA; dir = tDireccion(dir + 1)) {
        tMovimiento mov = moviendo(dir, fila, col);




        if (valida(tablero, mov.filaSalto, mov.colSalto) && esFicha(tablero, mov.filaSalto, mov.colSalto) && valida(tablero, mov.filaDestino, mov.colDestino) && esVacia(tablero, mov.filaDestino, mov.colDestino)) {
            if (listaMov.cont < MAX_M) {
                listaMov.arrayMovimiento[listaMov.cont] = mov;
                listaMov.cont++;

            }
        }


    }

    return (listaMov.cont > 0); // Devolver true si se encontraron movimientos posibles
}


tMovimiento eligeMovimiento(const tMovimientoLista& listaMov) {
    tJuego juego;
    tDireccion dir;
    //Si solo hay mas de 1 movimiento posible


        // Mostrar las direcciones de los movimientos en la lista
    cout << "Movimientos posibles:" << endl;
    for (int i = 0; i < listaMov.cont; ++i) {
        cout << i + 1 << ". ";
        switch (listaMov.arrayMovimiento[i].direccion) {
        case ARRIBA:
            cout << "Arriba" << endl;
            break;
        case ABAJO:
            cout << "Abajo" << endl;
            break;
        case IZQUIERDA:
            cout << "Izquierda" << endl;
            break;
        case DERECHA:
            cout << "Derecha" << endl;
            break;
        }

    }

    int opcion;
    cout << "Elige un movimiento (1-" << listaMov.cont << "): ";
    cin >> opcion;

    // Validar la opción ingresada por el usuario
    while (opcion < 1 || opcion > listaMov.cont) {
        cout << "Opción inválida. Elige un movimiento válido: ";
        cin >> opcion;
    }

    // Devolver el movimiento seleccionado por el usuario
    return listaMov.arrayMovimiento[opcion - 1];
}


/*
tMovimiento leeMovimiento(const tTablero& tablero, int& fila, int& col) {
    tMovimientoLista listaMov;
    tMovimiento dir{ ABAJO, -1, -1, -1, -1 };
    
    do {
        cout << "Seleccione una celda (fila y columna): " << endl;
        cout << "Fila: ";
        cin >> fila;
        cout << "Columna: ";
        cin >> col;

        if (fila == 0 && col == 0) {
           
 
           return dir; // Salir de la función inmediatamente
      
        }

        if (!valida(tablero, fila, col)) {
            cout << "Elige una celda válida" << endl;
        }
        else {
            fila--; // Ajustamos a índices de matriz
            col--;

            if (!movimientosPosibles(tablero, fila, col, listaMov)) {
                cout << "No hay movimientos posibles en esa celda, seleccione otra " << endl;
            }
        }

    } while ((!valida(tablero, fila, col) || !movimientosPosibles(tablero, fila, col, listaMov)));

    if (listaMov.cont == 1) {
        dir = listaMov.arrayMovimiento[listaMov.cont - 1];
    }
    else {
        dir = eligeMovimiento(listaMov);
    }
    
    return dir;
}
*/



tMovimiento leeMovimiento(const tTablero& tablero, int& fila, int& col) {
    tMovimientoLista listaMov;
    tMovimiento dir{ ABAJO, -1, -1, -1, -1 };
    bool entradaOk = false;

    while (!entradaOk) {
        cout << "Seleccione una celda (fila y col) [0 0 para guardar]: " << endl;
        cout << "Fila: ";
       cin >> fila;
        cout << "Col: ";
     cin >> col;

        fila--;
        col--;

        if (fila != -1 && col != -1) {
            col++;
            fila++;

            if (valida(tablero, fila, col)) {
                fila--;
                col--;

                if (movimientosPosibles(tablero, fila, col, listaMov)) {
                    entradaOk = true;

                    if (listaMov.cont == 1) {
                        dir = listaMov.arrayMovimiento[listaMov.cont - 1];
                    } else {
                        dir = eligeMovimiento(listaMov);
                    }
                } else {
                    cout << "No hay movimientos posibles en esa celda, seleccione otra. " << endl;
                }
            } else {
                cout << "Elige una celda valida" << endl;
            }
        }
        else {
            entradaOk = true;
        }
    }
    return dir;
}




void movimientoFicha(tTablero& tablero, int fila, int col, const tMovimiento& mov) {
    tablero.celdaArray[fila][col] = VACIA;
    tablero.celdaArray[mov.filaSalto][mov.colSalto] = VACIA;
    tablero.celdaArray[mov.filaDestino][mov.colDestino] = FICHA;
}

bool eligeMovimientoInverso(const tTablero& tablero, int fila, int col, tMovimiento& mov) {

    bool hayMovInv = false;

    tMovimientoLista movInvPos;
    movInvPos.cont = 0;


    for (tDireccion dir = ARRIBA; dir <= IZQUIERDA; dir = tDireccion(dir + 1)) {
        tMovimiento movimiento = moviendo(dir, fila, col);
        //cambiar
        if (eleccionValida(tablero, fila, col) && valida(tablero, movimiento.filaDestino, movimiento.colDestino)) {
            if (tablero.celdaArray[movimiento.filaDestino][movimiento.colDestino] != FICHA && tablero.celdaArray[movimiento.filaSalto][movimiento.colSalto] != FICHA) {
                movInvPos.arrayMovimiento[movInvPos.cont] = movimiento;
                movInvPos.cont++;
                hayMovInv = true;
            }
        }
    }

    if (movInvPos.cont > 0) {
        srand(time(NULL));
        mov = movInvPos.arrayMovimiento[rand() % movInvPos.cont];
        hayMovInv = true;
    }
    else if (movInvPos.cont == 1) {
        //mov = movInvPos.arrayMovimiento[0];
        hayMovInv = true;
    }

    return hayMovInv;
}

void realizaMovimientoInverso(tTablero& tablero, int fila, int col, const tMovimiento& mov) {
    tablero.celdaArray[fila][col] = VACIA;
    tablero.celdaArray[mov.filaSalto][mov.colSalto] = FICHA;
    tablero.celdaArray[mov.filaDestino][mov.colDestino] = FICHA;
}
