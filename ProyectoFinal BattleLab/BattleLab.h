#ifndef __BATTLEBOARD_H__
#define __BATTLEBOARD_H__

#include "stdlib.h"
#include "time.h"
#include "Queue.h"
#include "Stack.h"
#include "Board.h"
#include "ArbolesNArios.h"


// IMPORTANT
/*
    Own board internal codes
    1 water
    11 shot into the water
    2 AircraftCarriers 
    21 shot into the AircraftCarrier
    3 Vessel 
    31 shot into a vessel
    4 Submarines
    41 shot into a submarine
    5 Police vehicles
    51 shot into a submarine
    6 Bonus
    61 shot into the bonus option
*/

/* Opponent board internal codes
    100 water
    101 Sucessfull shot
    102 Failed shot
*/
struct cola;
typedef struct cola cola_t;

struct pila;
typedef struct pila pila_t;

struct nodoArbol;
typedef struct nodoArbol nodoArbolN_t;
/* Enums */
typedef enum team{
	COMPUTER, HUMAN
} team_e;

typedef enum shipEnum{
   AIRCRAFT_CARRIERS=2, VESSEL=3, SUBMARINES=4, POLICE_VEHICLES=5, BONUS=6
} ship_e;

typedef enum estadoBarco
{
    HABILITADO = 0, AVERIADO = 1, HUNDIDO = 2
}estadoBarco_e;

/* Structs */

struct posicion
{
    int posX;
    int posY;
};

typedef struct posicion posicion_t;

struct disparo{
    int posX;
    int posY;
};
typedef struct disparo disparo_t;

struct barco
{
    ship_e ship;
    estadoBarco_e estado;
    int numPosLibres;
    int numPosImpactadas;
    posicion_t * posicion;
};

typedef struct barco barco_t;

struct player{
    team_e team;
    int numPlayer;
    char * playerName;
    int score;
    int pierdeTurno; // Variable que indica si el jugador pierde el turno (1 Si y 0 NO)
    int aciertoTurnoAnt; //Variable para saber si acerto en su intento en el turno y saber si entonces falla para no perder el turno
};

typedef struct player player_t;
/* Struct para guardar el arreglo de jugadores */
struct teamPlayers
{
    player_t * playersArray; //Arrego con memoria dinámica para guadar los jugadores
    int numberOfPlayers;
    int numeroPosicionesImpactadas;
    int numeroDisparos;
    double effectivenessRate; // Porcentaje de efectividad
    team_e team;
};

typedef struct teamPlayers teamPlayers_t;

struct battleBoard
{
    // Asignar los valores a las matrices de acuerdo al código interno que se presenta al inicio

    /* En el tablero propio se ubican los barcos y se ven los disparos del contrincante*/
    int ** ownBoard;
    
    /* En el tablero del contrincante se ven los disparos que haga el
    equipo en el tablero del contrincante */
    int ** opponentBoard;

    barco_t * portaAvionesArray;
    barco_t * buquesArray;
    barco_t * submarinosArray;
    barco_t * patrullerosArray;
    barco_t * bonusArray;

    int portaAvionesLibres;
    int buquesLibres;
    int submarinosLibres;
    int patrullerosLibres;
    int bonusLibres;
};

typedef struct battleBoard battleBoard_t;
// Adicionar los structs que les falte

struct battleLabGame
{
    player_t * currentPlayer;    
    teamPlayers_t * humanPlayersTeam; 
    teamPlayers_t * computerTeam; 
      
    int isEnd;// 1: end of game, 0: otherwise
    battleBoard_t * humanBoardTeam;
    battleBoard_t * computerBoard;
    nodoArbolN_t * pArbolActual;
    int tiroDeGracia;
    cola_t * pColaEquipo;
    //Info para estadisticas
    player_t winnerPlayer;
    team_e partialWinnerTeam; 
    int foundBonus; // 0 no se ha encontrado, 1 en otro caso
    int modoDebug;
    

};
typedef struct battleLabGame pBattleLabGame_t;



// function to setup the global variables and initialize the boards
//pBattleLabGame_t startGame( teamPlayers_t * humanPlayersTeam1, teamPlayers_t* humanPlayersTeam2);

// function to update the game
//pBattleLabGame_t updateGame(int,int,int,int,pBattleLabGame_t);

// function to undo a play
//pBattleLabGame_t undo(pBattleLabGame_t);

// function to get the ordered array of results
//pBattleLabGame_t getScore(pBattleLabGame_t);

