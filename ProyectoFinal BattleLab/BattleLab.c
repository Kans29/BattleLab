#include "BattleLab.h"

void dispararEquipoHumano(pBattleLabGame_t * battleLabGameOriginal, pila_t * pilaJugadas)
{
	int pierdeTurno = 1; // variable booleana para verificar si el jugador puede hacer su turno o no.
	int acierto = 1; // variable que verifica si se acerto o no
	char posH; // variable quer guarda la posicion en Horizontal del barco(va de A hasta J)
	int posV; // variable que guarda la posicion en vertical del barco ( va de 1 a 10)
	int posJugador;
	if(battleLabGameOriginal->humanPlayersTeam->numberOfPlayers > 1)
	{
		do
		{   
		// en este ciclo se verifica si el jugador pierde el turno o no, de ser asi, se avanza en la cola de jugadores al siguiente
			pierdeTurno = verificarPierdeTurno(battleLabGameOriginal->pColaEquipo);
			if(pierdeTurno==1)
			{
				printf("El jugador: %s pierde el turno por haber fallado en su turno anterior.\n", battleLabGameOriginal->pColaEquipo->pInicioCola->player->playerName);
				actualizarTurno(battleLabGameOriginal->pColaEquipo);
			}
		}while(pierdeTurno != 0);
	}

	posJugador = battleLabGameOriginal->pColaEquipo->pInicioCola->player->numPlayer;

	// se actualizan tableros
	actualizarTablero(battleLabGameOriginal->humanBoardTeam->opponentBoard);
	actualizarTablero(battleLabGameOriginal->humanBoardTeam->ownBoard);

	do  // este ciclo es para realizar el disparo en base a la variable booleana que indica si hubo acierto o no, permitiendo repetir jugada
	{
		if(battleLabGameOriginal->modoDebug == 1)
		{
			actualizarTablero(battleLabGameOriginal->computerBoard->opponentBoard);
			actualizarTablero(battleLabGameOriginal->computerBoard->ownBoard);
		}
		printf("Es el turno del jugador %s del equipo HUMANO.\n", battleLabGameOriginal->pColaEquipo->pInicioCola->player->playerName);

		do// este ciclo es para realizar el disparo en general verificando que se ingresen datos adecuados y la posicion este libre
		{
			printf("Las posiciones en horizontal van desde la letra A hasta la letra J incluida. \n");
			printf("Digite en mayuscula una letra entre la A y la J incluida: \n");
			fflush(stdin);
			scanf("%c", &posH);

			printf("Escriba la posición en vertical (1 al 10) donde quiere disparar: \n");
			fflush(stdin);
			scanf("%d", &posV);

			if(posH < 65 || posH > 74 || posV < 1 || posV > 10) // se verifica posicion horizontal y vertical
			{
				printf("Esta ubicación se encuentra fuera del tablero.\n");
			}
			if(battleLabGameOriginal->humanBoardTeam->opponentBoard[posH-65][posV-1] != 100){

				printf("Esta posicion ya fue impactada.\n");
			}
		}while(posH < 65 || posH > 74 || posV < 1 || posV > 10 || battleLabGameOriginal->humanBoardTeam->opponentBoard[posH-65][posV-1] != 100);

		int posHInt=posH - 65;	
		posV = posV - 1;

		printf("%d \n", posH);
		printf("%d \n", posV);

		 // en este swich/case se dan las opciones de si llega a impactar un tipo de barco las modificaciones que sufren las matrices
		pBattleLabGame_t * battleLabGameCopia;
		battleLabGameCopia = (pBattleLabGame_t*)malloc(sizeof(pBattleLabGame_t));
		switch(battleLabGameOriginal->computerBoard->ownBoard[posHInt][posV]){ 
			case 1: // si se impacta agua
				battleLabGameOriginal->computerBoard->ownBoard[posHInt][posV] = 11;
				battleLabGameOriginal->humanBoardTeam->opponentBoard[posHInt][posV] = 102;
				battleLabGameOriginal->humanPlayersTeam->numeroDisparos++;
				if(battleLabGameOriginal->pColaEquipo->pInicioCola->player->aciertoTurnoAnt == 0)
				{
					battleLabGameOriginal->pColaEquipo->pInicioCola->player->pierdeTurno = 1;
					battleLabGameOriginal->pColaEquipo->pInicioCola->player->aciertoTurnoAnt = 0;
				}
				actualizarTablero(battleLabGameOriginal->humanBoardTeam->opponentBoard);
				actualizarTablero(battleLabGameOriginal->humanBoardTeam->ownBoard);
				acierto = 0;
				break;
			case 2: // si se impacta a un PortaAviones
				battleLabGameOriginal->computerBoard->ownBoard[posHInt][posV] = 21;
				battleLabGameOriginal->humanBoardTeam->opponentBoard[posHInt][posV] = 101;
				battleLabGameOriginal->pColaEquipo->pInicioCola->player->aciertoTurnoAnt = acierto = 1;
				actualizarTablero(battleLabGameOriginal->humanBoardTeam->opponentBoard);
				actualizarTablero(battleLabGameOriginal->humanBoardTeam->ownBoard);
				battleLabGameOriginal->humanPlayersTeam->playersArray[posJugador-1].score += 1;
				battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas++;
				battleLabGameOriginal->humanPlayersTeam->numeroDisparos++;
				cambiarEstadoBarco(battleLabGameOriginal->computerBoard, 2, posHInt, posV, &battleLabGameOriginal->humanPlayersTeam->playersArray[posJugador-1]);
				break;
			case 3: // si se impacta a un Buque
				battleLabGameOriginal->computerBoard->ownBoard[posHInt][posV] = 31;
				battleLabGameOriginal->humanBoardTeam->opponentBoard[posHInt][posV] = 101;
				battleLabGameOriginal->pColaEquipo->pInicioCola->player->aciertoTurnoAnt = acierto = 1;
				actualizarTablero(battleLabGameOriginal->humanBoardTeam->opponentBoard);
				actualizarTablero(battleLabGameOriginal->humanBoardTeam->ownBoard);
				battleLabGameOriginal->humanPlayersTeam->playersArray[posJugador-1].score += 1;
				battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas++;
				battleLabGameOriginal->humanPlayersTeam->numeroDisparos++;
				cambiarEstadoBarco(battleLabGameOriginal->computerBoard, 3, posHInt, posV, &battleLabGameOriginal->humanPlayersTeam->playersArray[posJugador-1]);
				break;
			case 4: // si se impacta a un Submarino
				battleLabGameOriginal->computerBoard->ownBoard[posHInt][posV] = 41;
				battleLabGameOriginal->humanBoardTeam->opponentBoard[posHInt][posV] = 101;
				battleLabGameOriginal->pColaEquipo->pInicioCola->player->aciertoTurnoAnt = acierto = 1;
				actualizarTablero(battleLabGameOriginal->humanBoardTeam->opponentBoard);
				actualizarTablero(battleLabGameOriginal->humanBoardTeam->ownBoard);
				battleLabGameOriginal->humanPlayersTeam->playersArray[posJugador-1].score += 1;
				battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas++;
				battleLabGameOriginal->humanPlayersTeam->numeroDisparos++;
				cambiarEstadoBarco(battleLabGameOriginal->computerBoard, 4, posHInt, posV, &battleLabGameOriginal->humanPlayersTeam->playersArray[posJugador-1]);
				break;
			case 5: // si se impacta a un Patrullero
				battleLabGameOriginal->computerBoard->ownBoard[posHInt][posV] = 51;
				battleLabGameOriginal->humanBoardTeam->opponentBoard[posHInt][posV] = 101;
				battleLabGameOriginal->pColaEquipo->pInicioCola->player->aciertoTurnoAnt = acierto = 1;
				actualizarTablero(battleLabGameOriginal->humanBoardTeam->opponentBoard);
				actualizarTablero(battleLabGameOriginal->humanBoardTeam->ownBoard);
				battleLabGameOriginal->humanPlayersTeam->playersArray[posJugador-1].score += 4;
				battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas++;
				battleLabGameOriginal->humanPlayersTeam->numeroDisparos++;
				cambiarEstadoBarco(battleLabGameOriginal->computerBoard, 5, posHInt, posV, &battleLabGameOriginal->humanPlayersTeam->playersArray[posJugador-1]);
				break;
			case 6: // si se impacta a l bonus
				battleLabGameOriginal->computerBoard->ownBoard[posHInt][posV] = 61;
				battleLabGameOriginal->humanBoardTeam->opponentBoard[posHInt][posV] = 101;
				quitarBonusImpactadoYUbicarbarco(battleLabGameOriginal->humanBoardTeam,battleLabGameOriginal->humanPlayersTeam->team); // se elimina el bonus del otro jugador
				battleLabGameOriginal->pColaEquipo->pInicioCola->player->aciertoTurnoAnt = acierto = 1;
				battleLabGameOriginal->humanPlayersTeam->playersArray[posJugador-1].score += 10;
				battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas++;
				battleLabGameOriginal->humanPlayersTeam->numeroDisparos++;
				actualizarTablero(battleLabGameOriginal->humanBoardTeam->opponentBoard);
				actualizarTablero(battleLabGameOriginal->humanBoardTeam->ownBoard);
				break;
		}
		copiarTodo(battleLabGameOriginal, battleLabGameCopia);
		pushPila(pilaJugadas, battleLabGameCopia);
	}while(acierto!=0);

	actualizarTurno(battleLabGameOriginal->pColaEquipo);

}

