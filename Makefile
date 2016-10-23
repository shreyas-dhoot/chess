chess: initialisechesspiece.o chessboard.o check_things.o future_moves.o check_checkmate.o
	gcc initialisechesspiece.o chessboard.o check_things.o future_moves.o check_checkmate.o -o chess -lncurses -lpanel
initialisechesspiece.o: initialisechesspiece.c
	gcc -c initialisechesspiece.c -g -Wall
chessboard.o: chessboard.c chess_declaration.h initialise.h functions_chess.h
	gcc -c chessboard.c -g -Wall
check_things.o: check_things.c
	gcc -c check_things.c -g -Wall
future_moves.o: future_moves.c
	gcc -c future_moves.c -g -Wall
check_checkmate.o: check_checkmate.c
	gcc -c check_checkmate.c -g -Wall
clean: 
	rm *.o chess
