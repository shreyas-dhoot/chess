#include "chess_declaration.h"
#include "functions_chess.h"
int check_checkmate_ifknight(int i, int j, input *ip, char ***pp) {
	if((check_in_board(i, j) && ip -> player == 1 && pp[i][j][0] == 'b' && pp [i][j][1] == 'n') || (check_in_board(i, j) && ip -> player == 0 && pp[i][j][0] == 'w' && pp [i][j][1] == 'n')) {
		return 1;
	}
	return 0;
}
int check(input *ip, char ***pp) {
	int kx, ky;
	char temp_piece[3];
	int i, j, enum_piece;
	if(ip -> player == 1) {
		kx = wk.cp[0]; 
		ky = wk.cp[1];
	}
	else {
		kx = bk.cp[0];
		ky = bk.cp[1];
	}
	if(check_checkmate_ifknight(kx + 2, ky + 1, ip, pp))
		return 1;
	if(check_checkmate_ifknight(kx + 2, ky - 1, ip, pp))
		return 1;
	if(check_checkmate_ifknight(kx - 2, ky + 1, ip, pp))
		return 1;
	if(check_checkmate_ifknight(kx - 2, ky - 1, ip, pp))
		return 1;
	if(check_checkmate_ifknight(kx + 1, ky + 2, ip, pp))
		return 1;
	if(check_checkmate_ifknight(kx - 1, ky + 2, ip, pp))
		return 1;
	if(check_checkmate_ifknight(kx + 1, ky - 2, ip, pp))
		return 1;
	if(check_checkmate_ifknight(kx - 1, ky - 2, ip, pp))
		return 1;
	for(i = kx - 1, j = ky + 1; i > -1 && j < 8; i--, j++) {
		if(pp[i][j][0] != '\0') {
			if((ip -> player == 1 && pp[i][j][0] == 'w') || (ip -> player == 0 && pp[i][j][0] == 'b'))
				break;
			temp_piece[0] = pp[i][j][1];
			if(pp[i][j][2] != '\0') {
				temp_piece[1] = pp[i][j][2];
				temp_piece[2] = '\0';
			}
			else
				temp_piece[1] = '\0';
			if(ip -> player == 1)
				enum_piece = check_chess_piece(0, temp_piece);
			else
				enum_piece = check_chess_piece(1, temp_piece);
			if((enum_piece >= 8 && enum_piece <= 15) && i == (kx - 1) ){
				return 1;
			}
			if(enum_piece == 18 || enum_piece == 20 || enum_piece == 21 || enum_piece == 2 || enum_piece == 4 || enum_piece == 5) {
				return 1;
			}
			break;
		}
	}

	for(i = kx - 1, j = ky - 1; i > -1 && j > -1; i--, j--) {
		if(pp[i][j][0] != '\0') {
			if((ip -> player == 1 && pp[i][j][0] == 'w') || (ip -> player == 0 && pp[i][j][0] == 'b'))
				break;
			temp_piece[0] = pp[i][j][1];
			if(pp[i][j][2] != '\0') {
				temp_piece[1] = pp[i][j][2];
				temp_piece[2] = '\0';
			}
			else
				temp_piece[1] = '\0';
			if(ip -> player == 1)
				enum_piece = check_chess_piece(0, temp_piece);
			else
				enum_piece = check_chess_piece(1, temp_piece);
			if((enum_piece >= 8 && enum_piece <= 15) && i == (kx - 1) ){
				return 1;
			}
			if(enum_piece == 18 || enum_piece == 20 || enum_piece == 21 || enum_piece == 2 || enum_piece == 4 || enum_piece == 5) {
				return 1;
			}
			break;
		}
	}
	for(i = kx + 1, j = ky - 1; i < 8 && j > -1; i++, j--) {
		if(pp[i][j][0] != '\0') {
			if((ip -> player == 1 && pp[i][j][0] == 'w') || (ip -> player == 0 && pp[i][j][0] == 'b'))
				break;
			temp_piece[0] = pp[i][j][1];
			if(pp[i][j][2] != '\0') {
				temp_piece[1] = pp[i][j][2];
				temp_piece[2] = '\0';
			}
			else
				temp_piece[1] = '\0';
			if(ip -> player == 1)
				enum_piece = check_chess_piece(0, temp_piece);
			else
				enum_piece = check_chess_piece(1, temp_piece);
			if((enum_piece >= 24 && enum_piece <= 31) && i == kx + 1 ){
				return 1;
			}
			if(enum_piece == 18 || enum_piece == 20 || enum_piece == 21 || enum_piece == 2 || enum_piece == 4 || enum_piece == 5) {
				return 1;
			}
			break;
		}
	}

	for(i = kx + 1, j = ky + 1; i < 8 && j < 8; i++, j++) {
	/*	printw("\nPlayer %d", ip -> player);
		printw("\nPiece at (%d, %d) is %s.", i, j, pp[i][j]);
		refresh();
		getch();*/
		if(pp[i][j][0] != '\0') {
			if((ip -> player == 1 && pp[i][j][0] == 'w') || (ip -> player == 0 && pp[i][j][0] == 'b'))
				break;
			temp_piece[0] = pp[i][j][1];
			if(pp[i][j][2] != '\0') {
				temp_piece[1] = pp[i][j][2];
				temp_piece[2] = '\0';
			}
			else
				temp_piece[1] = '\0';
			if(ip -> player == 1)
				enum_piece = check_chess_piece(0, temp_piece);
			else
				enum_piece = check_chess_piece(1, temp_piece);
			if(((enum_piece >= 24 && enum_piece <= 31) || (enum_piece >= 8 && enum_piece <= 15)) && i == kx + 1){
				return 1;
			}
			else if(enum_piece == 18 || enum_piece == 20 || enum_piece == 21 || enum_piece == 2 || enum_piece == 4 || enum_piece == 5) {
				return 1;
			}
			break;
		}
	}
	i = kx;
	for(j = ky + 1;j < 8;j++) {
		if(pp[i][j][0] != '\0') {
			if((ip -> player == 1 && pp[i][j][0] == 'w') || (ip -> player == 0 && pp[i][j][0] == 'b'))
				break;
			temp_piece[0] = pp[i][j][1];
			if(pp[i][j][2] != '\0') {
				temp_piece[1] = pp[i][j][2];
				temp_piece[2] = '\0';
			}
			else
				temp_piece[1] = '\0';
			if(ip -> player == 1)
				enum_piece = check_chess_piece(0, temp_piece);
			else
				enum_piece = check_chess_piece(1, temp_piece);
			if(enum_piece == 16 || enum_piece == 20 || enum_piece == 23 || enum_piece == 0 || enum_piece == 4 || enum_piece == 7) {
				return 1;
			}
			break;
		}
	}
	i = kx;
	for(j = ky - 1;j > -1;j--) {
		if(pp[i][j][0] != '\0') {
			if((ip -> player == 1 && pp[i][j][0] == 'w') || (ip -> player == 0 && pp[i][j][0] == 'b'))
				break;
			temp_piece[0] = pp[i][j][1];
			if(pp[i][j][2] != '\0') {
				temp_piece[1] = pp[i][j][2];
				temp_piece[2] = '\0';
			}
			else
				temp_piece[1] = '\0';
			if(ip -> player == 1)
				enum_piece = check_chess_piece(0, temp_piece);
			else
				enum_piece = check_chess_piece(1, temp_piece);
			if(enum_piece == 16 || enum_piece == 20 || enum_piece == 23 || enum_piece == 0 || enum_piece == 4 || enum_piece == 7) {
				return 1;
			}
			break;
		}
	}

	j = ky;
	for(i = kx - 1;i > -1;i--) {
		if(pp[i][j][0] != '\0') {
			if((ip -> player == 1 && pp[i][j][0] == 'w') || (ip -> player == 0 && pp[i][j][0] == 'b'))
				break;
			temp_piece[0] = pp[i][j][1];
			if(pp[i][j][2] != '\0') {
				temp_piece[1] = pp[i][j][2];
				temp_piece[2] = '\0';
			}
			else
				temp_piece[1] = '\0';
			if(ip -> player == 1)
				enum_piece = check_chess_piece(0, temp_piece);
			else
				enum_piece = check_chess_piece(1, temp_piece);
			if(enum_piece == 16 || enum_piece == 20 || enum_piece == 23 || enum_piece == 0 || enum_piece == 4 || enum_piece == 7) {
				return 1;
			}
			break;
		}
	}
	j = ky;
	for(i = kx + 1;i < 8;i++) {
		if(pp[i][j][0] != '\0') {
			if((ip -> player == 1 && pp[i][j][0] == 'w') || (ip -> player == 0 && pp[i][j][0] == 'b'))
				break;
		/*	printw("Future move when piece encountered: (%d, %d) ", temp_fmx, temp_fmy);
			printw(" Piece at (%d, %d) is %s", ip -> px, ip -> py, pp[ip -> px][ip -> px]);
			printw(" Virtually piece at (%d, %d) is %s.", temp_fmx, temp_fmy, pp[temp_fmx][temp_fmy]);
			printw(" i and j is %d and %d. ", i, j);
			getch();
			refresh();*/
			temp_piece[0] = pp[i][j][1];
			if(pp[i][j][2] != '\0') {
				temp_piece[1] = pp[i][j][2];
				temp_piece[2] = '\0';
			}
			else
				temp_piece[1] = '\0';
		//	printw("\nEncountered piece is %s.", temp_piece);
			if(ip -> player == 1)
				enum_piece = check_chess_piece(0, temp_piece);
			else
				enum_piece = check_chess_piece(1, temp_piece);
		//	printw("\nEnum of encountered piece is %d.", enum_piece);
		//	refresh();
		//	getch();
			if(enum_piece == 16 || enum_piece == 20 || enum_piece == 23 || enum_piece == 0 || enum_piece == 4 || enum_piece == 7) {
				return 1;
			}
			break;
		}
	}
	return 0;
}


