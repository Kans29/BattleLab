
#ifndef __PUJBattleLab__Stack__
#define __PUJBattleLab__Stack__

#include <stdio.h>
#include "stdlib.h"
#include "BattleLab.h"

struct battleLabGame;

typedef struct battleLabGame pBattleLabGame_t;

typedef enum {
	VACIA = 0, NO_VACIA = 1
} estado_e;

typedef struct nodo {
	pBattleLabGame_t * battleLabGame;
	struct nodo * pSgte;
} nodo_t;

typedef struct pila{
	nodo_t * pCabezaPila;
} pila_t;

/* Operaciones pilas */
/*pre-condición: True, es una operacion creadora de pilas */
/*post-condición: Retorna el apuntador a una estructura de tipo pila_t.*/
pila_t * crearPila();

/*pre-condición: Entra un apuntador a una estructura de tipo pila_t previamente creada. */
/*post-condición: Devuelve VACIA si la pila está vacía y devuelve NO_VACIA en caso contrario*/
estado_e esPilaVacia(pila_t* pPila);

/*pre-condición: Recibe por parametro un apuntador a una pila, y apuntador a una estructura de tipo pBattleLabGame. */
/*post-condición: Adiciona una copia de la estructura del pBattleLabGame al tope de la pila*/
void pushPila(pila_t* pPila, pBattleLabGame_t * battleLabGame);

/*pre-condición: Recibe por parametro un apuntador a una pila */
/*post-condición: Elimina el ultimo nodo que se adiciono a la estructura de la pila*/
void popPila(pila_t* pPila);

/*pre-condición: Recibe por parametro un apuntador a una pila. */
/*post-condición: Retorna el apuntador a la estructura de datos pBattleLabGame que se encuentra en el ultimo nodo que se adiciono a la pila.*/
pBattleLabGame_t * peekPila(pila_t* pPila);

/*pre-condición: Recibe por parametro una pila previamente creada */
/*post-condición: Remueve todos los elementos de la pila dejandola vacia, no tiene retorno.*/
void vaciarPila(pila_t* pPila);


#endif /* defined(_PUJBattleLab__Stack) */