/*pre-condición: Entra una estructura de tipo pBattleLabGame con los Tableros y los equipos. Entra la pila donde se almacenan las jugadas. */
/*post-condición: No retorna nada pero cambia el equipo humano y los tableros de ambos equipos.*/
void dispararEquipoHumano(pBattleLabGame_t * battleLabGameOriginal, pila_t * pilaJugadas);

/*pre-condición: Entra una estructura de tipo pBattleLabGame y el tipo de equipo*/
/*post-condición: Quita el bonus del equipo que impacto y permite mover un barco al equipo que impacto el bonus*/
void quitarBonusImpactadoYUbicarbarco(battleBoard_t * tableroEquipo,team_e equipo); // elimina el bonus si se le impacta

/*pre-condición: Entra un arreglo de jugadores y tres enteros*/
/*post-condición: Mezcla el arreglo jugadores y lo ordena*/
void merge(player_t* arreglo, int posInicial, int posMitad, int posFinal);

/*pre-condición: Entra el arreglo de jugadores y dos enteros*/
/*post-condición: Ordena el arreglo entre esas posiciones y con el merge mezcla los sub arrglos de jugadores y lo ordena por completo*/
void mergeSort(player_t* arreglo, int posInicial, int posFinal);

/*pre-condición: Entra un arreglo de estructura player y la imprime con dos enteros de desde y hasta. /
/*post-condición: Imprime el areglo*/
void imprimirRango(player_t* arreglo, int desde, int hasta);

/*pre-condición: Entra por parametros ambos equipos*/
/*post-condición: Imprime los arreglos ordenados con la funcion imprirmir arreglo */
void ordenarResultadosEquipos(teamPlayers_t * equipoUno, teamPlayers_t * equipoDos);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia la informacion del player en la estructura de copia*/
void copiarInfoPlayer(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia la estructura del equipo humano en la estructura de copia*/
void copiarInfoEquipoHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia la estructura del equipo máquina en la estructura de copia*/
void copiarInfoEquipoMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia la estructura del tablero del equipo humano en la estructura de copia*/
void copiarBoardEquipoHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia la estructura del tablero del equipo máquina en la estructura de copia*/
void copiarBoardEquipoMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Llama cada funcion de la copia de cada struct de barcos del equipo máquina */
void copiarBarcoEquipoMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int numeroBarco);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Llama cada funcion de la copia de cada struct de barcos del equipo humano */
void copiarBarcoEquipoHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int numeroBarco);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia el struct del porta aviones del equipo humano en la estructura de copia*/
void copiarPortaAvionesHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia el struct del porta aviones del equipo máquina en la estructura de copia*/
void copiarPortaAvionesMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia el struct de los buques del equipo humano en la estructura de copia*/
void copiarBuquesHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia el struct de los buques del equipo máquina en la estructura de copia*/
void copiarBuquesMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia el struct de los submarinos del equipo humano en la estructura de copia*/
void copiarSubMarinosHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia el struct de los submarinos del equipo máquina en la estructura de copia*/
void copiarSubMarinosMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia el struct de los patrulleros del equipo humano en la estructura de copia*/
void copiarPatrullerosHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia el struct de los patrulleros del equipo máquina en la estructura de copia*/
void copiarPatrullerosMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia el struct del bonus del equipo humano en la estructura de copia*/
void copiarBonusHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia el struct del bonus del equipo máquina en la estructura de copia*/
void copiarBonusMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Copia la cola del equipo humano y la coloca en la estructura de copia*/
void copiarColaEquipo(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia);

/*pre-condición: Entran dos estructura de tipo pBattleLabGame_t*/
/*post-condición: Llama todas las funciones de copia y hace la copia completa de todo la estructura pBattleLabGame_t*/
void copiarTodo(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia);

/*pre-condición: Entra una cola como parámetro donde guarda los jugadores*/
/*post-condición: Pasa al siguiente jugador en la cola*/
void actualizarTurno(cola_t * pCola);

/*pre-condición: Entra una cola donde se guardan los jugadores*/
/*post-condición: Verifica si el jugador en la cabeza de la cola debe o no perder el turno retornando un booleano*/
int verificarPierdeTurno(cola_t * pCola);

/*pre-condición: Entra una cola donde se guardan jugadores de tipo player_t y una estructura de equipo*/
/*post-condición: Inserta cada jugador del equipo en la cola de jugadores*/
void encolarJugadores(cola_t * pCola, teamPlayers_t * team);

