#include "BattleLab.h"
#include "Board.h"

int ** reservarMemoriaTablero()
{
	int ** tableroJugador;
	int i;
	tableroJugador=calloc(10,sizeof(int*)); // se reserva una matriz de 10 x 10

	if(tableroJugador!=NULL)
	{
		for(i=0; i<10; i++)
		{
			tableroJugador[i]=calloc(10,sizeof(int));
			if(tableroJugador == NULL)
			{
				printf("Error reservando memoria.\n");
				break;
			}
		}
	}
	else
	{
		printf("Error reservando memoria.\n");
	}

	return tableroJugador;
}

void verificarGanadorYTiroDeGracia(pBattleLabGame_t * battleLabGameOriginal, pila_t * pilaJugadas)
{
	if(battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas == 20 && battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas < 19 )
	{
		battleLabGameOriginal->isEnd = 1;
	}
	else if(battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas == 20 && battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas < 19 )
	{
		battleLabGameOriginal->isEnd = 1;
	}
	else if(battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas == 20 && battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas == 19)
	{
		battleLabGameOriginal->tiroDeGracia = 1;
	}
	else if(battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas == 20 && battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas == 19)
	{
		battleLabGameOriginal->tiroDeGracia = 1;

	}
	tiroDeGracia(battleLabGameOriginal, pilaJugadas);

}

void tiroDeGracia(pBattleLabGame_t * battleLabGameOriginal, pila_t * pilaJugadas)
{
	if(battleLabGameOriginal -> tiroDeGracia == 1)
	{
		if(battleLabGameOriginal->humanPlayersTeam->numeroPosicionesImpactadas == 19)
		{
			dispararEquipoHumano(battleLabGameOriginal, pilaJugadas);
		}
		else if(battleLabGameOriginal->computerTeam->numeroPosicionesImpactadas == 19)
		{
			disparoMaquina(battleLabGameOriginal, pilaJugadas);
		}
	}
}


battleBoard_t * crearTablerosEquipos(int ** MatrizJugador, int** MatrizOponente ){

	battleBoard_t* tableroJugadorUno; // se genera el tablero de un jugador

	tableroJugadorUno = (battleBoard_t*)malloc(sizeof(battleBoard_t)); // se le guarda memoria

	if(tableroJugadorUno==NULL){
		printf("No se pudo reservarMemoria\n");
	}

	// se crean las matrices de el tablero propio y de el tablero rival del equipo
	tableroJugadorUno->ownBoard = inicializarTableroEquipoUno(MatrizJugador); 

	tableroJugadorUno->opponentBoard = inicializarTableroOponente(MatrizOponente);

	tableroJugadorUno->portaAvionesLibres = 1;
	tableroJugadorUno->buquesLibres = 2;
	tableroJugadorUno->submarinosLibres = 3;
	tableroJugadorUno->patrullerosLibres = 4;
	tableroJugadorUno->bonusLibres = 1;

	return tableroJugadorUno;
}

void actualizarTablero(int ** MatrizJugador)
{
	int i,j;
	int letra;
	letra = 'A';
	printf("    ");
	for(i=1; i<11; i++) // se itera para ubicar los numeros del 1 al 10
	{
		printf("%d   ", i);
	}
	printf("\n\n");

	for (i=0; i<10; i++) // se itera para colocar las letras que van al lado izqueirdo e imprimir los datos de la matriz en la consola
	{
		printf("%c   ", letra);
		for(j=0; j<10; j++)
		{
			printf("%d   ", MatrizJugador[i][j]);
		}
		letra++;
		printf("\n\n");
	}
	printf("\n");

}



int** inicializarTableroEquipoUno(int ** MatrizJugador)
{
	// esta funcion realiza iteracion de la matriz a la que se le reservo memoria, incializandola con todos sus valores en 1
	int i,j;
	for (i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			MatrizJugador[i][j]=1;
		}
	}
	return MatrizJugador;

}

int** inicializarTableroOponente(int ** MatrizOponente)
{	
	// esta funcion realiza iteracion de la matriz a la que se le reservo memoria, incializandola con todos sus valores en 100

	int i,j;
	for (i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			MatrizOponente[i][j]=100;
		}
	}
	return MatrizOponente;

}