void mostrarEstadisticas(pBattleLabGame_t * battleLabGameOriginal){

	int eleccion;
	do{
		printf("Desea ver las estadisticas del juego? ( 1 : SI, 0 : NO)\n");
		scanf("%d",&eleccion);
		if(eleccion < 0 || eleccion > 1){
			printf("Esa opcion esta incorrecta.\n");
		}
	}while(eleccion < 0 || eleccion > 1);
	if(eleccion == 0){
		printf("No se mostraran las estadisticas.\n");
	}
	else{
		if(battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas > battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas){
			battleLabGameOriginal->partialWinnerTeam = HUMAN;
		}
		else{
			if(battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas < battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas){
				battleLabGameOriginal->partialWinnerTeam = COMPUTER;
			}
		}
		printf("      ESTADISTICAS INDIVIDUALES: \n\n");
		ordenarResultadosEquipos(battleLabGameOriginal->humanPlayersTeam, battleLabGameOriginal->computerTeam);
		battleLabGameOriginal->winnerPlayer = battleLabGameOriginal->humanPlayersTeam->playersArray[0];
		printf("      ESTADISTICAS GENERALES: \n\n");
		if(battleLabGameOriginal->partialWinnerTeam == HUMAN){
			printf("Equipo parcialmente ganador: HUMAN\n");
		}
		else{
			printf("Equipo parcialmente ganador: COMPUTER\n");
		}
		if(battleLabGameOriginal->winnerPlayer.score == 0){
			printf("Jugador con mayor puntaje: Todos tienen 0.\n");
		}
		else{
			printf("Jugador con mayor puntaje: %s\n", battleLabGameOriginal->winnerPlayer.playerName );
		}
		double numerador = battleLabGameOriginal->humanPlayersTeam-> numeroPosicionesImpactadas;
		double denominador = battleLabGameOriginal->humanPlayersTeam-> numeroDisparos;

		if(battleLabGameOriginal->humanPlayersTeam->numeroDisparos == 0){
			battleLabGameOriginal->humanPlayersTeam-> effectivenessRate = 0.0;
		}else{
			battleLabGameOriginal->humanPlayersTeam-> effectivenessRate = ( numerador / denominador)*100;
		}
		numerador = battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas;
		denominador = battleLabGameOriginal->computerTeam->numeroDisparos;

		if(battleLabGameOriginal->computerTeam->numeroDisparos == 0){
			battleLabGameOriginal->computerTeam-> effectivenessRate = 0.0;
		}else{
			battleLabGameOriginal->computerTeam-> effectivenessRate = (numerador / denominador)*100;
		}
		printf(" PORCENTAJES DE EFECTIVIDAD:\n\n");
		printf("HUMAN : %lf \n",battleLabGameOriginal->humanPlayersTeam->effectivenessRate);
		printf("COMPUTER: %lf\n",battleLabGameOriginal->computerTeam->effectivenessRate);

		printf("El status de los barcos del equipo Humano es el siguiente: \n");
		imprimirInfoBarcos(battleLabGameOriginal->humanBoardTeam->portaAvionesArray, 1, 4);
		imprimirInfoBarcos(battleLabGameOriginal->humanBoardTeam->buquesArray, 2, 3);
		imprimirInfoBarcos(battleLabGameOriginal->humanBoardTeam->submarinosArray, 3, 2);
		imprimirInfoBarcos(battleLabGameOriginal->humanBoardTeam->patrullerosArray, 4, 1);
		printf("El status de los barcos del equipo Maquina es el siguiente: \n");
		imprimirInfoBarcos(battleLabGameOriginal->computerBoard->portaAvionesArray, 1, 4);
		imprimirInfoBarcos(battleLabGameOriginal->computerBoard->buquesArray, 2, 3);
		imprimirInfoBarcos(battleLabGameOriginal->computerBoard->submarinosArray, 3, 2);
		imprimirInfoBarcos(battleLabGameOriginal->computerBoard->patrullerosArray, 4, 1);

		if(battleLabGameOriginal->foundBonus == 1)
		{
			printf("El elemento bonus ya ha sido encontrado.\n");
		}
		else
		{
			printf("El elemento bonus no ha sido encontrado.\n");
		}

	}
}

void reubicarBarco(battleBoard_t * tableroEquipo,team_e equipo){
	srand(time(NULL));
	printf(" Usted acaba de impactar el bonus, puede cambiar la posicion de un barco.\n");

	char posH;
	int posHInt;
	int posV;
	int bandera = 0;
	switch(equipo){
		case HUMAN:
			do{
				do// este ciclo es para realizar el disparo en general verificando que se ingresen datos adecuados y la posicion este libre
				{
					printf("Escriba la posicion en horizontal (letra en mayúscula) : \n");
					fflush(stdin);
					scanf("%c", &posH);

					printf("Escriba la posición en vertical (1 al 10) : \n");
					fflush(stdin);
					scanf("%d", &posV);

					if(posH < 65 || posH > 74 || posV < 1 || posV > 10) // se verifica posicion horizontal y vertical
					{
						printf("Esta ubicación se encuentra fuera del tablero.\n");
					}
					if(tableroEquipo->ownBoard[posH-65][posV-1] == 1){

						printf("En esta posicion no se encuentran barcos.\n");
					}
				}while(posH < 65 || posH > 74 || posV < 1 || posV > 10 );


				posHInt = posH - 65;	
				posV = posV - 1;
	
				bandera = encontrarYPosicionarBarco( tableroEquipo, posHInt, posV, equipo);
				if(bandera == 0){
					printf("El barco no esta habilitado.\n");
				}
			}while(bandera == 0);	
			break;
		case COMPUTER:
			do{
				do// este ciclo es para realizar el disparo en general verificando que se ingresen datos adecuados y la posicion este libre
				{
					posHInt = rand() % 10;
					posV = rand() % 10;

				}while(posHInt < 1 || posHInt > 10 || posV < 1 || posV > 10 );
	
				bandera = encontrarYPosicionarBarco( tableroEquipo, posHInt, posV, equipo);
			}while(bandera == 0);	
			break;
	}
	

}

void borrarBarco(battleBoard_t * tableroEquipo ,barco_t* barco, int numBarco, int medidaBarco){

	int i,x,y;

	for( i = 0; i < medidaBarco; ++i ){
		x = barco[numBarco].posicion[i].posX;
		y = barco[numBarco].posicion[i].posY;
		tableroEquipo->ownBoard[x][y] = 1;
	}

}

int encontrarYPosicionarBarco(battleBoard_t * tableroEquipo, int posH, int posV, team_e team){
	int i,j;
	int bandera = 0;
	for(i = 0; i < 1 && bandera == 0; ++i){
		for(j = 0; j < 4; ++j){
			if(tableroEquipo->portaAvionesArray[i].posicion[j].posX == posH && tableroEquipo->portaAvionesArray[i].posicion[j].posY == posV){
				if(tableroEquipo->portaAvionesArray[i].estado == HABILITADO){
					borrarBarco(tableroEquipo, tableroEquipo->portaAvionesArray, i , 4);
					if(team == HUMAN){
						ponerUnSoloBarco(tableroEquipo, 1, i);
					}
					else{
						ponerUnBarcoMaquina(tableroEquipo, 1, i);
					}
					bandera = 1;
				}
			}
		}
	}
	for(i = 0; i < 2 && bandera == 0; ++i){
		for(j = 0; j < 3; ++j){
			if(tableroEquipo->buquesArray[i].posicion[j].posX == posH && tableroEquipo->buquesArray[i].posicion[j].posY == posV){
				if(tableroEquipo->buquesArray[i].estado == HABILITADO){
					borrarBarco(tableroEquipo, tableroEquipo->buquesArray, i , 3);
					if(team == HUMAN){
						ponerUnSoloBarco(tableroEquipo, 2, i);
					}
					else{
						ponerUnBarcoMaquina(tableroEquipo, 2, i);
					}
					bandera = 1;

				}
			}
		}
	}
	for(i = 0; i < 3 && bandera == 0; ++i){
		for(j = 0; j < 2; ++j){
			if(tableroEquipo->submarinosArray[i].posicion[j].posX == posH && tableroEquipo->submarinosArray[i].posicion[j].posY == posV){
				if(tableroEquipo->submarinosArray[i].estado == HABILITADO){
					borrarBarco(tableroEquipo, tableroEquipo->submarinosArray, i , 2);
					if(team == HUMAN){
						ponerUnSoloBarco(tableroEquipo, 3, i);
					}
					else{
						ponerUnBarcoMaquina(tableroEquipo, 3, i);
					}
					bandera = 1;
				}
			}
		}
	}
	for(i = 0; i < 4 && bandera == 0; ++i){
		for(j = 0; j < 1; ++j){
			if(tableroEquipo->patrullerosArray[i].posicion[j].posX == posH && tableroEquipo->patrullerosArray[i].posicion[j].posY == posV){
				if(tableroEquipo->portaAvionesArray[i].estado == HABILITADO){
					borrarBarco(tableroEquipo, tableroEquipo->patrullerosArray, i , 1);
					if(team == HUMAN){
						ponerUnSoloBarco(tableroEquipo, 4, i);
					}
					else{
						ponerUnBarcoMaquina(tableroEquipo, 4, i);
					}
					bandera = 1;
				}
			}
		}
	}
	return bandera;

}

