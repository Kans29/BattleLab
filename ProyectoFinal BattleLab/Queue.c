#include "Queue.h"
#include "BattleLab.h"

estadoCola_e esColaVacia(cola_t* pCola) 
{

	if (pCola->pInicioCola == NULL) 
	{
		return COLA_VACIA;
	} 
	else 
	{
		return COLA_NO_VACIA;
	}
}

cola_t* crearCola() 
{
	cola_t *pCola = malloc(sizeof(cola_t));
	pCola->pInicioCola = NULL;
	pCola->pFinCola = NULL;
	return pCola;
}

void pushCola(cola_t* pCola, player_t* player) {

	//Crear el nuevo nodo
	nodoCola_t * nuevoNodo = malloc(sizeof(nodoCola_t));
	nuevoNodo->player = (player_t*)malloc(sizeof(player_t));
	if (nuevoNodo == NULL) 
	{
		printf("No se pudo reservar la memoria \n");
		//Instrucción para terminar el programa inmediatamente
		exit(EXIT_FAILURE);
	} 
	else 
	{
		nuevoNodo->player = player;
		nuevoNodo->pSgte = NULL;
		if (esColaVacia(pCola) == COLA_VACIA) 
		{
			//El nuevo nodo es el único elemento
			pCola->pInicioCola = nuevoNodo;
		} 
		else 
		{
			pCola->pFinCola->pSgte =  nuevoNodo;
			//Se acomadan los indices del final
		}
		//Se actualiza el fin de la cola con el nuevo nodo
		pCola->pFinCola = nuevoNodo;
	}

}

player_t* peekCola(cola_t* pCola)
{
	if (esColaVacia(pCola)==COLA_NO_VACIA) 
	{
		return pCola->pInicioCola->player;
	}
	else
	{
		printf("Se sacó un valor de una pila vacía");
		//Instrucción para terminar el programa inmediatamente
		exit(EXIT_FAILURE);
	}
}

void popCola(cola_t* pCola) {

	if (esColaVacia(pCola) == COLA_NO_VACIA) 
	{
		nodoCola_t * pNodoAux = pCola->pInicioCola;
		pCola->pInicioCola = pNodoAux->pSgte;
		free(pNodoAux);
	}
	else
	{
		printf("Se sacó un valor de una pila vacía");
		//Instrucción para terminar el programa inmediatamente
		exit(EXIT_FAILURE);
	}
}

void vaciarCola(cola_t* pCola)
{
	while(esColaVacia(pCola)==COLA_NO_VACIA)
	{
		popCola(pCola);
	}
}