teamPlayers_t * crearEquipo()
{
	int i;
	int numberOfPlayers;
	teamPlayers_t * equipoHumano;

	equipoHumano=(teamPlayers_t*)malloc(sizeof(teamPlayers_t)); // se le reserva memoria a el equipo humano
	if(equipoHumano!=NULL)
	{
		// se llenan los datos necesarios de el equipo humano establecidos en el BattleLab.h
		equipoHumano->team = HUMAN;
		equipoHumano->effectivenessRate = 0;
		equipoHumano->numeroPosicionesImpactadas = 0;
		equipoHumano->numeroDisparos = 0;
		printf("Cuantos jugadores van a componer el equipo: \n");
		do
		{
			fflush(stdin);
			scanf("%2d", &numberOfPlayers);
			if(numberOfPlayers < 1)
			{
				printf("El numero de jugadores debe ser mayor a 0.\n");
			}
		}while(numberOfPlayers < 1);

		equipoHumano->numberOfPlayers = numberOfPlayers;
		player_t * playersArray = (player_t*)malloc(equipoHumano->numberOfPlayers *(sizeof(player_t)));

		if(playersArray!=NULL) // se crean los jugadores necesarios para la cantidad de jugadores del equipo
		{

			equipoHumano->playersArray = playersArray;

			fflush(stdin);
			for(i=0; i<equipoHumano->numberOfPlayers; i++) // se crean los jugadores necesarios para la cantidad de jugadores del equipo
			{
				player_t  player;
				player = crearJugardor();
				player.numPlayer = i+1;
				equipoHumano->playersArray[i] = player;
			}
		}
		else
		{
			printf("No se pudo reservar memoria para el arreglo de jugadores.\n");
		}
	}
	else
	{
		printf("No se pudo reservar memoria para el equipo.\n");
	}

	return equipoHumano;
}

teamPlayers_t * crearEquipoMaquina()
{
	teamPlayers_t * equipoMaquina;
	equipoMaquina = (teamPlayers_t*)malloc(sizeof(teamPlayers_t));
	equipoMaquina->playersArray = (player_t*)malloc(sizeof(player_t));
	equipoMaquina->playersArray[0] = crearJugardorMaquina();
	equipoMaquina->numberOfPlayers = 1;
	equipoMaquina->numeroPosicionesImpactadas= 0;
	equipoMaquina->numeroDisparos= 0;
	equipoMaquina->effectivenessRate = 0;
	equipoMaquina->team = COMPUTER;

	return equipoMaquina;
}

player_t crearJugardorMaquina()
{
	player_t jugadorMaquina;
	jugadorMaquina.team = COMPUTER;
	jugadorMaquina.playerName = malloc(sizeof(char*)*7);
	jugadorMaquina.playerName = "MAQUINA";
	jugadorMaquina.score = 0;
	jugadorMaquina.numPlayer = 0;

	return jugadorMaquina;
}

player_t crearJugardor()
{ 
	// crea un jugador y le llena los datos necesarios
	player_t jugador;

	jugador.team = HUMAN;
	jugador.playerName = malloc(sizeof(char)*15);
	printf("Ingrese el nombre del jugador:\n");
	fgets(jugador.playerName,15,stdin);
	fflush(stdin);
	jugador.score = 0;
	jugador.pierdeTurno = 0;
	jugador.aciertoTurnoAnt = 0;
	jugador.numPlayer = 0;

	return jugador;
}


void colocarBarcos(battleBoard_t * boardHumano)
{ // pone en la matriz que entra por parametros los barcos, llamando a la funcion ponerBarco

	ponerBarco( boardHumano, 1);
	ponerBarco( boardHumano, 2);			
	ponerBarco( boardHumano, 3);
	ponerBarco( boardHumano, 4);
	ponerBarco( boardHumano, 5);
}