void quitarBonusImpactadoYUbicarbarco(battleBoard_t * tableroEquipo, team_e equipo){ // esta funcion elimina el bonus si es impactado por uno de los jugadores

	int i,j,bandera = 0;
	for(i = 0; i < 10 && bandera == 0; i++){
		for(j = 0; j < 10 && bandera == 0; j++){

			if(tableroEquipo->ownBoard[i][j] == 6){
				tableroEquipo->ownBoard[i][j] = 1;
				bandera = 1;
			}
		}
	}
	reubicarBarco(tableroEquipo,equipo);
}


void merge(player_t * arreglo, int posInicial, int posMitad, int posFinal) 
{

	int tamArrayTemp = (posFinal - posInicial)+1;
	player_t* arregloParcial;
	arregloParcial = (player_t*) calloc(tamArrayTemp,sizeof(player_t));
	int indexMitadUno = posInicial;
	int indexMitadDos = posMitad + 1;
	int indexArregloParcial = 0;
	int indexArregloFinal;

	//printf("\n Inicia mezcla posInicial:%d, posMitad:%d, posFinal:%d\n ",
	//		posInicial, posMitad, posFinal);

	//printf(" Arreglo para mezclar:____\n");

	//imprimirRango(arreglo, posInicial,posFinal);

	while (indexMitadUno <= posMitad && indexMitadDos <= posFinal) {
		//Se hacen las comparaciones para el ordenamiento
		if (arreglo[indexMitadUno].score >= arreglo[indexMitadDos].score) {
			//Se pone primero en el arreglo parcial el contenido de indexMitadUno
			arregloParcial[indexArregloParcial] = arreglo[indexMitadUno];
			//Se incrementa el index de mitad dos para avanzar en el arreglo
			indexMitadUno++;
		} else {
			//Se pone primero en el arreglo parcial el contenido de indexMitadDos
			arregloParcial[indexArregloParcial] = arreglo[indexMitadDos];
			//Se incrementa el index de mitad dos para avanzar en el arreglo
			indexMitadDos++;
		}
		//Se incrementa el indice del arreglo parcial
		indexArregloParcial++;
	}
	//Se acomodan los elementos que faltan
	while (indexMitadUno <= posMitad) {
		arregloParcial[indexArregloParcial] = arreglo[indexMitadUno];
		indexArregloParcial++;
		indexMitadUno++;
	}
	while (indexMitadDos <= posFinal) {
		arregloParcial[indexArregloParcial] = arreglo[indexMitadDos];
		indexArregloParcial++;
		indexMitadDos++;
	}
	//Se actualizan los valores en el arreglo de entrada
	//printf("Arreglo temporal mezcla:____\n");
	//imprimirRango(arregloParcial, 0,indexArregloParcial-1);
	
	for (indexArregloParcial = 0; indexArregloParcial < tamArrayTemp;
			indexArregloParcial++) {
		indexArregloFinal = posInicial + indexArregloParcial;
		arreglo[indexArregloFinal] = arregloParcial[indexArregloParcial];
	}
	//printf("Arreglo ajustado \n");
	//imprimirRango(arreglo, posInicial, posFinal);

}

void imprimirRango(player_t* arreglo, int desde, int hasta) {

	int i = 0;
	for (i = desde; i <= hasta; i++) {
		printf("Posicion: %d -- Jugador: %s -- Puntaje: %d \n", i+1, arreglo[i].playerName, arreglo[i].score);
	}
}
/* Funcion que ordena usando el algoritmo de ordenamento merge sort */
void mergeSort(player_t* arreglo, int posInicial, int posFinal) 
{

	//Condicion de salida recursion
	//Cuando no se cumple, esto indica que se ha llegado a arrays de un elemento
	//printf("\n posInicial:%d, posFinal:%d, subArray a ordenar: \n", posInicial,
	//		posFinal);

	
	if (posInicial < posFinal) {
		int posMitad = (posInicial + posFinal) / 2;
		//Se parte el arreglo recursivamente
		//Primera mitad ( en la primera iteracion de la 0 a la posMitad)
		mergeSort(arreglo, posInicial, posMitad);
		//Segunda mitad ( en la primera iteracion de la posMitad+1 a posFinal)
		mergeSort(arreglo, posMitad + 1, posFinal);
		//Mezclar arreglo ( En este procedimiento se ordena el arreglo)
		merge(arreglo, posInicial, posMitad, posFinal);

		//printf("El arreglo de jugadores ordenado es:\n");
		
	}else{
		//printf(".....Para la recursion\n");
	}

}
void ordenarResultadosEquipos(teamPlayers_t * equipoUno, teamPlayers_t * equipoDos)
{

	printf("Los resultados del equipo uno son:\n");
	int cantidadJugadoresUno = equipoUno->numberOfPlayers;
	mergeSort(equipoUno->playersArray, 0 , cantidadJugadoresUno-1 );
	imprimirRango(equipoUno->playersArray, 0, cantidadJugadoresUno-1);

	printf("Los resultados del equipo dos son:\n");
	int cantidadJugadoresDos = equipoDos->numberOfPlayers;
	mergeSort(equipoDos->playersArray, 0 , cantidadJugadoresDos-1 );
	imprimirRango(equipoDos->playersArray, 0, cantidadJugadoresDos-1);
}

void copiarInfoPlayer(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia) 
{
	// se realiza una copia elemento por elemento del jugador que entre por parametro, y meterlo a una copia del juego original

	battleLabGameCopia->currentPlayer = (player_t*)malloc(sizeof(player_t));
	battleLabGameCopia->currentPlayer->playerName = malloc(sizeof(char*)*15);


	battleLabGameCopia->currentPlayer->team = battleLabGameOriginal->currentPlayer->team;
	battleLabGameCopia->currentPlayer->numPlayer = battleLabGameOriginal->currentPlayer->numPlayer;
	battleLabGameCopia->currentPlayer->playerName = battleLabGameOriginal->currentPlayer->playerName;
	battleLabGameCopia->currentPlayer->score = battleLabGameOriginal->currentPlayer->score;
	battleLabGameCopia->currentPlayer->pierdeTurno = battleLabGameOriginal->currentPlayer->pierdeTurno;
	battleLabGameCopia->currentPlayer->aciertoTurnoAnt = battleLabGameOriginal->currentPlayer->aciertoTurnoAnt;

}

void copiarInfoEquipoHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia)
{
	// se realiza una copia elemento por elemento del equipo que entra or parametro para poder llevar el manejo de las jugadas y poder deshacerlas
	int i;
	battleLabGameCopia->humanPlayersTeam = (teamPlayers_t*)malloc(sizeof(teamPlayers_t));
	battleLabGameCopia->humanPlayersTeam->playersArray = (player_t*)malloc(sizeof(player_t)*battleLabGameOriginal->humanPlayersTeam->numberOfPlayers);


	for(i=0; i<battleLabGameOriginal->humanPlayersTeam->numberOfPlayers; i++)
	{
		battleLabGameCopia->humanPlayersTeam->playersArray[i].team = battleLabGameOriginal->humanPlayersTeam->playersArray[i].team;
		battleLabGameCopia->humanPlayersTeam->playersArray[i].numPlayer = battleLabGameOriginal->humanPlayersTeam->playersArray[i].numPlayer;
		battleLabGameCopia->humanPlayersTeam->playersArray[i].playerName = battleLabGameOriginal->humanPlayersTeam->playersArray[i].playerName;
		battleLabGameCopia->humanPlayersTeam->playersArray[i].score = battleLabGameOriginal->humanPlayersTeam->playersArray[i].score;
		battleLabGameCopia->humanPlayersTeam->playersArray[i].pierdeTurno = battleLabGameOriginal->humanPlayersTeam->playersArray[i].pierdeTurno;
		battleLabGameCopia->humanPlayersTeam->playersArray[i].aciertoTurnoAnt = battleLabGameOriginal->humanPlayersTeam->playersArray[i].aciertoTurnoAnt;
	}
	battleLabGameCopia->humanPlayersTeam->numberOfPlayers = battleLabGameOriginal->humanPlayersTeam->numberOfPlayers;
	battleLabGameCopia->humanPlayersTeam->numeroPosicionesImpactadas = battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas;
	battleLabGameCopia->humanPlayersTeam->effectivenessRate = battleLabGameOriginal->humanPlayersTeam->effectivenessRate;
	battleLabGameCopia->humanPlayersTeam->team = battleLabGameOriginal->humanPlayersTeam->team;

}

void copiarInfoEquipoMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia)
{
	// se realiza una copia elemento por elemento del equipo que entra or parametro para poder llevar el manejo de las jugadas y poder deshacerlas
	int i;
	battleLabGameCopia->computerTeam = (teamPlayers_t*)malloc(sizeof(teamPlayers_t));
	battleLabGameCopia->computerTeam->playersArray = (player_t*)malloc(sizeof(player_t));


	battleLabGameCopia->computerTeam->playersArray[0].team = battleLabGameOriginal->computerTeam->playersArray[0].team;
	battleLabGameCopia->computerTeam->playersArray[0].numPlayer = battleLabGameOriginal->computerTeam->playersArray[0].numPlayer;
	battleLabGameCopia->computerTeam->playersArray[0].playerName = battleLabGameOriginal->computerTeam->playersArray[0].playerName;
	battleLabGameCopia->computerTeam->playersArray[0].score = battleLabGameOriginal->computerTeam->playersArray[0].score;

	battleLabGameCopia->computerTeam->numberOfPlayers = battleLabGameOriginal->computerTeam->numberOfPlayers;
	battleLabGameCopia->computerTeam->numeroPosicionesImpactadas = battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas;
	battleLabGameCopia->computerTeam->effectivenessRate = battleLabGameOriginal->computerTeam->effectivenessRate;
	battleLabGameCopia->computerTeam->team = battleLabGameOriginal->computerTeam->team;

}

void copiarBoardEquipoHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia)
{
	// copia los elementos del tablero uno a uno del juego actual
	int i,j;
	battleLabGameCopia->humanBoardTeam = (battleBoard_t*)malloc(sizeof(battleBoard_t));
	battleLabGameCopia->humanBoardTeam->ownBoard = reservarMemoriaTablero();
	battleLabGameCopia->humanBoardTeam->opponentBoard = reservarMemoriaTablero();

	battleLabGameCopia->humanBoardTeam = crearTablerosEquipos(battleLabGameCopia->humanBoardTeam->ownBoard, battleLabGameCopia->humanBoardTeam->opponentBoard);

	for(i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			battleLabGameCopia->humanBoardTeam->ownBoard[i][j] = battleLabGameOriginal->humanBoardTeam->ownBoard[i][j];
			battleLabGameCopia->humanBoardTeam->opponentBoard[i][j] = battleLabGameOriginal->humanBoardTeam->opponentBoard[i][j];
		}
	}

	copiarBarcoEquipoHumano(battleLabGameOriginal, battleLabGameCopia, 2);
	copiarBarcoEquipoHumano(battleLabGameOriginal, battleLabGameCopia, 3);
	copiarBarcoEquipoHumano(battleLabGameOriginal, battleLabGameCopia, 4);
	copiarBarcoEquipoHumano(battleLabGameOriginal, battleLabGameCopia, 5);
	copiarBarcoEquipoHumano(battleLabGameOriginal, battleLabGameCopia, 6);
}

void copiarBoardEquipoMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia)
{
	// copia los elementos del tablero uno a uno del juego actual
	int i,j;
	battleLabGameCopia->computerBoard = (battleBoard_t*)malloc(sizeof(battleBoard_t));
	battleLabGameCopia->computerBoard->ownBoard = reservarMemoriaTablero();
	battleLabGameCopia->computerBoard->opponentBoard = reservarMemoriaTablero();

	battleLabGameCopia->computerBoard = crearTablerosEquipos(battleLabGameCopia->computerBoard->ownBoard, battleLabGameCopia->computerBoard->opponentBoard);

	for(i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			battleLabGameCopia->computerBoard->ownBoard[i][j] = battleLabGameOriginal->computerBoard->ownBoard[i][j];
			battleLabGameCopia->computerBoard->opponentBoard[i][j] = battleLabGameOriginal->computerBoard->opponentBoard[i][j];
		}
	}

	copiarBarcoEquipoMaquina(battleLabGameOriginal, battleLabGameCopia, 2);
	copiarBarcoEquipoMaquina(battleLabGameOriginal, battleLabGameCopia, 3);
	copiarBarcoEquipoMaquina(battleLabGameOriginal, battleLabGameCopia, 4);
	copiarBarcoEquipoMaquina(battleLabGameOriginal, battleLabGameCopia, 5);
	copiarBarcoEquipoMaquina(battleLabGameOriginal, battleLabGameCopia, 6);
}

void copiarBarcoEquipoHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int numeroBarco)
{	
	int i;
	int cantidadBarcos;
	int medidaBarco;
	switch(numeroBarco)
	{
		case 2:
			cantidadBarcos = 1;
			medidaBarco = 4;
			battleLabGameCopia->humanBoardTeam->portaAvionesArray = (barco_t*)malloc(sizeof(barco_t));
			battleLabGameCopia->humanBoardTeam->portaAvionesArray[0] = crearBarco(2, medidaBarco);
			copiarPortaAvionesHumano(battleLabGameOriginal, battleLabGameCopia, cantidadBarcos, medidaBarco);
			break;
		case 3:
			cantidadBarcos = 2;
			medidaBarco = 3;
			battleLabGameCopia->humanBoardTeam->buquesArray = (barco_t*)malloc(sizeof(barco_t)*2);
			for(i=0; i<cantidadBarcos; i++)
			{	
				battleLabGameCopia->humanBoardTeam->buquesArray[i] = crearBarco(3, medidaBarco);
			}
			copiarBuquesHumano(battleLabGameOriginal, battleLabGameCopia, cantidadBarcos, medidaBarco);
			break;
		case 4:
			cantidadBarcos = 3;
			medidaBarco = 2;
			battleLabGameCopia->humanBoardTeam->submarinosArray = (barco_t*)malloc(sizeof(barco_t)*3);
			for(i=0; i<cantidadBarcos; i++)
			{
				battleLabGameCopia->humanBoardTeam->submarinosArray[i] = crearBarco(4, medidaBarco);
			}
			copiarSubMarinosHumano(battleLabGameOriginal, battleLabGameCopia, cantidadBarcos, medidaBarco);
			break;
		case 5:
			cantidadBarcos = 4;
			medidaBarco = 1;
			battleLabGameCopia->humanBoardTeam->patrullerosArray = (barco_t*)malloc(sizeof(barco_t)*4);
			for(i=0; i<cantidadBarcos; i++)
			{
				battleLabGameCopia->humanBoardTeam->patrullerosArray[i] = crearBarco(5, medidaBarco);
			}
			copiarPatrullerosHumano(battleLabGameOriginal, battleLabGameCopia, cantidadBarcos, medidaBarco);
			break;
		case 6:
			cantidadBarcos = 1;
			medidaBarco = 1;
			battleLabGameCopia->humanBoardTeam->bonusArray = (barco_t*)malloc(sizeof(barco_t));
			battleLabGameCopia->humanBoardTeam->bonusArray[0] = crearBarco(6, medidaBarco);
			copiarBonusHumano(battleLabGameOriginal, battleLabGameCopia, cantidadBarcos, medidaBarco);
			break;
	}
}

void copiarBarcoEquipoMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int numeroBarco)
{	
	int i;
	int cantidadBarcos;
	int medidaBarco;
	switch(numeroBarco)
	{
		case 2:
			cantidadBarcos = 1;
			medidaBarco = 4;
			battleLabGameCopia->computerBoard->portaAvionesArray = (barco_t*)malloc(sizeof(barco_t));
			battleLabGameCopia->computerBoard->portaAvionesArray[0] = crearBarco(2, medidaBarco);
			copiarPortaAvionesMaquina(battleLabGameOriginal, battleLabGameCopia, cantidadBarcos, medidaBarco);
			break;
		case 3:
			cantidadBarcos = 2;
			medidaBarco = 3;
			battleLabGameCopia->computerBoard->buquesArray = (barco_t*)malloc(sizeof(barco_t)*2);
			for(i=0; i<cantidadBarcos; i++)
			{	
				battleLabGameCopia->computerBoard->buquesArray[i] = crearBarco(3, medidaBarco);
			}
			copiarBuquesMaquina(battleLabGameOriginal, battleLabGameCopia, cantidadBarcos, medidaBarco);
			break;
		case 4:
			cantidadBarcos = 3;
			medidaBarco = 2;
			battleLabGameCopia->computerBoard->submarinosArray = (barco_t*)malloc(sizeof(barco_t)*3);
			for(i=0; i<cantidadBarcos; i++)
			{
				battleLabGameCopia->computerBoard->submarinosArray[i] = crearBarco(4, medidaBarco);
			}
			copiarSubMarinosMaquina(battleLabGameOriginal, battleLabGameCopia, cantidadBarcos, medidaBarco);
			break;
		case 5:
			cantidadBarcos = 4;
			medidaBarco = 1;
			battleLabGameCopia->computerBoard->patrullerosArray = (barco_t*)malloc(sizeof(barco_t)*4);
			for(i=0; i<cantidadBarcos; i++)
			{
				battleLabGameCopia->computerBoard->patrullerosArray[i] = crearBarco(5, medidaBarco);
			}
			copiarPatrullerosMaquina(battleLabGameOriginal, battleLabGameCopia, cantidadBarcos, medidaBarco);
			break;
		case 6:
			cantidadBarcos = 1;
			medidaBarco = 1;
			battleLabGameCopia->computerBoard->bonusArray = (barco_t*)malloc(sizeof(barco_t));
			battleLabGameCopia->computerBoard->bonusArray[0] = crearBarco(6, medidaBarco);
			copiarBonusMaquina(battleLabGameOriginal, battleLabGameCopia, cantidadBarcos, medidaBarco);
			break;
	}
}

void copiarPortaAvionesHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco)
{
	int i,j;
	for(i=0; i<cantidadBarcos; i++)
	{	
		for(j=0; j<medidaBarco; j++)
		{	
			battleLabGameCopia->humanBoardTeam->portaAvionesArray[i].posicion[j].posX = battleLabGameOriginal->humanBoardTeam->portaAvionesArray[i].posicion[j].posX;
			battleLabGameCopia->humanBoardTeam->portaAvionesArray[i].posicion[j].posY = battleLabGameOriginal->humanBoardTeam->portaAvionesArray[i].posicion[j].posY;
		}
		battleLabGameCopia->humanBoardTeam->portaAvionesArray[i].ship = battleLabGameOriginal->humanBoardTeam->portaAvionesArray[i].ship;
		battleLabGameCopia->humanBoardTeam->portaAvionesArray[i].estado = battleLabGameOriginal->humanBoardTeam->portaAvionesArray[i].estado;
		battleLabGameCopia->humanBoardTeam->portaAvionesArray[i].numPosLibres = battleLabGameOriginal->humanBoardTeam->portaAvionesArray[i].numPosLibres;
		battleLabGameCopia->humanBoardTeam->portaAvionesArray[i].numPosImpactadas = battleLabGameOriginal->humanBoardTeam->portaAvionesArray[i].numPosImpactadas;
	}
}

void copiarPortaAvionesMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco)
{
	int i,j;
	for(i=0; i<cantidadBarcos; i++)
	{	
		for(j=0; j<medidaBarco; j++)
		{	
			battleLabGameCopia->computerBoard->portaAvionesArray[i].posicion[j].posX = battleLabGameOriginal->computerBoard->portaAvionesArray[i].posicion[j].posX;
			battleLabGameCopia->computerBoard->portaAvionesArray[i].posicion[j].posY = battleLabGameOriginal->computerBoard->portaAvionesArray[i].posicion[j].posY;
		}
		battleLabGameCopia->computerBoard->portaAvionesArray[i].ship = battleLabGameOriginal->computerBoard->portaAvionesArray[i].ship;
		battleLabGameCopia->computerBoard->portaAvionesArray[i].estado = battleLabGameOriginal->computerBoard->portaAvionesArray[i].estado;
		battleLabGameCopia->computerBoard->portaAvionesArray[i].numPosLibres = battleLabGameOriginal->computerBoard->portaAvionesArray[i].numPosLibres;
		battleLabGameCopia->computerBoard->portaAvionesArray[i].numPosImpactadas = battleLabGameOriginal->computerBoard->portaAvionesArray[i].numPosImpactadas;
	}
}

void copiarBuquesHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco)
{
	int i,j;
	for(i=0; i<cantidadBarcos; i++)
	{	
		for(j=0; j<medidaBarco; j++)
		{	
			battleLabGameCopia->humanBoardTeam->buquesArray[i].posicion[j].posX = battleLabGameOriginal->humanBoardTeam->buquesArray[i].posicion[j].posX;
			battleLabGameCopia->humanBoardTeam->buquesArray[i].posicion[j].posY = battleLabGameOriginal->humanBoardTeam->buquesArray[i].posicion[j].posY;
		}
		battleLabGameCopia->humanBoardTeam->buquesArray[i].ship = battleLabGameOriginal->humanBoardTeam->buquesArray[i].ship;
		battleLabGameCopia->humanBoardTeam->buquesArray[i].estado = battleLabGameOriginal->humanBoardTeam->buquesArray[i].estado;
		battleLabGameCopia->humanBoardTeam->buquesArray[i].numPosLibres = battleLabGameOriginal->humanBoardTeam->buquesArray[i].numPosLibres;
		battleLabGameCopia->humanBoardTeam->buquesArray[i].numPosImpactadas = battleLabGameOriginal->humanBoardTeam->buquesArray[i].numPosImpactadas;
	}
}

void copiarBuquesMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco)
{
	int i,j;
	for(i=0; i<cantidadBarcos; i++)
	{	
		for(j=0; j<medidaBarco; j++)
		{	
			battleLabGameCopia->computerBoard->buquesArray[i].posicion[j].posX = battleLabGameOriginal->computerBoard->buquesArray[i].posicion[j].posX;
			battleLabGameCopia->computerBoard->buquesArray[i].posicion[j].posY = battleLabGameOriginal->computerBoard->buquesArray[i].posicion[j].posY;
		}
		battleLabGameCopia->computerBoard->buquesArray[i].ship = battleLabGameOriginal->computerBoard->buquesArray[i].ship;
		battleLabGameCopia->computerBoard->buquesArray[i].estado = battleLabGameOriginal->computerBoard->buquesArray[i].estado;
		battleLabGameCopia->computerBoard->buquesArray[i].numPosLibres = battleLabGameOriginal->computerBoard->buquesArray[i].numPosLibres;
		battleLabGameCopia->computerBoard->buquesArray[i].numPosImpactadas = battleLabGameOriginal->computerBoard->buquesArray[i].numPosImpactadas;
	}
}

void copiarSubMarinosHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco)
{
	int i,j;
	for(i=0; i<cantidadBarcos; i++)
	{	
		for(j=0; j<medidaBarco; j++)
		{	
			battleLabGameCopia->humanBoardTeam->submarinosArray[i].posicion[j].posX = battleLabGameOriginal->humanBoardTeam->submarinosArray[i].posicion[j].posX;
			battleLabGameCopia->humanBoardTeam->submarinosArray[i].posicion[j].posY = battleLabGameOriginal->humanBoardTeam->submarinosArray[i].posicion[j].posY;
		}
		battleLabGameCopia->humanBoardTeam->submarinosArray[i].ship = battleLabGameOriginal->humanBoardTeam->submarinosArray[i].ship;
		battleLabGameCopia->humanBoardTeam->submarinosArray[i].estado = battleLabGameOriginal->humanBoardTeam->submarinosArray[i].estado;
		battleLabGameCopia->humanBoardTeam->submarinosArray[i].numPosLibres = battleLabGameOriginal->humanBoardTeam->submarinosArray[i].numPosLibres;
		battleLabGameCopia->humanBoardTeam->submarinosArray[i].numPosImpactadas = battleLabGameOriginal->humanBoardTeam->submarinosArray[i].numPosImpactadas;
	}
}

void copiarSubMarinosMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco)
{
	int i,j;
	for(i=0; i<cantidadBarcos; i++)
	{	
		for(j=0; j<medidaBarco; j++)
		{	
			battleLabGameCopia->computerBoard->submarinosArray[i].posicion[j].posX = battleLabGameOriginal->computerBoard->submarinosArray[i].posicion[j].posX;
			battleLabGameCopia->computerBoard->submarinosArray[i].posicion[j].posY = battleLabGameOriginal->computerBoard->submarinosArray[i].posicion[j].posY;
		}
		battleLabGameCopia->computerBoard->submarinosArray[i].ship = battleLabGameOriginal->computerBoard->submarinosArray[i].ship;
		battleLabGameCopia->computerBoard->submarinosArray[i].estado = battleLabGameOriginal->computerBoard->submarinosArray[i].estado;
		battleLabGameCopia->computerBoard->submarinosArray[i].numPosLibres = battleLabGameOriginal->computerBoard->submarinosArray[i].numPosLibres;
		battleLabGameCopia->computerBoard->submarinosArray[i].numPosImpactadas = battleLabGameOriginal->computerBoard->submarinosArray[i].numPosImpactadas;
	}
}

void copiarPatrullerosHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco)
{
	int i,j;
	for(i=0; i<cantidadBarcos; i++)
	{	
		for(j=0; j<medidaBarco; j++)
		{	
			battleLabGameCopia->humanBoardTeam->patrullerosArray[i].posicion[j].posX = battleLabGameOriginal->humanBoardTeam->patrullerosArray[i].posicion[j].posX;
			battleLabGameCopia->humanBoardTeam->patrullerosArray[i].posicion[j].posY = battleLabGameOriginal->humanBoardTeam->patrullerosArray[i].posicion[j].posY;
		}
		battleLabGameCopia->humanBoardTeam->patrullerosArray[i].ship = battleLabGameOriginal->humanBoardTeam->patrullerosArray[i].ship;
		battleLabGameCopia->humanBoardTeam->patrullerosArray[i].estado = battleLabGameOriginal->humanBoardTeam->patrullerosArray[i].estado;
		battleLabGameCopia->humanBoardTeam->patrullerosArray[i].numPosLibres = battleLabGameOriginal->humanBoardTeam->patrullerosArray[i].numPosLibres;
		battleLabGameCopia->humanBoardTeam->patrullerosArray[i].numPosImpactadas = battleLabGameOriginal->humanBoardTeam->patrullerosArray[i].numPosImpactadas;
	}
}

void copiarPatrullerosMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco)
{
	int i,j;
	for(i=0; i<cantidadBarcos; i++)
	{	
		for(j=0; j<medidaBarco; j++)
		{	
			battleLabGameCopia->computerBoard->patrullerosArray[i].posicion[j].posX = battleLabGameOriginal->computerBoard->patrullerosArray[i].posicion[j].posX;
			battleLabGameCopia->computerBoard->patrullerosArray[i].posicion[j].posY = battleLabGameOriginal->computerBoard->patrullerosArray[i].posicion[j].posY;
		}
		battleLabGameCopia->computerBoard->patrullerosArray[i].ship = battleLabGameOriginal->computerBoard->patrullerosArray[i].ship;
		battleLabGameCopia->computerBoard->patrullerosArray[i].estado = battleLabGameOriginal->computerBoard->patrullerosArray[i].estado;
		battleLabGameCopia->computerBoard->patrullerosArray[i].numPosLibres = battleLabGameOriginal->computerBoard->patrullerosArray[i].numPosLibres;
		battleLabGameCopia->computerBoard->patrullerosArray[i].numPosImpactadas = battleLabGameOriginal->computerBoard->patrullerosArray[i].numPosImpactadas;
	}
}

void copiarBonusHumano(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco)
{
	int i,j;
	for(i=0; i<cantidadBarcos; i++)
	{	
		for(j=0; j<medidaBarco; j++)
		{	
			battleLabGameCopia->humanBoardTeam->bonusArray[i].posicion[j].posX = battleLabGameOriginal->humanBoardTeam->bonusArray[i].posicion[j].posX;
			battleLabGameCopia->humanBoardTeam->bonusArray[i].posicion[j].posY = battleLabGameOriginal->humanBoardTeam->bonusArray[i].posicion[j].posY;
		}
		battleLabGameCopia->humanBoardTeam->bonusArray[i].ship = battleLabGameOriginal->humanBoardTeam->bonusArray[i].ship;
		battleLabGameCopia->humanBoardTeam->bonusArray[i].estado = battleLabGameOriginal->humanBoardTeam->bonusArray[i].estado;
		battleLabGameCopia->humanBoardTeam->bonusArray[i].numPosLibres = battleLabGameOriginal->humanBoardTeam->bonusArray[i].numPosLibres;
		battleLabGameCopia->humanBoardTeam->bonusArray[i].numPosImpactadas = battleLabGameOriginal->humanBoardTeam->bonusArray[i].numPosImpactadas;
	}
}

void copiarBonusMaquina(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia, int cantidadBarcos, int medidaBarco)
{
	int i,j;
	for(i=0; i<cantidadBarcos; i++)
	{	
		for(j=0; j<medidaBarco; j++)
		{	
			battleLabGameCopia->computerBoard->bonusArray[i].posicion[j].posX = battleLabGameOriginal->computerBoard->bonusArray[i].posicion[j].posX;
			battleLabGameCopia->computerBoard->bonusArray[i].posicion[j].posY = battleLabGameOriginal->computerBoard->bonusArray[i].posicion[j].posY;
		}
		battleLabGameCopia->computerBoard->bonusArray[i].ship = battleLabGameOriginal->computerBoard->bonusArray[i].ship;
		battleLabGameCopia->computerBoard->bonusArray[i].estado = battleLabGameOriginal->computerBoard->bonusArray[i].estado;
		battleLabGameCopia->computerBoard->bonusArray[i].numPosLibres = battleLabGameOriginal->computerBoard->bonusArray[i].numPosLibres;
		battleLabGameCopia->computerBoard->bonusArray[i].numPosImpactadas = battleLabGameOriginal->computerBoard->bonusArray[i].numPosImpactadas;
	}
}

void copiarColaEquipo(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia)
{
	battleLabGameCopia->pColaEquipo = crearCola();
	player_t * playerActual;
	player_t * copiaPlayer;
	playerActual = (player_t*)malloc(sizeof(player_t));
	playerActual->playerName = malloc(sizeof(char*)*15);
	copiaPlayer = (player_t*)malloc(sizeof(player_t));
	copiaPlayer->playerName = malloc(sizeof(char*)*15);
	nodoCola_t * pNodoAux = (nodoCola_t*)malloc(sizeof(nodoCola_t));
	pNodoAux = battleLabGameOriginal->pColaEquipo->pInicioCola;
	do
	{
		playerActual = peekCola(battleLabGameOriginal->pColaEquipo);
		copiaPlayer->team = playerActual->team;
		copiaPlayer->numPlayer = playerActual->numPlayer;
		copiaPlayer->playerName = playerActual->playerName;
		copiaPlayer->score = playerActual->score;
		copiaPlayer->pierdeTurno = playerActual->pierdeTurno;
		copiaPlayer->aciertoTurnoAnt = playerActual->aciertoTurnoAnt;
		pushCola(battleLabGameCopia->pColaEquipo, copiaPlayer);
		battleLabGameOriginal->pColaEquipo->pInicioCola = battleLabGameOriginal->pColaEquipo->pInicioCola->pSgte;
	}while(battleLabGameOriginal->pColaEquipo->pInicioCola != NULL);
	battleLabGameOriginal->pColaEquipo->pInicioCola = pNodoAux;
}

void copiarTodo(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia)
{	
	// hace el llamado de todas las funciones para generar la copia del juego
	copiarInfoPlayer(battleLabGameOriginal, battleLabGameCopia);
	copiarInfoEquipoHumano(battleLabGameOriginal, battleLabGameCopia);
	copiarInfoEquipoMaquina(battleLabGameOriginal, battleLabGameCopia);
	copiarBoardEquipoHumano(battleLabGameOriginal, battleLabGameCopia);
	copiarBoardEquipoMaquina(battleLabGameOriginal, battleLabGameCopia);
	copiarColaEquipo(battleLabGameOriginal, battleLabGameCopia);
	battleLabGameCopia->isEnd = battleLabGameOriginal->isEnd;
	battleLabGameCopia->tiroDeGracia = battleLabGameCopia->tiroDeGracia;
	battleLabGameCopia->foundBonus = battleLabGameOriginal->foundBonus;
	battleLabGameCopia->modoDebug = battleLabGameOriginal->modoDebug;
}

pBattleLabGame_t * deshacerJugada(pila_t * pilaJugadas)
{
	popPila(pilaJugadas);
	return peekPila(pilaJugadas);
}

int verificarPierdeTurno(cola_t * pCola)
{
	if(pCola->pInicioCola->player->pierdeTurno == 1)
	{
		pCola->pInicioCola->player->pierdeTurno = 0;
		return 1;
	}
   return 0;
	
}

