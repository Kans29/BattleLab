#include "BattleLab.h"
#include "Board.h"
#include "Queue.h"
#include "Stack.h"
#include "ArbolesNArios.h"


int main()
{
	int cantidadDeshacer, i;
	int posHijo;
	pBattleLabGame_t * battleLabGameOriginal;
	battleLabGameOriginal = (pBattleLabGame_t*)malloc(sizeof(pBattleLabGame_t));

	do
	{
		printf("Desea iniciar el juego con el modo debug: (SI: 1, NO: 0)\n");
		scanf("%d", &battleLabGameOriginal->modoDebug);
		if(battleLabGameOriginal->modoDebug < 0 || battleLabGameOriginal->modoDebug > 1)
		{
			printf("El modoDebug debe tomar el valor de 1 o 0.\n");
		}
	}while(battleLabGameOriginal->modoDebug < 0 || battleLabGameOriginal->modoDebug > 1);


	battleLabGameOriginal->humanPlayersTeam = crearEquipo();
	battleLabGameOriginal->computerTeam = crearEquipoMaquina();
	battleLabGameOriginal->pColaEquipo = crearCola();
	encolarJugadores(battleLabGameOriginal->pColaEquipo, battleLabGameOriginal->humanPlayersTeam);

	battleLabGameOriginal->humanBoardTeam = (battleBoard_t*)malloc(sizeof(battleBoard_t));
	battleLabGameOriginal->humanBoardTeam->ownBoard = reservarMemoriaTablero();
	battleLabGameOriginal->humanBoardTeam->opponentBoard = reservarMemoriaTablero();
	battleLabGameOriginal->humanBoardTeam = crearTablerosEquipos(battleLabGameOriginal->humanBoardTeam->ownBoard, battleLabGameOriginal->humanBoardTeam->opponentBoard);

	battleLabGameOriginal->computerBoard = (battleBoard_t*)malloc(sizeof(battleBoard_t));
	battleLabGameOriginal->computerBoard->ownBoard = reservarMemoriaTablero();
	battleLabGameOriginal->computerBoard->opponentBoard = reservarMemoriaTablero();
	battleLabGameOriginal->computerBoard = crearTablerosEquipos(battleLabGameOriginal->computerBoard->ownBoard, battleLabGameOriginal->computerBoard->opponentBoard);

	pila_t * pilaJugadas;
	pilaJugadas = crearPila();
	battleLabGameOriginal->isEnd = 0;
	battleLabGameOriginal->foundBonus = 0;
	battleLabGameOriginal->tiroDeGracia = 0;
	battleLabGameOriginal->currentPlayer = peekCola(battleLabGameOriginal->pColaEquipo);

	printf(" VA A PONER LOS BARCOS EL EQUIPO 1 \n\n");
	actualizarTablero(battleLabGameOriginal->humanBoardTeam->ownBoard);
	colocarBarcos(battleLabGameOriginal->humanBoardTeam);

	printf(" VA A PONER LOS BARCOS EL DE LA MAQUINA \n\n");
	colocarBarcosMaquina(battleLabGameOriginal->computerBoard);
	if(battleLabGameOriginal->modoDebug == 1)
	{
		printf("TABLERO DE LA MAQUINA\n");
		actualizarTablero(battleLabGameOriginal->computerBoard->ownBoard);
	}

	
	pBattleLabGame_t * battleLabGameCopia;
	battleLabGameCopia = (pBattleLabGame_t*)malloc(sizeof(pBattleLabGame_t));
	copiarTodo(battleLabGameOriginal, battleLabGameCopia);
	pushPila(pilaJugadas, battleLabGameCopia);

	battleLabGameOriginal->pArbolActual = crearArbol();
	disparo_t * disparo = (disparo_t*)malloc(sizeof(disparo_t));
	disparo->posX = 0;
	disparo->posY = 0;
	battleLabGameOriginal->pArbolActual = insertarNodo(battleLabGameOriginal->pArbolActual, disparo);
	int cantidadDisparos = 0;
	do
	{	
		dispararEquipoHumano(battleLabGameOriginal, pilaJugadas);
		disparoMaquina(battleLabGameOriginal,pilaJugadas);
		cantidadDisparos++;
		crearPosiblesDisparos(battleLabGameOriginal, 0);
		if(cantidadDisparos >= 16)
 		{
 			printf("Va a entrar por la segunda seleccion\n");
 			crearPosiblesDisparos(battleLabGameOriginal, 1);
 		}
 		else{
 			crearPosiblesDisparos(battleLabGameOriginal, 0);
 		}
		battleLabGameOriginal->pArbolActual = battleLabGameOriginal->pArbolActual->pHijos->pHijo;
		printf("Cuantas jugadas desea deshacer: \n");
		scanf("%d", &cantidadDeshacer);
		for(i=0; i<cantidadDeshacer; i++)
		{	
			deshacer(pilaJugadas, battleLabGameOriginal);
		}
		mostrarEstadisticas(battleLabGameOriginal);
		verificarGanadorYTiroDeGracia(battleLabGameOriginal, pilaJugadas);
	}while(battleLabGameOriginal->isEnd == 0);
	printf("SE TERMINO EL JUEGO\n");
	printf("ESTADISTICAS FINALES\n");
	mostrarEstadisticas(battleLabGameOriginal);

	free(battleLabGameCopia);
	free(battleLabGameOriginal);
}