void ponerBarco(battleBoard_t * boardHumano, int barco) 
{
	int i; // para iterar las matrices
	int medidaBarco; // casillas que ocupa el barco
	int cantidadBarcos; // numero de barcos a poner del mismo tipo
	int numeroBarco; // identificador de cada barco de 1 hasta 5
	switch(barco){

		case 1: // Porta Aviiones
			cantidadBarcos = 1;
			medidaBarco = 4;
			numeroBarco = 2;
			boardHumano->portaAvionesArray = (barco_t*)malloc(sizeof(barco_t));
			barco_t portaAviones = crearBarco(numeroBarco, medidaBarco);
			boardHumano->portaAvionesArray[0] = portaAviones;
			printf("En esta parte, su equipo colocará sus Porta Aviones.\n");
			printf("Recuerde que se coloca desde su posición ingresada hacia abajo si lo coloca en dirección vertical o hacia la derecha si lo coloca en dirección horizontal.\n");
			printf("Recuerde que este barco ocupa 4 casillas de su tablero y debe colocar 1 de ellos.\n");
			posicionarBarco(boardHumano, medidaBarco, numeroBarco, cantidadBarcos, boardHumano->portaAvionesArray, 1);
			break;
		case 2: // Buques
			cantidadBarcos = 2;
			medidaBarco = 3;
			numeroBarco = 3;
			boardHumano->buquesArray = (barco_t*)malloc(sizeof(barco_t)*2);
			for(i=0; i<cantidadBarcos; i++)
			{
				barco_t buque = crearBarco(numeroBarco, medidaBarco);
				boardHumano->buquesArray[i] = buque;
			}
			printf("En esta parte, su equipo colocará sus Buques.\n");
			printf("Recuerde que se coloca desde su posición ingresada hacia abajo si lo coloca en dirección vertical o hacia la derecha si lo coloca en dirección horizontal.\n");
			printf("Recuerde que este barco ocupa 3 casillas de su tablero y debe colocar 2 de ellos.\n");
			posicionarBarco(boardHumano, medidaBarco, numeroBarco, cantidadBarcos, boardHumano->buquesArray, 2);
			break;
		case 3: // Submarinos
			cantidadBarcos = 3;
			medidaBarco = 2;
			numeroBarco = 4;
			boardHumano->submarinosArray = (barco_t*)malloc(sizeof(barco_t)*3);
			for (i=0; i<cantidadBarcos; i++)
			{
				barco_t submarino = crearBarco(numeroBarco, medidaBarco);
				boardHumano->submarinosArray[i] = submarino;
			}
			printf("En esta parte, su equipo colocará sus Submarinos.\n");
			printf("Recuerde que se coloca desde su posición ingresada hacia abajo si lo coloca en dirección vertical o hacia la derecha si lo coloca en dirección horizontal.\n");
			printf("Recuerde que este barco ocupa 2 casillas de su tablero y debe colocar 3 de ellos.\n");
			posicionarBarco(boardHumano, medidaBarco, numeroBarco, cantidadBarcos, boardHumano->submarinosArray, 3);
			break;
		case 4: // Patrulleros
			cantidadBarcos = 4;
			medidaBarco = 1;
			numeroBarco = 5;
			boardHumano->patrullerosArray = (barco_t*)malloc(sizeof(barco_t)*4);
			for (i=0; i<cantidadBarcos; i++)
			{
				barco_t patrullero = crearBarco(numeroBarco, medidaBarco);
				boardHumano->patrullerosArray[i] = patrullero;
			}
			printf("En esta parte, su equipo colocará sus Patrulleros.\n");
			printf("Recuerde que este barco ocupa 1 casilla de su tablero y debe colocar 4 de ellos.\n");
			posicionarBarco(boardHumano, medidaBarco, numeroBarco, cantidadBarcos, boardHumano->patrullerosArray, 4);
			break;
		case 5: // Bonus
			cantidadBarcos = 1;
			medidaBarco = 1;
			numeroBarco = 6;
			boardHumano->bonusArray = (barco_t*)malloc(sizeof(barco_t));
			barco_t bonus = crearBarco(numeroBarco, medidaBarco);
			boardHumano->bonusArray[0] = bonus; 
			printf("En esta parte, su equipo colocará su Bonus.\n");
			printf("Recuerde que solo ocupa 1 casillas de su tablero y debe colocar 1 .\n");
			posicionarBarco(boardHumano, medidaBarco, numeroBarco, cantidadBarcos, boardHumano->bonusArray, 5);
			break;
	}
}

