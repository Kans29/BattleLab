#ifndef __ARBOLNARIOS_H_
#define __ARBOLNARIOS_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BattleLab.h"


struct disparo;
typedef struct disparo disparo_t;


typedef struct nodoHijo 
{
    struct nodoArbol* pHijo;
    struct nodoHijo* pSgte;
}nodoHijo_t;

typedef struct nodoArbol 
{
	int numHijos;
    disparo_t * nuevoDisparo;
    nodoHijo_t *pHijos;
}nodoArbolN_t;

typedef enum 
{
	VACIO = 1, NO_VACIO = 0
}estadoArbolN_e;

/*pre-condición: True, es una funcion creadora, no requiere que exista algo antes */
/*post-condición: Retorna un apuntador a una estructura tipo arbol N-Ario*/
nodoArbolN_t* crearArbol();

/*pre-condición: Le entra un apuntador a una estructura de tipo Disparo, junto a las posiciones en X y en Y que va a tener el nuevo nodo */
/*post-condición: Retorna un Nodo de tipo nodoArbolN-T* con el campo de disparo inicializado en el X y en Y que entraron por parametro*/
nodoArbolN_t * crearNodo(disparo_t * disparo, int posX, int posY);

/*pre-condición: Entra por parametro un apuntador a una estreuctura de tipo NodoArbolN_t, debe existir previamente */
/*post-condición: Retorna el estado de dicho arbol, VACIO o NO_VACIO, que hacen parte del enum estadoArbolN-t*/
estadoArbolN_e esVacio(nodoArbolN_t * pArbol);

/*pre-condición: Entra por parametro un apuntador a un Arbol N-ario y un apuntador a una estructura de datos de tipo disparo para insertarla como nuevo nodo del arbol */
/*post-condición: Retorna el apuntador al arbol con el nuevo nodo ingresado en el arbol, nodo que tiene en el valos dirparo el que entro por parametro.*/
nodoArbolN_t * insertarNodo(nodoArbolN_t * pArbol, disparo_t * disparo);

/*pre-condición: Recibe por parametros una lista enlazada de los hijos de un arbol y el nuevo nodo que se va a anexar a la lista de hijos del arbol */
/*post-condición: Retorna el apuntador a la lizta enlazada a la que se le agrego el nuevo hijo.*/
nodoHijo_t * insertarHijo(nodoHijo_t* pLista, nodoArbolN_t* nuevoHijo);

#endif