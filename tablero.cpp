#include "tablero.h"

const int FILS = 4;
const int COLS = 5;
const int f_meta = 2, c_meta = 1;
const int DEFAULT_COLOR = -1;

typedef int tmatriz[FILS][COLS];

tmatriz m = {
    { 0, 0, 1, 2, 2 },
    { 2, 1, 2, 2, 0 },
    { 0, 1, 1, 2, 0 },
    { 0, 0, 0, 0, 0 }
};



const string FG_BLACK = "\x1B[30m";
const string FG_BLUE = "\x1b[34m";
const string BG_BLACK = "\x1B[40m";
const string BG_BROWN = "\x1B[48;5;94m";
const string BG_ORANGE = "\x1B[48;2;204;102;0m";
const string Reset = "\x1b[0m";

const char Horizontal = char(196);
const char UpperLeft = char(218);
const char UpperCross = char(194);
const char UpperRight = char(191);
const char Vertical = char(179);
const char MidLeft = char(195);
const char MidCross = char(197);

const char MidRight = char(180);
const char LowerLeft = char(192);
const char LowerCross = char(193);
const char LowerRight = char(217);
const char Square = char(219);





/*
void cargar(tTablero& tablero, std::ifstream& file) {
    int valor;
    file >> tablero.num_filas >> tablero.num_columnas;
    for (int i = 0; i < tablero.num_filas; i++) {
        for (int j = 0; j < tablero.num_columnas; j++) {
            file >> valor;
            valor = tablero.celdaArray[i][j];
        }
    }
    mostrar(tablero);
    file >> tablero.fila_meta >> tablero.columna_meta;
}
*/
void cargar(tTablero& tablero, std::ifstream& file) {
    int valor;
    file >> tablero.num_filas >> tablero.num_columnas;
    for (int i = 0; i < tablero.num_filas; i++) {
        for (int j = 0; j < tablero.num_columnas; j++) {
            file >> valor;
            tablero.celdaArray[i][j] = tCelda(valor);
        }
    }
    file >> tablero.fila_meta >> tablero.columna_meta;
}

bool valida(const tTablero& tablero, int fila, int col) {
    bool ret;
    if (col <= tablero.num_columnas && fila <= tablero.num_filas && col >= 0 && fila >= 0) {
        ret = true;
    }
    else {
        ret = false;
    }
    return ret;
}

bool eleccionValida(const tTablero& tablero, int fila, int col) {
    bool ret;
    if (valida(tablero, fila, col) && esFicha(tablero, fila, col)) {
        ret = true;
    }
    else {
        ret = false;
    }
    return ret;
}

bool esFicha(const tTablero& tablero, int fila, int col) {
    bool ret = false;
    //-1 por que el array empieza contando desde cero.

    if (tablero.celdaArray[fila][col] != 0 && tablero.celdaArray[fila][col] != 1) {
        ret = true;
    }
    else {
        ret = false;
    }
    return ret;
}

bool esVacia(const tTablero& tablero, int fila, int col) {
    bool ret;
    if (tablero.celdaArray[fila][col] == 1) {
        ret = true;
    }
    else {
        ret = false;
    }
    return ret;
}

void ponCelda(tTablero& tablero, int fila, int col, tCelda celda) {
    tablero.celdaArray[fila][col] = celda;
}

int numFilas(const tTablero& tablero) {
    return tablero.num_filas;
}

int numColumnas(const tTablero& tablero) {
    return tablero.num_columnas;
}

void dameMeta(const tTablero& tablero, int& fila, int& col) {
    fila = tablero.fila_meta;
    col = tablero.columna_meta;
}

void ponMeta(tTablero& tablero, int fila, int col) {
    fila = tablero.fila_meta;
    col = tablero.columna_meta;
}

void mostrar(const tTablero& tablero) {
    //system("cls"); 
    cout << Reset;
    pintaCabecera(tablero.num_columnas);
    pintaBordeHorizontal(UpperLeft, UpperCross, tablero.num_columnas, UpperRight);
    for (int fila = 0; fila < tablero.num_filas; fila++) {
        pintaBordeCelda(tablero.celdaArray, fila, tablero.num_columnas, tablero.fila_meta, tablero.columna_meta);
        pintaCentroCelda(tablero.celdaArray, fila, tablero.num_columnas, tablero.fila_meta, tablero.columna_meta);
        pintaBordeCelda(tablero.celdaArray, fila, tablero.num_columnas, tablero.fila_meta, tablero.columna_meta);
        if (fila < tablero.num_filas - 1) {
            pintaBordeHorizontal(MidLeft, MidCross, tablero.num_columnas, MidRight);
        }
        else {
            pintaBordeHorizontal(LowerLeft, LowerCross, tablero.num_columnas, LowerRight);
        }
    }
}


void pintaCabecera(int col) {
    cout << setw(2) << "    ";
    cout << setw(5) << 1;
    for (int i = 2; i <= col; i++)
        cout << setw(7) << i;
    cout << endl;
}

void pintaBordeHorizontal(char left, char cross, int col, char right) {
    cout << "    ";
    cout << left;
    for (int i = 0; i < col - 1; i++) {
        cout << string(6, Horizontal) << cross;
    }
    cout << string(6, Horizontal) << right << endl;
}

void pintaBordeCelda(const tCeldaArray& matriz, int fila, int coltotal, int filaMeta, int colMeta) {
    cout << "    ";
    for (int k = 0; k < coltotal; k++) {
        cout << Vertical;
        if (filaMeta == fila && colMeta == k)
            cout << BG_ORANGE;
        else if (matriz[fila][k] == NULA)
            cout << BG_BLACK;
        else
            cout << BG_BROWN;
        cout << "      ";
        cout << Reset;
    }
    cout << Vertical << endl;
}

void pintaCentroCelda(const tCeldaArray& matriz, int fila, int coltotal, int filaMeta, int colMeta) {
    cout << "  " << setw(2) << fila + 1;
    for (int k = 0; k < coltotal; k++) { // cada col
        cout << Vertical;
        if (matriz[fila][k] == NULA) {
            cout << BG_BLACK;
            cout << "      ";
        }
        else {
            if (filaMeta == fila && colMeta == k)
                cout << BG_ORANGE;
            else
                cout << BG_BROWN;
            cout << "  ";
            if (matriz[fila][k] == 1)
                cout << FG_BLACK;
            else
                cout << FG_BLUE;
            cout << Square << Square;
            cout << Reset;
            if (filaMeta == fila && colMeta == k)
                cout << BG_ORANGE;
            else
                cout << BG_BROWN;
            cout << "  ";
        }
        cout << Reset;
    }
    cout << Vertical << endl;
}

void fichaAleatoria(const tTablero& tablero, int& fila, int& columna) {
    srand(time(NULL));
    // mostrar(tablero);
    do {
        fila = rand() % tablero.num_filas;
        columna = rand() % tablero.num_columnas;
    } while (!esFicha(tablero, fila, columna));


}

void reseteaTablero(tTablero& tablero, int f, int c) {
    tablero.num_filas = f;
    tablero.num_columnas = c;
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            tablero.celdaArray[i][j] = NULA;
        }
    }
}

void guardar(const tTablero& tablero, std::ofstream& file) {
    
        file << tablero.num_filas << " " << tablero.num_columnas << endl;
        for (int i = 0; i < tablero.num_filas; i++) {
            for (int j = 0; j < tablero.num_columnas; j++) {
                file << tablero.celdaArray[i][j] << " ";
            }
            file << endl;
        }
        file << tablero.fila_meta << " " << tablero.columna_meta << endl;
      
}