void actualizarTurno(cola_t * pCola)
{
	pushCola(pCola, pCola->pInicioCola->player);
	popCola(pCola);
}

void encolarJugadores(cola_t * pCola, teamPlayers_t * team)
{	
	int i;
	for(i=0; i<team->numberOfPlayers; i++)
	{	
		pushCola(pCola, &team->playersArray[i]);
	}
}

void deshacer(pila_t * pilaJugadas, pBattleLabGame_t * battleLabGameOriginal)
{
	//int deshacer; // variable booleana que permite verificar el deshacer jugadas
	pBattleLabGame_t * battleLabGameCopia = (pBattleLabGame_t*)malloc(sizeof(pBattleLabGame_t));

	if(esPilaVacia(pilaJugadas)) // Si la pila de jugadas no es vacia, permite deshacer una jugada
	{
		battleLabGameCopia = deshacerJugada(pilaJugadas); // deshace la ultima jugada, es equivalente al popPila
		actualizarStructOriginal(battleLabGameOriginal, battleLabGameCopia);
	}
	else
	{
		printf("No se pueden deshacer mas jugadas, este el turno inicial.\n");
	}
}

void actualizarStructOriginal(pBattleLabGame_t * battleLabGameOriginal, pBattleLabGame_t * battleLabGameCopia)
{
	battleLabGameOriginal->currentPlayer = battleLabGameCopia->currentPlayer;
	battleLabGameOriginal->humanPlayersTeam = battleLabGameCopia->humanPlayersTeam;
	battleLabGameOriginal->computerTeam = battleLabGameCopia->computerTeam;
	battleLabGameOriginal->humanBoardTeam = battleLabGameCopia->humanBoardTeam;
	battleLabGameOriginal->computerBoard = battleLabGameCopia->computerBoard;
	battleLabGameOriginal->pColaEquipo = battleLabGameCopia->pColaEquipo;
}

void cambiarEstadoBarco(battleBoard_t * board, int tipoBarco, int posX, int posY, player_t * playerActual)
{
	int i,j;
	int encontrado = 0;
	switch(tipoBarco)
	{
		case 2:
			for(i=0; i<4 && encontrado == 0; i++)
			{
				if(board->portaAvionesArray[0].posicion[i].posX == posX && board->portaAvionesArray[0].posicion[i].posY == posY)
				{
					board->portaAvionesArray[0].numPosImpactadas++;
					board->portaAvionesArray[0].numPosLibres--;
					if(board->portaAvionesArray[0].numPosImpactadas == 4)
					{
						playerActual->score += 5;
						board->portaAvionesArray[0].estado = HUNDIDO;
						printf("Este portaAviones ha sido hundido.\n");
						encontrado = 1;
					}
					else
					{
						board->portaAvionesArray[0].estado = AVERIADO;
						encontrado = 1;
					}
					
				}
			}
			break;
		case 3:
			for(i=0; i<2 && encontrado == 0; i++)
			{
				for(j=0; j<3 && encontrado == 0; j++)
				{
					if(board->buquesArray[i].posicion[j].posX == posX && board->buquesArray[i].posicion[j].posY == posY)
					{
						board->buquesArray[i].numPosImpactadas++;
						board->buquesArray[i].numPosLibres--;
						if(board->buquesArray[i].numPosImpactadas == 3)
						{
							playerActual->score += 5;
							board->buquesArray[i].estado = HUNDIDO;
							printf("Este buque ha sido hundido.\n");
							encontrado = 1;
						}
						else
						{
							board->buquesArray[i].estado = AVERIADO;
							encontrado = 1;
						}
						
					}
				}
			}
			break;
		case 4:
			for(i=0; i<3 && encontrado == 0; i++)
			{
				for(j=0; j<2 && encontrado == 0; j++)
				{
					if(board->submarinosArray[i].posicion[j].posX == posX && board->submarinosArray[i].posicion[j].posY == posY)
					{
						board->submarinosArray[i].numPosImpactadas++;
						board->submarinosArray[i].numPosLibres--;
						if(board->submarinosArray[i].numPosImpactadas == 2)
						{
							playerActual->score += 5;
							board->submarinosArray[i].estado = HUNDIDO;
							printf("Este submarino ha sido hundido.\n");
							encontrado = 1;
						}
						else
						{
							board->submarinosArray[i].estado = AVERIADO;
							encontrado = 1;
						}
						
					}
				}
			}
			break;
		case 5:
			for(i=0; i<4 && encontrado == 0; i++)
			{
				if(board->patrullerosArray[i].posicion[0].posX == posX && board->patrullerosArray[i].posicion[0].posY == posY)
				{
					playerActual->score += 5;
					board->patrullerosArray[i].numPosImpactadas++;
					board->patrullerosArray[i].numPosLibres--;
					board->patrullerosArray[i].estado = HUNDIDO;
					printf("Este patrullero ha sido hundido.\n");
					encontrado = 1;
				}
				
			}
			break;
	}
}

nodoArbolN_t* generarNuevaRaiz(nodoArbolN_t* pArbolActual, int posHijo){
	int i;
	for(i = 0; i < pArbolActual->numHijos ; ++i){
		if(i == posHijo){
			return pArbolActual->pHijos->pHijo;
		}
		pArbolActual-> pHijos = pArbolActual->pHijos->pSgte;
	}
}

void disparoMaquina(pBattleLabGame_t * battleLabGameOriginal,pila_t* pilaJugadas)
{	
	int posX, posY;
	posX = battleLabGameOriginal->pArbolActual->nuevoDisparo->posX;
	posY = battleLabGameOriginal->pArbolActual->nuevoDisparo->posY;
	pBattleLabGame_t * battleLabGameCopia;
	battleLabGameCopia = (pBattleLabGame_t*)malloc(sizeof(pBattleLabGame_t));
	switch(battleLabGameOriginal->humanBoardTeam->ownBoard[posX][posY])
	{
		case 1:
			battleLabGameOriginal->humanBoardTeam->ownBoard[posX][posY] = 11;
			battleLabGameOriginal->computerBoard->opponentBoard[posX][posY] = 102;
			battleLabGameOriginal->computerTeam->numeroDisparos++;
			break;
		case 2:
			battleLabGameOriginal->humanBoardTeam->ownBoard[posX][posY] = 21;
			battleLabGameOriginal->computerBoard->opponentBoard[posX][posY] = 101;
			battleLabGameOriginal->computerTeam->numeroDisparos++;
			battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas++;
			battleLabGameOriginal->computerTeam->playersArray[0].score+=1;
			//battleLabGameOriginal->pArbolActual->nuevoDisparo->impacto = 1;
			cambiarEstadoBarco(battleLabGameOriginal->humanBoardTeam, 2, posX, posY, &battleLabGameOriginal->computerTeam->playersArray[0]);
			break;
		case 3:
			battleLabGameOriginal->humanBoardTeam->ownBoard[posX][posY] = 31;
			battleLabGameOriginal->computerBoard->opponentBoard[posX][posY] = 101;
			battleLabGameOriginal->computerTeam->numeroDisparos++;
			battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas++;
			battleLabGameOriginal->computerTeam->playersArray[0].score+=1;
			//battleLabGameOriginal->pArbolActual->nuevoDisparo->impacto = 1;
			cambiarEstadoBarco(battleLabGameOriginal->humanBoardTeam, 3, posX, posY, &battleLabGameOriginal->computerTeam->playersArray[0]);
			break;
		case 4:
			battleLabGameOriginal->humanBoardTeam->ownBoard[posX][posY] = 41;
			battleLabGameOriginal->computerBoard->opponentBoard[posX][posY] = 101;
			battleLabGameOriginal->computerTeam->numeroDisparos++;
			battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas++;
			battleLabGameOriginal->computerTeam->playersArray[0].score+=1;
			//battleLabGameOriginal->pArbolActual->nuevoDisparo->impacto = 1;
			cambiarEstadoBarco(battleLabGameOriginal->humanBoardTeam, 4, posX, posY, &battleLabGameOriginal->computerTeam->playersArray[0]);
			break;
		case 5:
			battleLabGameOriginal->humanBoardTeam->ownBoard[posX][posY] = 51;
			battleLabGameOriginal->computerBoard->opponentBoard[posX][posY] = 101;
			battleLabGameOriginal->computerTeam->numeroDisparos++;
			battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas++;
			battleLabGameOriginal->computerTeam->playersArray[0].score+=4;
			//battleLabGameOriginal->pArbolActual->nuevoDisparo->impacto = 1;
			cambiarEstadoBarco(battleLabGameOriginal->humanBoardTeam, 5, posX, posY, &battleLabGameOriginal->computerTeam->playersArray[0]);
			break;
		case 6:
			battleLabGameOriginal->humanBoardTeam->ownBoard[posX][posY] = 61;
			quitarBonusImpactadoYUbicarbarco(battleLabGameOriginal->computerBoard,battleLabGameOriginal->computerTeam->team);
			battleLabGameOriginal->computerBoard->opponentBoard[posX][posY] = 101;
			battleLabGameOriginal->humanBoardTeam->bonusArray[0].estado = HUNDIDO;
			battleLabGameOriginal->foundBonus = 1;
			battleLabGameOriginal->computerTeam->numeroDisparos++;
			battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas++;
			battleLabGameOriginal->computerTeam->playersArray[0].score+=10;
			break;	
	}
	copiarTodo(battleLabGameOriginal, battleLabGameCopia);
	pushPila(pilaJugadas, battleLabGameCopia);
}

