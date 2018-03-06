#include "ArbolesNArios.h"

nodoArbolN_t* crearArbol()
{
	nodoArbolN_t * pArbol= NULL;
	return pArbol;
}

nodoArbolN_t * crearNodo(disparo_t * disparo, int posX, int posY)
{
	nodoArbolN_t * nuevoNodo = malloc(sizeof(nodoArbolN_t));
	nuevoNodo->nuevoDisparo = disparo;
	nuevoNodo->nuevoDisparo->posX = posX;
	nuevoNodo->nuevoDisparo->posY = posY;
	/*nuevoNodo->nuevoDisparo->dir = -1;
	nuevoNodo->nuevoDisparo->dirEncontrada = 0;
	nuevoNodo->nuevoDisparo->impacto = -1;*/
	nuevoNodo->pHijos=NULL;
	nuevoNodo->numHijos = 0;
	return nuevoNodo;
}

nodoHijo_t * insertarHijo(nodoHijo_t* pLista, nodoArbolN_t* nuevoHijo)
{
	nodoHijo_t * nuevoNodo = (nodoHijo_t*)malloc(sizeof(nodoHijo_t));
	nuevoNodo->pHijo = nuevoHijo;
	if(pLista==NULL)
	{
		nuevoNodo->pSgte = NULL;
		pLista = nuevoNodo;
	}
	else
	{
		nuevoNodo->pSgte = pLista;
		pLista = nuevoNodo;
	}
	return pLista;
	
}

nodoArbolN_t * insertarNodo(nodoArbolN_t * pArbol, disparo_t * disparo)
{
	nodoArbolN_t * nodoNuevo = crearNodo(disparo, disparo->posX, disparo->posY);
	if(esVacio(pArbol))
	{
		pArbol = nodoNuevo;
		return pArbol;
	}
	else
	{
		pArbol->pHijos = insertarHijo(pArbol->pHijos, nodoNuevo);
		nodoNuevo->numHijos++;
	}

	return pArbol;
}

estadoArbolN_e esVacio(nodoArbolN_t * pArbol) 
{
	if (pArbol == NULL) {
		return VACIO;
	} else {
		return NO_VACIO;
	}
}


