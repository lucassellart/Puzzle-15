#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10            // Total partidas
#define FIL 4           // Filas tablero
#define COL 4           // Columnas tablero
#define MIN 40          // Minimo apuesta
#define MAX 200         // Maximo apuesta

#ifdef _WIN64
    #define LIMPIAR_PANTALLA system("cls");     //Windows 64 bits
#elif _WIN32
    #define LIMPIAR_PANTALLA system("cls");     //Windows 32 bits
#elif __linux__
    #define LIMPIAR_PANTALLA system("clear");     //Linux
#endif


//Declaracion funciones

void mostrarTablero(int tablero[FIL][COL], int partidas);        // Funcion para mostrar el tablero

void realizarMovimiento(char direc, int B[FIL][COL], int *m);    // Funcion desplazamiento piezas

void asignacion_movimientos();                                   // Funcion para mostrar las teclas de desplazamiento

int solucion(int T[FIL][COL]);                                   // Funcion para recorrer el tablero hasta encontrar la solución

int puntaje(int mov, int apu);                                   // Funcion que analiza las apuestas y los movimientos, devolviendo un puntaje

int main() {

    int i;          // Va a iterar dentro del for que maneja las partidas
    int j;          // Va a iterar dentro del for que maneja el historial de las apuestas
    int num;        // Guardar numeros aleatorios generados
    int apuesta;    // Guardar apuesta del usuario
    int seguirJugando = 1;      // Variable utilizada para darle la opcion al usuario de seguir jugando (1) o abandonar la partida (0)

    int pp[N];      // Array para almacenar los puntajes de las partidas

    int tablerosUtilizados[N] = {0};        // Array para guardar tableros ya utilizados


    // Definir y cargar manualmente 10 tableros iniciales

    int tablerosIniciales[N][FIL][COL] = {                  // Todos estos tableros tienen solución (extraídos del Puzzle 15 online)

        {
            {6, 12, 3, 14}, {8, 11, 5, 10}, {7, 15, 1, 13}, {2, 4, 9, 0}
        },

        {
            {7, 9, 14, 11}, {3, 6, 13, 2}, {10, 5, 0, 4}, {12, 1, 8, 15}
        },

        {
            {10, 3, 11, 8}, {4, 14, 15, 5}, {7, 9, 1, 0}, {13, 12, 6, 2}
        },

        {
            {4, 6, 8, 2}, {13, 3, 1, 11}, {9, 10, 7, 12}, {0, 14, 15, 5}
        },

        {
            {10, 12, 9, 1}, {13, 0, 3, 14}, {6, 11, 7, 8}, {5, 2, 15, 4}
        },

        {
            {13, 12, 11, 14}, {15, 1, 9, 0}, {3, 7, 2, 5}, {10, 6, 4, 8}
        },

        {
            {8, 5, 15, 13}, {1, 12, 0, 11}, {2, 7, 3, 4}, {6, 10, 9, 14}
        },

        {
            {4, 8, 14, 0}, {11, 5, 12, 9}, {10, 6, 15, 13}, {2, 3, 7, 1}
        },

        {
            {10, 6, 7, 4}, {12, 14, 8, 11}, {5, 13, 0, 2}, {3, 15, 1, 9}
        },

        {
            {1, 4, 6, 3}, {10, 5, 8, 11}, {0, 7, 2, 14}, {9, 12, 13, 15}
        }

    };

    srand(time(NULL));          //Semilla para generar numeros aleatorios (evitar que siempre salgan los tableros en el mismo orden)

    printf("PUZZLE 15! A JUGAR!\n");

    printf("\nIngrese 1 para comenzar: ");
    scanf("%d", &seguirJugando);

    while (seguirJugando != 1) {
        printf("\nIngrese 1 para comenzar: ");
        scanf("%d", &seguirJugando);
    }

    printf("\n");

    for (i=0; i<N && seguirJugando == 1; i++) {             // Ciclo for principal, contiene las partidas, apuestas, historial, puntaje

        char direccion = ' ';                               // Variable declarada para manejar el abandono de una partida
        int movimientos = 0;                                // Variable utilizada para los movimientos que realiza el usuario (en la funcion cumple el rol de contador)

        // APUESTA

        do {
            printf("En cuantos movimientos apuesta resolver el juego? Entre [%d] y [%d]:\n", MIN, MAX);
            scanf("%d", &apuesta);
        } while (apuesta < MIN || apuesta > MAX);


        // TABLERO

        do {
            num = rand()%10;                            //Seleccionar un tablero aleatorio
        } while (tablerosUtilizados[num] != 0);         //Verificar que el tablero no se haya utilizado antes

            tablerosUtilizados[num] = 1;                //Marcar tablero actual como utilizado

            mostrarTablero(tablerosIniciales[num], i);

            asignacion_movimientos();


        // MOVIMIENTOS


        while (solucion(tablerosIniciales[num]) == 0 && direccion != 'q') {             // Mientras no se haya encontrado la solución y el jugador no quiera abandonar la partida:
            printf("\nDesplazamiento: ");
            scanf(" %c", &direccion);
            realizarMovimiento(direccion, tablerosIniciales[num], &movimientos);
            mostrarTablero(tablerosIniciales[num], i);
            asignacion_movimientos();

            printf("\nMovimientos: %d\n", movimientos);
            printf("\nApuesta: %d\n", apuesta);
        }


        if (solucion(tablerosIniciales[num]) == 1) {                                    // Si el jugador encontró la solución se muestra el puntaje y terminó la partida
            printf("FELICITACIONES! DESAFIO RESUELTO!\n");

            puntaje(movimientos, apuesta);
            printf("Puntaje obtenido: %d\n", puntaje(movimientos, apuesta));
            printf("\n");
        }

        if (direccion == 'q') {                                                         // Se le dá la opción al jugador de abandonar la partida cuando lo deseé
            printf("\nLA PARTIDA HA FINALIZADO.\n");
            printf("\n");

            puntaje(movimientos, apuesta);
            printf("Puntaje obtenido partida %d: %d\n", i+1,  puntaje(movimientos, apuesta));
            printf("\n");
        }

        pp[i] = puntaje(movimientos, apuesta);          // Almacenar en el array de puntaje el resultado del puntaje de la partida

        // MOSTRAR HISTORIAL

        printf("Historial:\n");

        for (j = 0; j < i+1; j++) {                     // Ciclo para mostrar el puntaje de todas las partidas jugadas

            printf("Partida %d: puntos: %d\n", j+1, pp[j]);
        }

        printf("\nDesea realizar una nueva partida? (1 = si, 0 = no): \n");

        do {
            printf("> ");
            scanf("%d", &seguirJugando);
        } while (seguirJugando != 1 && seguirJugando != 0);

    }

    if (i == N || seguirJugando == 0) {
        printf("\nEL JUEGO HA FINALIZADO. GRACIAS POR JUGAR.\n");
    }



    return 0;
}

