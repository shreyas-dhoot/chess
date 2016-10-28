chess: initialisechesspiece.o chessboard.o check_things.o future_moves.o check_checkmate.o
	gcc initialisechesspiece.o chessboard.o check_things.o future_moves.o check_checkmate.o -o chess -lncurses -lpanel
initialisechesspiece.o: initialisechesspiece.c
	gcc -c initialisechesspiece.c -Wall
chessboard.o: chessboard.c chess_declaration.h initialise.h functions_chess.h
	gcc -c chessboard.c -Wall
check_things.o: check_things.c
	gcc -c check_things.c -Wall
future_moves.o: future_moves.c
	gcc -c future_moves.c -Wall
check_checkmate.o: check_checkmate.c
	gcc -c check_checkmate.c -Wall
clean: 
	rm *.o chess
