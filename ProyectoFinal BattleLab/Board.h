#ifndef __PUJBattleLab__Board__
#define __PUJBattleLab__Board__
#include "stdio.h"
#include "stdlib.h"
#include "BattleLab.h"

struct barco;
typedef struct barco barco_t;

struct player;
typedef struct player player_t;

struct pila;
typedef struct pila pila_t;

struct teamPlayers;
typedef struct teamPlayers teamPlayers_t;

struct battleBoard;
typedef struct battleBoard battleBoard_t;

struct battleLabGame;
typedef struct battleLabGame pBattleLabGame_t;

/*pre-condición: True, no tiene pre requisito, reserva la memoria para una matriz de enteros */
/*post-condición: Retorna el apuntador a la matriz de enteros a la que se le ha reservado memoria previamente*/
int ** reservarMemoriaTablero(); // Funcion para reservar memoria a una matriz de enteros

/*pre-condición: Recibe por parametro un apuntador a una matriz de enteros previamente creada */
/*post-condición: Inicializa todos los valores de la matriz en 1 y la retorna*/
int** inicializarTableroEquipoUno(int ** MatrizJugador); // inicializa los tabkeros en los valores principales

/*pre-condición: Recibe por parametro un apuntador a una matriz de enteros previamente creada */
/*post-condición: Inicializa todos los valores enteros de dicha matriz en 100, luegoi retorna el apuntador a dicha matriz*/
int** inicializarTableroOponente(int ** MatrizOponente);// inicializa los tabkeros en los valores principales

/*pre-condición: Recibe por parametro recibe or parametro un apuntador a una matriz de enteros previamente creada */
/*post-condición: No tiene retorno, pero actualiza e imprime en consola la matriz con sus valores de forma ordenada*/
void actualizarTablero(int ** MatrizJugador);//actualiza la matriz

/*pre-condición: Recibe por parametro Un apuntador a una estructura de tipo tablero previamente creada */
/*post-condición: No tiene retorno, Ubica en la matriz del tablero propia los barcos de un equipo*/
void colocarBarcos(battleBoard_t * boardHumano);//funcion para poner todos los barcos en los tableros

/*pre-condición: Recibe por parametro un apuntador a una estructura de un Tablero de juego y un identificador de tipo entero que referencia a el barco a ubicar
1 si es portaaviones, 2 si es buque, 3 si es submarino, 4 si es patrullero y 5 si es el bonus. */
/*post-condición: No retorna nada,Ubica todos los barcos que permite el juego del tipo de barco que se ingreso por parametro, es decir, si es un portaaviones, solo pone 1.*/
void ponerBarco(battleBoard_t * boardHumano, int barco);//funcion para poner barco

/*pre-condición: rue, es una funcion creadora de jugadores */
/*post-condición: retorna un jugador de tipo Player_t*/
player_t crearJugardor(); // genera un jugador

/*pre-condición: True, es una funcion creadora para la maquina */
/*post-condición: Retorna un jugador de tipo Maquina*/
player_t crearJugardorMaquina();

/*pre-condición: True, es una funcion creadora del equipo humano */
/*post-condición: Retorna un apuntador a una estructura de un equipo de jugadores humanos*/
teamPlayers_t * crearEquipo(); // crea un equipo de jugadores

/*pre-condición: True, es una funcion creadora del equipo maquina */
/*post-condición: Retorna un apuntador a una estructura del equipo de la maquina*/
teamPlayers_t * crearEquipoMaquina();

/*pre-condición: Recibe por parametro 2 matrices de enteros previamente creadas */
/*post-condición: Retorna un apuntador a una estructura de tipo battleBoard al que se le asignan las matrices que entraron por parametro como own y opponent*/
battleBoard_t * crearTablerosEquipos(int ** MatrizJugador, int** MatrizOponente ); // crea los tableros de los equipos

/*pre-condición: Recibe or parametro el apuntador a la estructura del juego actual, y la pila de ugadas */
/*post-condición: No tiene retorno, verifica que ya exista un ganador entre los equipos y revisa si puede brindar el tiro de gracia al equipo perdedor*/
void verificarGanadorYTiroDeGracia(pBattleLabGame_t * battleLabGameOriginal,pila_t * pilaJugadas);