void mostrarTablero(int tablero[FIL][COL], int partidas) {

    LIMPIAR_PANTALLA;           //Esta macro depende del sistema operativo y se utiliza para limpiar la pantalla de la computadora antes de mostrar el tablero. Dependiendo del sistema operativo, se utilizará el comando correspondiente para limpiar la pantalla (cls en Windows o clear en Linux).

    printf("Partida: %d\n", partidas + 1);
    printf("\n");

    int i, j;                           // i: fila, j: columna

    for (i = 0; i < FIL; i++) {         //Estos bucles for se utilizan para iterar sobre todas las filas y columnas del tablero bidimensional. El primer bucle for controla las filas (i representa el índice de la fila), y el segundo bucle for controla las columnas (j representa el índice de la columna).
        for (j = 0; j < COL; j++) {
            if (tablero[i][j] == 0) {   //Verifica si el valor en la posición actual del tablero es igual a cero (el valor del espacio vacío). Si es así, imprime "[ ]" para representar visualmente un espacio vacío.
                printf("[    ]");
            } else {
                printf("[ %.2d ] ", tablero[i][j]);
            }
        }
        printf("\n");   // Salto de linea despues de cada fila
    }
    printf("\n");       // Linea en blanco despues de imprimir el tablero completo
}


 void realizarMovimiento(char direc, int B[FIL][COL], int *m) {

 /*
    Parámetros:

        char direc: Representa la dirección del movimiento ('w', 'a', 's' o 'd').

        int B[FIL][COL]: Es el tablero del juego representado como un array bidimensional.

        int *m: Es un puntero a un entero, funciona como contador de los movimientos realizados.
 */

    int i, j, temporal, fil=0, col=0;

    for (i=0; i < FIL; i++) {
        for (j=0; j < COL; j++) {
            if (B[i][j] == 0) {     //Identificar la posicion actual del espacio vacio en el tablero
                fil = i;
                col = j;
                break;
            }
        }
    }

    // Realizar el movimiento segun la direccion

    switch (direc) {

    case 'w': case 'W':  // Arriba
        if (fil >= 0 && fil < 3) {              //Verificar si la pieza puede moverse en la direccion sin salir de los limites del tablero
            temporal = B[fil][col];
            B[fil][col] = B[fil + 1][col];
            B[fil + 1][col] = temporal;
            (*m)++;                             //Se incrementa el contador de movimientos mediante el puntero.
        }
        break;

    case 'a': case 'A':   // Izquierda
        if (col >= 0 && col < 3) {
            temporal = B[fil][col];
            B[fil][col] = B[fil][col + 1];
            B[fil][col + 1] = temporal;
            (*m)++;
        }
        break;

    case 's': case 'S':   // Abajo
        if (fil <= 3 && fil > 0) {
            temporal = B[fil][col];
            B[fil][col] = B[fil - 1][col];
            B[fil - 1][col] = temporal;
            (*m)++;
        }
        break;

    case 'd': case 'D':   // Derecha
        if (col <= 3 && col > 0) {
            temporal = B[fil][col];
            B[fil][col] = B[fil][col - 1];
            B[fil][col - 1] = temporal;
            (*m)++;
        }
        break;

    }
}

void asignacion_movimientos() {

    printf("w: Arriba\n");
    printf("a: Izquierda\n");
    printf("s: Abajo\n");
    printf("d: Derecha\n");
    printf("q: Abandonar partida\n");
}

int solucion(int T[FIL][COL]) {

    int i, j;
    int numero = 1;      //n se inicializa en 1 porque es el primer numero del tablero

    for (i=0; i < FIL; i++) {       //recorrer todo el tablero
        for (j=0; j < COL; j++) {

            if (T[i][j] == numero) {     //Verificar si el numero en la posicion actual es = al numero esperado
                numero++;                //Incrementar ese numero

                if (numero == 15 && T[FIL - 1][COL - 1] == 0) {      //Verificar si todos los numeros estan en orden
                    return 1;
                }
            }   else {
                    return 0;
            }
        }
    }
    return 0;
}

int puntaje(int mov, int apu) {

    if (mov >= (apu - 10) && mov < apu) {
        return 1200;

    } else if (mov > apu && mov <= (apu + 10)) {
        return 500;

    } else if (mov == apu) {
        return 1000;

    } else if (mov >= MIN && mov < (apu - 10)) {
        return  1500;

    } else {
        return 0;
    }
}