void ponerUnSoloBarco(battleBoard_t * boardHumano, int barco, int ubicacion) 
{ 
	int medidaBarco; // casillas que ocupa el barco
	int numeroBarco; // identificador de cada barco de 1 hasta 5
	switch(barco){

		case 1: // Porta Aviiones
			medidaBarco = 4;
			numeroBarco = 2;
			printf("En esta parte, su equipo colocará su Porta Aviones.\n");
			printf("Recuerde que se coloca desde su posición ingresada hacia abajo si lo coloca en dirección vertical o hacia la derecha si lo coloca en dirección horizontal.\n");
			printf("Recuerde que este barco ocupa 4 casillas de su tablero y debe colocar 1 de ellos.\n");
			posicionarUnSoloBarco(boardHumano, medidaBarco, numeroBarco,  boardHumano->portaAvionesArray, ubicacion, 1);
			break;
		case 2: // Buques
			medidaBarco = 3;
			numeroBarco = 3;
			printf("En esta parte, su equipo colocará su Buque.\n");
			printf("Recuerde que se coloca desde su posición ingresada hacia abajo si lo coloca en dirección vertical o hacia la derecha si lo coloca en dirección horizontal.\n");
			printf("Recuerde que este barco ocupa 3 casillas de su tablero y debe colocar 2 de ellos.\n");
			posicionarUnSoloBarco(boardHumano, medidaBarco, numeroBarco, boardHumano->buquesArray,ubicacion, 2);
			break;
		case 3: // Submarinos
			medidaBarco = 2;
			numeroBarco = 4;
			printf("En esta parte, su equipo colocará sus Submarinos.\n");
			printf("Recuerde que se coloca desde su posición ingresada hacia abajo si lo coloca en dirección vertical o hacia la derecha si lo coloca en dirección horizontal.\n");
			printf("Recuerde que este barco ocupa 2 casillas de su tablero y debe colocar 3 de ellos.\n");
			posicionarUnSoloBarco(boardHumano, medidaBarco, numeroBarco, boardHumano->submarinosArray,ubicacion, 3);
			break;
		case 4: // Patrulleros
			medidaBarco = 1;
			numeroBarco = 5;
			printf("En esta parte, su equipo colocará sus Patrulleros.\n");
			printf("Recuerde que este barco ocupa 1 casilla de su tablero y debe colocar 4 de ellos.\n");
			posicionarUnSoloBarco(boardHumano, medidaBarco, numeroBarco, boardHumano->patrullerosArray,ubicacion, 4);
			break;
	}
}

void posicionarUnSoloBarco(battleBoard_t * boardHumano, int medidaBarco, int numeroBarco, barco_t * barcosArray,int ubicacion, int barco)
{
	char posH; // posicion en horizontal desde la A hasta la J
	int posV; // posicion el vertical desde 1 hasta 10
	int dirB ; // la direccion del barco, 0 vertical 1 horizontal
	int puesto = 0;
	int colocar=1; // variable booleana para verificar si la posicion esta ocupada o no
	int posHInt;
	int i,j;

	do
	{ // se repite hasta que se hayan ingresado la cantidad de barcos requerida

		do
		{ // verificacion de la posicion del barco
			printf("Escriba la posicion en horizontal (letra en mayúscula) donde quiere ubicar el barco: \n");
			fflush(stdin);
			scanf("%c", &posH);

			printf("Escriba la posición en vertical (1 al 10) donde quiere ubicar el barco: \n");
			fflush(stdin);
			scanf("%d", &posV);

			if(posH < 65 || posH > 74 || posV < 1 || posV > 10)
			{
				printf("Esta ubicación se encuentra fuera del tablero.\n");
			}
		}while(posH < 65 || posH > 74 || posV < 1 || posV > 10);
		
		posHInt=posH-65;
		posV = posV-1;
		printf("Posicion Horizontal %d\n", posHInt);
		printf("Posicion vertical %d \n", posV);

		if(barco < 4)
		{
			do
			{ // verificacion de la orientacion del barco
				printf("En que dirección desea colocar el barco (0 Vertical o 1 Horizontal)\n");
				fflush(stdin);
				scanf("%d", &dirB);
				if(dirB < 0 || dirB > 2)
				{
					printf("Esta dirección es errónea.\n");
				}
			}while((dirB < 0 || dirB > 2));
		}

		if(dirB==0 && posHInt + medidaBarco <= 10) // verificacion de si el barco puede ubicarse en las casillas designadas
		{
			for(i=posHInt, j=0; j<medidaBarco && colocar==1; i++, j++)
			{
				if(!(boardHumano->ownBoard[i][posV]==1))
				{
					colocar=0;
					printf("Lo siento pero la casilla %c%d se encuentra ocupada.\n", i+65, posV+1);
				}
			}
			if(colocar==1)
			{
				for(i=posHInt, j=0; j<medidaBarco; i++, j++)
				{
					boardHumano->ownBoard[i][posV]= numeroBarco;
					barcosArray[ubicacion].posicion[j].posX = i;
					barcosArray[ubicacion].posicion[j].posY = posV;
				}
				puesto = 1;
				actualizarTablero(boardHumano->ownBoard);
			}
		}
		else if(dirB==0 && posHInt + medidaBarco > 10)
		{
			printf("Lo siento pero este barco no se puede colocar en esta posicion ya que se sale del tablero.\n");
		}
		else if(dirB==1 && posV + medidaBarco <= 10) // verificacion de si el barco puede ubicarse en las casillas designadas
		{
			for(i=posV, j=0; j < medidaBarco && colocar==1; i++, j++)
			{
				if(!(boardHumano->ownBoard[posHInt][i]==1))
				{
					colocar=0;
					printf("Lo siento pero la casilla %c%d se encuentra ocupada.\n", posH+65, i+1);
				}
			}
			if(colocar==1)
			{
				for(i=posV, j=0; j < medidaBarco; j++, i++)
				{
					boardHumano->ownBoard[posHInt][i]= numeroBarco;
					barcosArray[ubicacion].posicion[j].posX = posHInt;
					barcosArray[ubicacion].posicion[j].posY = i;
				}
				puesto = 1;
				actualizarTablero(boardHumano->ownBoard);
			}
			
		}
		else if(dirB==1 && posV + medidaBarco >= 10)
		{
			printf("Lo siento pero este barco no se puede colocar en esta posición ya que se sale del tablero.\n");
		}
	}while(puesto != 1);
}

