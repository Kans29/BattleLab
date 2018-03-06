all: programaBattleLab

programaBattleLab: BattleLab.o Board.o MainBattleLab.o Stack.o Queue.o ArbolesNArios.o
	gcc -o Juego BattleLab.o Board.o MainBattleLab.o Stack.o Queue.o ArbolesNArios.o

Stack.o: Stack.c Stack.h BattleLab.h
	gcc -c Stack.c 

Board.o: Board.c BattleLab.h Board.h
	gcc -c Board.c

Queue.o: Queue.c Queue.h BattleLab.h
	gcc -c Queue.c

ArbolesNArios.o: ArbolesNArios.c ArbolesNArios.h BattleLab.h
	gcc -c ArbolesNArios.c

BattleLab.o: BattleLab.c BattleLab.h Queue.h Stack.h Board.h ArbolesNArios.h
	gcc -c BattleLab.c

MainBattleLab.o: MainBattleLab.c BattleLab.h Board.h Queue.h Stack.h ArbolesNArios.h
	gcc -c MainBattleLab.c





