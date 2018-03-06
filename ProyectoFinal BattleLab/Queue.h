#ifndef __PUJBattleLab__Queue__
#define __PUJBattleLab__Queue__

#include "stdio.h"
#include "stdlib.h"
#include "BattleLab.h"

struct player;
typedef struct player player_t;

typedef enum {
	COLA_VACIA = 0, COLA_NO_VACIA = 1
} estadoCola_e;

typedef struct nodoCola {
	player_t* player;
	struct nodoCola * pSgte;
} nodoCola_t;

typedef struct cola{
	nodoCola_t * pInicioCola;
	nodoCola_t * pFinCola;
} cola_t;

/* Operaciones colas */
cola_t* crearCola();

/*pre-condición: True, es una operacion creadora de colas */
/*post-condición: Retorna el apuntador a una estructura de tipo cola_t.*/
estadoCola_e esColaVacia(cola_t* pCola);

/*pre-condición: Entra un apuntador a una estructura de tipo Cola_t previamente creada. */
/*post-condición: Devuelve VACIA si la cola está vacía y devuelve NO_VACIA en caso contrario*/
void pushCola(cola_t* pCola, player_t * player);

/*pre-condición: Recibe por parametro un apuntador a una cola, y un jugador de tipo Player_t para anexar a la cola. */
/*post-condición: Adiciona un jugador al final de la cola y retorna la cola*/
player_t* peekCola(cola_t* pCola);

/*pre-condición: Recibe por parametro una cola previamente creada */
/*post-condición: extrae de la cola el jugador que ocupa la primera posición, lo cual significa que el jugador que antes ocupaba la segunda posición ahora ocupa el primer lugar.*/
void popCola(cola_t* pCola);

/*pre-condición: Recibe por parametro una cola previamente creada */
/*post-condición: Remueve todos los elementos de la cola dejandola vacia, no tiene retorno.*/
void vaciarCola(cola_t* pCola);

#endif /* defined(__PUJBattleLab__Queue__) */