void posicionarBarco(battleBoard_t * boardHumano, int medidaBarco, int numeroBarco, int cantidadBarcos, barco_t * barcosArray, int barco)
{
	char posH; // posicion en horizontal desde la A hasta la J
	int posV; // posicion el vertical desde 1 hasta 10
	int dirB ; // la direccion del barco, 0 vertical 1 horizontal
	int numB=0; // cantidad de barcos a poner
	int colocar=1; // variable booleana para verificar si la posicion esta ocupada o no
	int posHInt;
	int i,j;

	do
	{ // se repite hasta que se hayan ingresado la cantidad de barcos requerida
		do{
			do
			{ // verificacion de la posicion del barco
				printf("Escriba la posicion en horizontal (letra en mayúscula) donde quiere ubicar el barco: \n");
				fflush(stdin);
				scanf("%c", &posH);

				printf("Escriba la posición en vertical (1 al 10) donde quiere ubicar el barco: \n");
				fflush(stdin);
				scanf("%d", &posV);

				if(posH < 65 || posH > 74 || posV < 1 || posV > 10)
				{
					printf("Esta ubicación se encuentra fuera del tablero.\n");
				}
			}while(posH < 65 || posH > 74 || posV < 1 || posV > 10);
			
			posHInt=posH-65;
			posV = posV-1;
			printf("Posicion Horizontal %d\n", posHInt);
			printf("Posicion vertical %d \n", posV);

			if(barco < 4)
			{
				do
				{ // verificacion de la orientacion del barco
					printf("En que dirección desea colocar el barco (0 Vertical o 1 Horizontal)\n");
					fflush(stdin);
					scanf("%d", &dirB);
					if(dirB < 0 || dirB > 2)
					{
						printf("Esta dirección es errónea.\n");
					}
				}while((dirB < 0 || dirB > 2));
			}
			else
				dirB=0;
			if(verificarPosicionBarco(boardHumano, medidaBarco, posHInt, posV, dirB)==0)
			{
				printf("Este barco no puede ser colocado desde esta posicion. Ingrese los datos de nuevo.\n");
			}
		}while(verificarPosicionBarco(boardHumano, medidaBarco, posHInt, posV, dirB)==0);

		if(dirB==0 && posHInt + medidaBarco <= 10) // verificacion de si el barco puede ubicarse en las casillas designadas
		{
			for(i=posHInt, j=0; j<medidaBarco && colocar==1; i++, j++)
			{
				if(!(boardHumano->ownBoard[i][posV]==1))
				{
					colocar=0;
					printf("Lo siento pero la casilla %c%d se encuentra ocupada.\n", i+65, posV+1);
				}
			}
			if(colocar==1)
			{
				for(i=posHInt, j=0; j<medidaBarco; i++, j++)
				{
					boardHumano->ownBoard[i][posV]= numeroBarco;
					barcosArray[numB].posicion[j].posX = i;
					barcosArray[numB].posicion[j].posY = posV;
				}
				numB++;
				actualizarTablero(boardHumano->ownBoard);
			}
		}
		else if(dirB==0 && posHInt + medidaBarco > 10)
		{
			printf("Lo siento pero este barco no se puede colocar en esta posicion ya que se sale del tablero.\n");
		}
		else if(dirB==1 && posV + medidaBarco <= 10) // verificacion de si el barco puede ubicarse en las casillas designadas
		{
			for(i=posV, j=0; j < medidaBarco && colocar==1; i++, j++)
			{
				if(!(boardHumano->ownBoard[posHInt][i]==1))
				{
					colocar=0;
					printf("Lo siento pero la casilla %c%d se encuentra ocupada.\n", posH+65, i+1);
				}
			}
			if(colocar==1)
			{
				for(i=posV, j=0; j < medidaBarco; j++, i++)
				{
					boardHumano->ownBoard[posHInt][i]= numeroBarco;
					barcosArray[numB].posicion[j].posX = posHInt;
					barcosArray[numB].posicion[j].posY = i;
				}
				numB++;
				actualizarTablero(boardHumano->ownBoard);
			}
			
		}
		else if(dirB==1 && posV + medidaBarco >= 10)
		{
			printf("Lo siento pero este barco no se puede colocar en esta posición ya que se sale del tablero.\n");
		}
	}while(numB < cantidadBarcos);
}