void crearPosiblesDisparos(pBattleLabGame_t * battleLabGameOriginal, int verificadorHijos)
{	
	int disparoCorrecto = 0;
	int posX, posY;
	int terceraCondicion = 0;
	posX = battleLabGameOriginal->pArbolActual->nuevoDisparo->posX;
	posY = battleLabGameOriginal->pArbolActual->nuevoDisparo->posY;
	
	if(battleLabGameOriginal->humanBoardTeam->portaAvionesLibres > 0 || battleLabGameOriginal->humanBoardTeam->buquesLibres > 0 && verificadorHijos == 0)
	{	
		terceraCondicion++;
		if(posX + 3 < 10 && verificarDisparoCorrecto(battleLabGameOriginal, posX+3, posY))
		{
			disparo_t * nuevoDisparo = (disparo_t*)malloc(sizeof(disparo_t));
			nuevoDisparo->posX = battleLabGameOriginal->pArbolActual->nuevoDisparo->posX+3;
			nuevoDisparo->posY = battleLabGameOriginal->pArbolActual->nuevoDisparo->posY;
			battleLabGameOriginal->pArbolActual = insertarNodo(battleLabGameOriginal->pArbolActual, nuevoDisparo);			
		}
		if(posY + 3 < 10 && verificarDisparoCorrecto(battleLabGameOriginal, posX, posY+3))
		{
			disparo_t * nuevoDisparo = (disparo_t*)malloc(sizeof(disparo_t));
			nuevoDisparo->posX = battleLabGameOriginal->pArbolActual->nuevoDisparo->posX;
			nuevoDisparo->posY = battleLabGameOriginal->pArbolActual->nuevoDisparo->posY+3;
			battleLabGameOriginal->pArbolActual = insertarNodo(battleLabGameOriginal->pArbolActual, nuevoDisparo);			
		}
		if(posX - 3 >= 0 && verificarDisparoCorrecto(battleLabGameOriginal, posX-3, posY))
		{
			disparo_t * nuevoDisparo = (disparo_t*)malloc(sizeof(disparo_t));
			nuevoDisparo->posX = battleLabGameOriginal->pArbolActual->nuevoDisparo->posX-3;
			nuevoDisparo->posY = battleLabGameOriginal->pArbolActual->nuevoDisparo->posY;
			battleLabGameOriginal->pArbolActual = insertarNodo(battleLabGameOriginal->pArbolActual, nuevoDisparo);			
		}
		if(posY - 3 >= 0 && verificarDisparoCorrecto(battleLabGameOriginal, posX, posY-3))
		{
			disparo_t * nuevoDisparo = (disparo_t*)malloc(sizeof(disparo_t));
			nuevoDisparo->posX = battleLabGameOriginal->pArbolActual->nuevoDisparo->posX;
			nuevoDisparo->posY = battleLabGameOriginal->pArbolActual->nuevoDisparo->posY-3;
			battleLabGameOriginal->pArbolActual = insertarNodo(battleLabGameOriginal->pArbolActual, nuevoDisparo);			
		}
	}
	else if(((battleLabGameOriginal->humanBoardTeam->portaAvionesLibres == 0 && battleLabGameOriginal->humanBoardTeam->buquesLibres == 0) && (
 			battleLabGameOriginal->humanBoardTeam->submarinosLibres > 0)) || verificadorHijos == 1)
	{
		terceraCondicion++;
		if(posX + 2 < 10 && verificarDisparoCorrecto(battleLabGameOriginal, posX+2, posY))
		{
			disparo_t * nuevoDisparo = (disparo_t*)malloc(sizeof(disparo_t));
			nuevoDisparo->posX = battleLabGameOriginal->pArbolActual->nuevoDisparo->posX+2;
			nuevoDisparo->posY = battleLabGameOriginal->pArbolActual->nuevoDisparo->posY;
			battleLabGameOriginal->pArbolActual = insertarNodo(battleLabGameOriginal->pArbolActual, nuevoDisparo);			
		}
		if(posY + 2 < 10 && verificarDisparoCorrecto(battleLabGameOriginal, posX, posY+2))
		{
			disparo_t * nuevoDisparo = (disparo_t*)malloc(sizeof(disparo_t));
			nuevoDisparo->posX = battleLabGameOriginal->pArbolActual->nuevoDisparo->posX;
			nuevoDisparo->posY = battleLabGameOriginal->pArbolActual->nuevoDisparo->posY+2;
			battleLabGameOriginal->pArbolActual = insertarNodo(battleLabGameOriginal->pArbolActual, nuevoDisparo);			
		}
		if(posX - 2 >= 0 && verificarDisparoCorrecto(battleLabGameOriginal, posX-2, posY))
		{
			disparo_t * nuevoDisparo = (disparo_t*)malloc(sizeof(disparo_t));
			nuevoDisparo->posX = battleLabGameOriginal->pArbolActual->nuevoDisparo->posX-2;
			nuevoDisparo->posY = battleLabGameOriginal->pArbolActual->nuevoDisparo->posY;
			battleLabGameOriginal->pArbolActual = insertarNodo(battleLabGameOriginal->pArbolActual, nuevoDisparo);			
		}
		if(posY - 2 >= 0 && verificarDisparoCorrecto(battleLabGameOriginal, posX, posY-2))
		{
			disparo_t * nuevoDisparo = (disparo_t*)malloc(sizeof(disparo_t));
			nuevoDisparo->posX = battleLabGameOriginal->pArbolActual->nuevoDisparo->posX;
			nuevoDisparo->posY = battleLabGameOriginal->pArbolActual->nuevoDisparo->posY-2;
			battleLabGameOriginal->pArbolActual = insertarNodo(battleLabGameOriginal->pArbolActual, nuevoDisparo);			
		}		
	}
	else if((battleLabGameOriginal->humanBoardTeam->portaAvionesLibres == 0 || battleLabGameOriginal->humanBoardTeam->buquesLibres == 0 ||
 			battleLabGameOriginal->humanBoardTeam->submarinosLibres == 0 || battleLabGameOriginal->pArbolActual-> numHijos == 0) || terceraCondicion == 0)
	{
		do
		{
			posX = rand() % 10;
			posY = rand() % 10;
			if(verificarDisparoCorrecto(battleLabGameOriginal, posX, posY))
			{
				disparo_t * nuevoDisparo = (disparo_t*)malloc(sizeof(disparo_t));
				nuevoDisparo->posX = posX;
				nuevoDisparo->posY = posY;
				battleLabGameOriginal->pArbolActual = insertarNodo(battleLabGameOriginal->pArbolActual, nuevoDisparo);
				disparoCorrecto = 1;
			}
		}while(disparoCorrecto == 0);
	}
}

int verificarDisparoCorrecto(pBattleLabGame_t * battleLabGameOriginal, int posX, int posY)
{
	if(battleLabGameOriginal->computerBoard->opponentBoard[posX][posY] == 100)
		return 1;
	else
		return 0;
}

void imprimirInfoBarcos(barco_t * barcosArray, int cantidadBarcos, int medidaBarco)
{
	int i;
	if(cantidadBarcos == 1)
	{
		printf("\nInfo Porta Aviones: \n");
	}
	else if(cantidadBarcos == 2)
	{
		printf("\nInfo Buques: \n");
	}
	else if(cantidadBarcos == 3)
	{
		printf("\nInfo Submarinos: \n");
	}
	else if(cantidadBarcos == 4)
		printf("\nInfo Patrulleros: \n");

	for(i=0; i<cantidadBarcos; i++)
	{	
		if(barcosArray[i].estado == 2)
		{
			printf("El barco N° %d esta HUNDIDO.\n");
		}
		else if(barcosArray[i].estado == 1)
		{	
			printf("Su estado es AVERIADO.\n");
			printf("El barco N° %d esta a %d de ser hundido.\n", i+1 ,barcosArray[i].numPosLibres);
		}
		else
			printf("Su estado es HABILITADO y faltan %d tiros para hundirlo.\n", medidaBarco);
	}
}