/*pre-condición: Entra una pila de jugadas que almacena una estructura pBattleLabGame_t */
/*post-condición: Retorna la estructura que se encuentra en la cabeza de la pila para actualizar el juego*/
pBattleLabGame_t * deshacerJugada(pila_t * pilaJugadas);

/*pre-condición: Entra una pila donde se almacena cada jugada y la estructura actual del juego de tipo pBattleLabGame_t*/
/*post-condición: Deshace la jugada y actualiza el juego hasta esa jugada*/
void deshacer(pila_t * pilaJugadas, pBattleLabGame_t * battleLabGameOriginal);

/*pre-condición: Entran dos estructuras de tipo pBattleLabGame_T*/
/*post-condición: Se en carga de igualar la estructura actual con los datos de la copia para completar el deshacer*/
void actualizarStructOriginal(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia);

/*pre-condición: Entra una estructura de battleboard_t, un entero que identifica el barco, las posicones en X y Y donde se disparo y el player que esta disparando*/
/*post-condición: Cambia el estado del barco que se impacto y aumenta el score del jugador dependiendo de si se hundio el barco o no*/
void cambiarEstadoBarco(battleBoard_t * board, int tipoBarco, int posX, int posY, player_t * playerActual);

/*pre-condición: Entra una estructura de tipo pBattleLabGame con los Tableros y los equipos. Entra la pila donde se almacenan las jugadas.*/
/*post-condición: No retorna nada pero cambio el estado de los tableros de ambos equipo y el equipo máquina*/
void disparoMaquina(pBattleLabGame_t * battleLabGameOriginal, pila_t* pilaJugadas);

/*pre-condición: Entra la estructura de tipo pBattleLabGame, una posicion en X y una en Y*/
/*post-condición: Retorna un booleano si se es posible hacer el disparo en esa posición X y Y*/
int verificarDisparoCorrecto(pBattleLabGame_t * battleLabGameOriginal, int posX, int posY);

/*pre-condición: Entra una estructura de tipo battleboard_t y un equipo*/
/*post-condición: Reubica un barco habilitado y actualiza el tablero del equipo que reubicó el barco*/
void reubicarBarco(battleBoard_t * tableroEquipo,team_e equipo);

/*pre-condición: Entra una estructura battleboard_t, una posicion en X y otra en Y y un equipo*/
/*post-condición: Encuentra el barco que se quiere reubicar y lo coloca en la nueva posición con ayuda de la función reubicar barco*/
int encontrarYPosicionarBarco(battleBoard_t * tableroEquipo, int posH, int posV, team_e team);

/*pre-condición: Entra el tablero, el tipo de barco, el numero del barco y la medidad como enteros*/
/*post-condición: Borra el barco que se quiere cambiar*/
void borrarBarco(battleBoard_t * tableroEquipo ,barco_t* barco, int numBarco, int medidaBarco);

/*pre-condición: Recibe toda la estructura pBattleLabGame_t*/
/*post-condición: Imprime en pantalla todas las estadísticas del juego, equipo ganador, efectividad, ordena los equipos por puntajes y muestra el estado de los barcos*/
void mostrarEstadisticas(pBattleLabGame_t * battleLabGameOriginal);

/*pre-condición: Entra una raiz de un arbol n-ario y un entero*/
/*post-condición: Retorna un hijo del abol para actualizar la nueva raiz usando el entero que se recibe por parametro */
nodoArbolN_t* generarNuevaRaiz(nodoArbolN_t* pArbolActual, int posHijo);

/*pre-condición: Recibe la estructura de todo el juego y un entero para verificar ciertos condicionales */
/*post-condición: Actualiza la raiz del arbol con sus hijos que son los posibles disparos que puede hacer la máquina*/
void crearPosiblesDisparos(pBattleLabGame_t * battleLabGameOriginal, int verificadorHijos);

/*pre-condición: Entra la estructura pBattleLabGame_t y dos enteros que son dos posiciones en X y en Y*/
/*post-condición: Retorna un booleano que permite verificar si el disparo es correcto en esa posición X y Y*/
int verificarDisparoCorrecto(pBattleLabGame_t * battleLabGameOriginal, int posX, int posY);

/*pre-condición: Recibe un arreglo de barcos, y dos enteros*/
/*post-condición: Imprime la información del estado de los barcos para las estadísticas*/
void imprimirInfoBarcos(barco_t * barcosArray, int cantidadBarcos, int medidaBarco);
// .... 

#endif