void ponerBarcosMaquina(battleBoard_t * boardMaquina, int barco)
{	
	srand(time(NULL));
	int i;
	int posX, posY, dir;
	int medidaBarco; // casillas que ocupa el barco
	int cantidadBarcos; // numero de barcos a poner del mismo tipo
	int numeroBarco; // identificador de cada barco de 1 hasta 5
	int barcoPuesto;
	int puesto = 0;
	int numB = 0;
	switch(barco)
	{
		case 1: // Porta Aviiones
			cantidadBarcos = 1;
			medidaBarco = 4;
			numeroBarco = 2;
			boardMaquina->portaAvionesArray = (barco_t*)malloc(sizeof(barco_t));
			barco_t portaAviones = crearBarco(numeroBarco, medidaBarco);
			boardMaquina->portaAvionesArray[0] = portaAviones;
			do
			{
				posX = rand() % 10;
				posY = rand() % 10;
				dir = rand() % 2;
				if(verificarPosicionBarco(boardMaquina, medidaBarco, posX, posY, dir) == 1)
				{
					posicionarBarcoMaquina(boardMaquina, boardMaquina->portaAvionesArray, medidaBarco, numeroBarco, posX, posY, dir, numB);
					numB++;
				}
			}while(numB < cantidadBarcos);
			break;
		case 2: // Buques
			cantidadBarcos = 2;
			medidaBarco = 3;
			numeroBarco = 3;
			boardMaquina->buquesArray = (barco_t*)malloc(sizeof(barco_t)*2);
			for(i=0; i<cantidadBarcos; i++)
			{
				barco_t buque = crearBarco(numeroBarco, medidaBarco);
				boardMaquina->buquesArray[i] = buque;
			}
			do
			{
				posX = rand() % 10;
				posY = rand() % 10;
				dir = rand() % 2;
				if(verificarPosicionBarco(boardMaquina, medidaBarco, posX, posY, dir) == 1)
				{
					posicionarBarcoMaquina(boardMaquina, boardMaquina->buquesArray, medidaBarco, numeroBarco, posX, posY, dir, numB);
					numB++;
				}
			}while(numB < cantidadBarcos);
			break;
		case 3: // Submarinos
			cantidadBarcos = 3;
			medidaBarco = 2;
			numeroBarco = 4;
			boardMaquina->submarinosArray = (barco_t*)malloc(sizeof(barco_t)*3);
			for (i=0; i<cantidadBarcos; i++)
			{
				barco_t submarino = crearBarco(numeroBarco, medidaBarco);
				boardMaquina->submarinosArray[i] = submarino;
			}
			do
			{
				posX = rand() % 10;
				posY = rand() % 10;
				dir = rand() % 2;
				if(verificarPosicionBarco(boardMaquina, medidaBarco, posX, posY, dir) == 1)
				{
					posicionarBarcoMaquina(boardMaquina, boardMaquina->submarinosArray, medidaBarco, numeroBarco, posX, posY, dir, numB);
					numB++;
				}
			}while(numB < cantidadBarcos);
			break;
		case 4: // Patrulleros
			cantidadBarcos = 4;
			medidaBarco = 1;
			numeroBarco = 5;
			boardMaquina->patrullerosArray = (barco_t*)malloc(sizeof(barco_t)*4);
			for (i=0; i<cantidadBarcos; i++)
			{
				barco_t patrullero = crearBarco(numeroBarco, medidaBarco);
				boardMaquina->patrullerosArray[i] = patrullero;
			}
			do
			{
				posX = rand() % 10;
				posY = rand() % 10;
				dir = rand() % 2;
				if(verificarPosicionBarco(boardMaquina, medidaBarco, posX, posY, dir) == 1)
				{
					posicionarBarcoMaquina(boardMaquina, boardMaquina->patrullerosArray, medidaBarco, numeroBarco, posX, posY, dir, numB);
					numB++;
				}
			}while(numB < cantidadBarcos);
			break;
		case 5: // Bonus
			cantidadBarcos = 1;
			medidaBarco = 1;
			numeroBarco = 6;
			boardMaquina->bonusArray = (barco_t*)malloc(sizeof(barco_t));
			barco_t bonus = crearBarco(numeroBarco, medidaBarco);
			boardMaquina->bonusArray[0] = bonus;
			do
			{
				posX = rand() % 10;
				posY = rand() % 10;
				dir = rand() % 2;
				if(verificarPosicionBarco(boardMaquina, medidaBarco, posX, posY, dir) == 1)
				{
					posicionarBarcoMaquina(boardMaquina, boardMaquina->bonusArray, medidaBarco, numeroBarco, posX, posY, dir, numB);
					numB++;
				}
			}while(numB < cantidadBarcos);
			break;
	}

}

