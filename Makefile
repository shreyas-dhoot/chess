chess: initialisechesspiece.o chessboard.o
	gcc initialisechesspiece.o chessboard.o -o chess -lcurses
initialisechesspiece.o: initialisechesspiece.c
	gcc -c initialisechesspiece.c
lastwalafinalchessboard.o: chessboard.c
	gcc -c chessboard.c
clean: 
	rm *.o chess
