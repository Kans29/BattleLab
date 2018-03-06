#include "Stack.h"
#include "BattleLab.h"

pila_t * crearPila() 
{

	pila_t *pPila = malloc(sizeof(pila_t));
	pPila->pCabezaPila = NULL;
	return pPila;
}


/* Retornar VACIA o NO_VACIA segun corresponda*/
estado_e esPilaVacia(pila_t* pPila) 
{
	if (pPila->pCabezaPila == NULL)
	{
		return VACIA;
	}
	else
	{
		return NO_VACIA;
	}
}


void pushPila(pila_t* pPila, pBattleLabGame_t * battleLabGame) {
	//Crear el nuevo nodo
	nodo_t * nuevoNodo = malloc(sizeof(nodo_t));
	if (nuevoNodo == NULL) {
		printf("No se pudo reservar la memoria \n");
		//Instrucción para terminar el programa inmediatamente
		exit(EXIT_FAILURE);
	} 
	else 
	{
		nuevoNodo->battleLabGame = battleLabGame;
		if (esPilaVacia(pPila) == VACIA) 
		{
			//El nuevo nodo es el único elemento y 
			//debe apuntar a siguiente
			nuevoNodo->pSgte=NULL;
		} 
		else 
		{
			//Reencadenar la pila
			nuevoNodo->pSgte=pPila->pCabezaPila;
		}
		//Actualizar la cabeza de la pila
		pPila->pCabezaPila = nuevoNodo;
	}
}

void popPila(pila_t* pPila) 
{
	
	if (esPilaVacia(pPila) == NO_VACIA) 
	{
		nodo_t * pNodoAux = pPila->pCabezaPila;
		pPila->pCabezaPila = pNodoAux->pSgte;
		free(pNodoAux);
	} 
	else 
	{
		printf("Se sacó un valor de una pila vacía");
		//Instrucción para terminar el programa inmediatamente
		exit(EXIT_FAILURE);
	}
}

pBattleLabGame_t * peekPila(pila_t* pPila) {
	if (esPilaVacia(pPila) == NO_VACIA) 
	{
		return pPila->pCabezaPila->battleLabGame;
	}
	else
	{
		printf("No se pudo consultar el valor de la cabeza, "
			"la pila estaba vacía");
		//Instrucción para terminar el programa inmediatamente
		exit(EXIT_FAILURE);
	}
	
}


void vaciarPila(pila_t* pPila)
{
	while(esPilaVacia(pPila)==NO_VACIA)
	{
		popPila(pPila);
	}
}