int verificarPosicionBarco(battleBoard_t * boardMaquina, int medidaBarco, int posX, int posY, int dir)
{
	int i, j;
	if(dir == 0 && posX + medidaBarco < 10)
	{
		for(i=posX, j=0; j<medidaBarco; i++, j++)
		{
			if(boardMaquina->ownBoard[i][posY] != 1)
			{
				return 0;
			}
		}
		return 1;
	}
	else if(dir == 1 && posY + medidaBarco < 10)
	{
		for(i=posY, j=0; j<medidaBarco; i++, j++)
		{
			if(boardMaquina->ownBoard[posX][i] != 1)
			{
				return 0; 
			}
		}
		return 1;
	}
}

void ponerUnBarcoMaquina(battleBoard_t * boardMaquina, int barco, int ubicacion)
{	
	srand(time(NULL));
	int i = 0;
	int posX, posY, dir;
	int medidaBarco; // casillas que ocupa el barco
	int cantidadBarcos = 1; // numero de barcos a poner del mismo tipo
	int numeroBarco; // identificador de cada barco de 1 hasta 5
	int barcoPuesto = 0;
	int puesto = 0;
	int numB = 0;
	switch(barco)
	{
		case 1: // Porta Aviiones
			medidaBarco = 4;
			numeroBarco = 2;
			do
			{
				posX = rand() % 10;
				posY = rand() % 10;
				dir = rand() % 2;
				if(verificarPosicionBarco(boardMaquina, medidaBarco, posX, posY, dir) == 1)
				{
					posicionarBarcoMaquina(boardMaquina, boardMaquina->portaAvionesArray, medidaBarco, numeroBarco, posX, posY, dir, numB);
					barcoPuesto = 1;
				}
			}while(barcoPuesto != 1);
			break;
		case 2: // Buques
			medidaBarco = 3;
			numeroBarco = 3;
			do
			{
				posX = rand() % 10;
				posY = rand() % 10;
				dir = rand() % 2;
				if(verificarPosicionBarco(boardMaquina, medidaBarco, posX, posY, dir) == 1)
				{
					posicionarBarcoMaquina(boardMaquina, boardMaquina->buquesArray, medidaBarco, numeroBarco, posX, posY, dir, numB);
					barcoPuesto = 1;
				}
			}while(barcoPuesto != 1);
			break;
		case 3: // Submarinos
			medidaBarco = 2;
			numeroBarco = 4;
			do
			{
				posX = rand() % 10;
				posY = rand() % 10;
				dir = rand() % 2;
				if(verificarPosicionBarco(boardMaquina, medidaBarco, posX, posY, dir) == 1)
				{
					posicionarBarcoMaquina(boardMaquina, boardMaquina->submarinosArray, medidaBarco, numeroBarco, posX, posY, dir, numB);
					barcoPuesto = 1;
				}
			}while(barcoPuesto != 1);
			break;
		case 4: // Patrulleros
			medidaBarco = 1;
			numeroBarco = 5;
			do
			{
				posX = rand() % 10;
				posY = rand() % 10;
				dir = rand() % 2;
				if(verificarPosicionBarco(boardMaquina, medidaBarco, posX, posY, dir) == 1)
				{
					posicionarBarcoMaquina(boardMaquina, boardMaquina->patrullerosArray, medidaBarco, numeroBarco, posX, posY, dir, numB);
					barcoPuesto = 1;
				}
			}while(barcoPuesto != 1);
			break;
	}
}