/*pre-condición: Recibe por parametros el apuntador a la estructura del juego actual, y el apuntador a la pila de las jugadas realizadas */
/*post-condición: No tiene retorno, realiza el tiro de gracia por parte del equipo que perdio la partida*/
void tiroDeGracia(pBattleLabGame_t * battleLabGameOriginal, pila_t* pilaJugadas);

/*pre-condición: Recibe por parametro el apuntador al tablero del equipo humano, la medida de el barco a ubicar, el identificador del abrco,
la cantidad de barcos de ese tipo que se van a poner, el arreglo del tipo de barcos que se va a poner y el numero del barco. */
/*post-condición: No tiene retorno, Ubica el barco con las caracteristicas ingresadas por parametros en el tablero del equipo*/
void posicionarBarco(battleBoard_t * boardHumano, int medidaBarco, int numeroBarco, int cantidadBarcos, barco_t * barcosArray, int barco);

/*pre-condición: Recibe por parametros el tipo de barco y la medida del barco que se va a crear */
/*post-condición: Retorna una estructura de tipo batco_t de tipo tipoBarco y medida medidaBarco*/
barco_t crearBarco(int tipoBarco, int medidaBarco);

/*pre-condición: Recibe por parametros el board de la maquina y el identificador del tipo de barco que s eva a ubicar en el tablero */
/*post-condición: No retorna, Ubica en el tablero todos os barcos del identificador que entro or parametro.*/
void ponerBarcosMaquina(battleBoard_t * boardMaquina, int barco);

/*pre-condición: Recibe por parametro un apuntador a un board, la medida de un barco, una posicion en X y en Y junto a la direccion vertical u horizontal */
/*post-condición: Retorna un Valor booleano dependiendo de si el barco se puede ubicar en la posicion deseada o no*/
int verificarPosicionBarco(battleBoard_t * boardMaquina, int medidaBarco, int posX, int posY, int dir);

/*pre-condición: recibe por parametros el tablero de la maquina, el arreglo de los barcos de un tipo de la maquina, la medida del tipo de barco, el identificador,
las posiciones en X y en Y en donde se quiere posicionar el barco y su direccion. */
/*post-condición: No tiene retorno, ubica el barco del tipo ingresado en las posiciones X y Y con la Dir ingresadas.*/
void posicionarBarcoMaquina(battleBoard_t * boardMaquina, barco_t * barcosArray, int medidaBarco, int numeroBarco, int posX, int posY, int dir, int numBarco);

/*pre-condición: Recibe por parametro el apuntador a el board de la maquina*/
/*post-condición: No tiene retorno, ubica todos los barcos de manera correcta y al azar en el tablero de la maquina*/
void colocarBarcosMaquina(battleBoard_t * boardMaquina);

/*pre-condición: Recibe or parametro el board del humano, el identificador del barco, y la ubicacion de ese barco en el arreglo de barcos del tablero,
solo se usa para reubicar un barco previamente puesto */
/*post-condición: No tiene retorno, ubica el barco que se encuentra en la ubicacion del arreglo ingresada por parametro en una nueva posicion del teclado*/
void ponerUnSoloBarco(battleBoard_t * boardHumano, int barco, int ubicacion);

/*pre-condición: Recibe or parametro el board del humano, el identificador del barco, la medida del barco, el arreglo del tipo de barco deseado 
y la ubicacion de ese barco en el arreglo de barcos del tablero,solo se usa para reubicar un barco previamente puesto */
/*post-condición: No tiene retorno, posiciona correctamente el barco que se encuentra en la ubicacion del arreglo ingresada por parametro en una nueva posicion del teclado*/
void posicionarUnSoloBarco(battleBoard_t * boardHumano, int medidaBarco, int numeroBarco, barco_t * barcosArray,int ubicacion, int barco);

/*pre-condición: Recibe or parametro el board de la maquina, el identificador del barco, y la ubicacion de ese barco en el arreglo de barcos del tablero,
solo se usa para reubicar un barco previamente puesto */
/*post-condición: No tiene retorno, ubica el barco que se encuentra en la ubicacion del arreglo ingresada por parametro en una nueva posicion del teclado
generada a travez de un random*/
void ponerUnBarcoMaquina(battleBoard_t * boardMaquina, int barco, int ubicacion);

#endif /* defined(__PUJDamasLab__TableroJugadas__) */