void posicionarBarcoMaquina(battleBoard_t * boardMaquina, barco_t * barcosArray, int medidaBarco, int numeroBarco, int posX, int posY, int dir, int numBarco)
{	
	int i ,j;
	if(dir == 0 && posX + medidaBarco < 10)
	{
		for(i=posX, j=0; j<medidaBarco; i++, j++)
		{	
			if(boardMaquina->ownBoard[i][posY] == 1)
			{
				boardMaquina->ownBoard[i][posY] = numeroBarco;
				barcosArray[numBarco].posicion[j].posX = i;
				barcosArray[numBarco].posicion[j].posY = posY;
			}		
		}
	}
	else if(dir == 1 && posY + medidaBarco < 10)
	{
		for(i=posY, j=0; j<medidaBarco; i++, j++)
		{	
			if(boardMaquina->ownBoard[posX][i] == 1)
			{
				boardMaquina->ownBoard[posX][i] = numeroBarco;
				barcosArray[numBarco].posicion[j].posX = posX;
				barcosArray[numBarco].posicion[j].posY = i;
			}
		}
	}
}

void colocarBarcosMaquina(battleBoard_t * boardMaquina)
{	
	ponerBarcosMaquina(boardMaquina, 1);
	ponerBarcosMaquina(boardMaquina, 2);
	ponerBarcosMaquina(boardMaquina, 3);
	ponerBarcosMaquina(boardMaquina, 4);
	ponerBarcosMaquina(boardMaquina, 5);
	
}

barco_t crearBarco(int tipoBarco, int medidaBarco)
{
	if(tipoBarco == 2)
	{
		barco_t portaAviones;
		portaAviones.ship = tipoBarco;
		portaAviones.estado = 0;
		portaAviones.numPosLibres = medidaBarco;
		portaAviones.numPosImpactadas = 0;
		portaAviones.posicion = (posicion_t*)calloc(medidaBarco,sizeof(barco_t));
		return portaAviones;
	}
	else if(tipoBarco == 3)
	{
		barco_t buque;
		buque.ship = tipoBarco;
		buque.estado = 0;
		buque.numPosLibres = medidaBarco;
		buque.numPosImpactadas = 0;
		buque.posicion = (posicion_t*)calloc(medidaBarco,sizeof(barco_t));
		return buque;
	}
	else if(tipoBarco == 4)
	{
		barco_t submarino;
		submarino.ship = tipoBarco;
		submarino.estado = 0;
		submarino.numPosLibres = medidaBarco;
		submarino.numPosImpactadas = 0;
		submarino.posicion = (posicion_t*)calloc(medidaBarco,sizeof(barco_t));
		return submarino;		
	}
	else if (tipoBarco == 5)
	{
		barco_t patrullero;
		patrullero.ship = tipoBarco;
		patrullero.estado = 0;
		patrullero.numPosLibres = medidaBarco;
		patrullero.numPosImpactadas = 0;
		patrullero.posicion = (posicion_t*)calloc(medidaBarco,sizeof(barco_t));
		return patrullero;		
	}
	else if(tipoBarco == 6)
	{
		barco_t bonus;
		bonus.ship = tipoBarco;
		bonus.estado = 0;
		bonus.numPosLibres = medidaBarco;
		bonus.numPosImpactadas = 0;
		bonus.posicion = (posicion_t*)calloc(medidaBarco,sizeof(barco_t));
		return bonus;			
	}


}