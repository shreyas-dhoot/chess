#include <string.h>
#include "chess_declaration.h"
#include "functions_chess.h"
int check_in_board(int i, int j) {				//Checking if (i, j) is a valid position or not
	if(i > 7 || i < 0 || j < 0 || j > 7)
		return 0;
	else
		return 1;
}

int check_chess_piece(int player, char *piece) {
	int i;
	if(player == 1) {
		for(i = 0; i < 16; i++) {
			if((strcmp(chess_piece[i], piece) == 0) || (strcmp(chess_piece[i], piece) == 32)) {
				return i;
			}
		}
		return -1;

	}
	else {
		for(i = 16; i < 32; i++) {
			if((strcmp(chess_piece[i], piece) == 0) || (strcmp(chess_piece[i], piece) == 32)) {
				return i;
			}
		}
		return -1;
	}
}

int generate_future_move(input *ip) {
	switch(ip -> enum_piece) {
		case 0: ip -> fm = future_move_rook(ip -> px, ip -> py, wr1.fm, pp);
				break;
		case 1: ip -> fm = future_move_knight(ip -> px, ip -> py, wn1.fm, pp);
				break;
		case 2: ip -> fm = future_move_bishop(ip -> px, ip -> py, wb1.fm, pp, 0, 1);
				break;
		case 3: ip -> fm = future_move_king(ip -> px, ip -> py, wk.fm, pp);
				break;
		case 4: ip -> fm = future_move_queen(ip -> px, ip -> py, wq.fm, pp);
				break;
		case 5: ip -> fm = future_move_bishop(ip -> px, ip -> py, wb2.fm, pp, 0, 1);
				break;
		case 6: ip -> fm = future_move_knight(ip -> px, ip -> py, wn2.fm, pp);
				break;
		case 7: ip -> fm = future_move_rook(ip -> px, ip -> py, wr2.fm, pp);
				break;
		case 8: ip -> fm = future_move_pawn(ip -> px, ip -> py, wp1.fm, pp);
				break;
		case 9: ip -> fm = future_move_pawn(ip -> px, ip -> py, wp2.fm, pp);
				break;
		case 10: ip -> fm = future_move_pawn(ip -> px, ip -> py, wp3.fm, pp);
				break;
		case 11: ip -> fm = future_move_pawn(ip -> px, ip -> py, wp4.fm, pp);
				break;
		case 12: ip -> fm = future_move_pawn(ip -> px, ip -> py, wp5.fm, pp);
				break;
		case 13: ip -> fm = future_move_pawn(ip -> px, ip -> py, wp6.fm, pp);
				break;
		case 14: ip -> fm = future_move_pawn(ip -> px, ip -> py, wp7.fm, pp);
				break;
		case 15: ip -> fm = future_move_pawn(ip -> px, ip -> py, wp8.fm, pp);
				break;
		case 16: ip -> fm = future_move_rook(ip -> px, ip -> py, br1.fm, pp);
				break;
		case 17: ip -> fm = future_move_knight(ip -> px, ip -> py, bn1.fm, pp);
				break;
		case 18: ip -> fm = future_move_bishop(ip -> px, ip -> py, bb1.fm, pp, 0, 1);
				break;
		case 19: ip -> fm = future_move_king(ip -> px, ip -> py, bk.fm, pp);
				break;
		case 20: ip -> fm = future_move_queen(ip -> px, ip -> py, bq.fm, pp);
				break;
		case 21: ip -> fm = future_move_bishop(ip -> px, ip -> py, bb2.fm, pp, 0, 1);
				break;
		case 22: ip -> fm = future_move_knight(ip -> px, ip -> py, bn2.fm, pp);
				break;
		case 23: ip -> fm = future_move_rook(ip -> px, ip -> py, br2.fm, pp);
				break;
		case 24: ip -> fm = future_move_pawn(ip -> px, ip -> py, bp1.fm, pp);
				break;
		case 25: ip -> fm = future_move_pawn(ip -> px, ip -> py, bp2.fm, pp);
				break;
		case 26: ip -> fm = future_move_pawn(ip -> px, ip -> py, bp3.fm, pp);
				break;
		case 27: ip -> fm = future_move_pawn(ip -> px, ip -> py, bp4.fm, pp);
				break;
		case 28: ip -> fm = future_move_pawn(ip -> px, ip -> py, bp5.fm, pp);
				break;
		case 29: ip -> fm = future_move_pawn(ip -> px, ip -> py, bp6.fm, pp);
				break;
		case 30: ip -> fm = future_move_pawn(ip -> px, ip -> py, bp7.fm, pp);
				break;
		case 31: ip -> fm = future_move_pawn(ip -> px, ip -> py, bp8.fm, pp);
				break;
		default: return 0;
	}
	return 1;
}


int check_chess_move(input *ip) {
	int i = 0;
	while((ip -> fm)[i][0] != -1) {
		if((ip -> fm)[i][0] == ((ip -> move)[0] - '0')) {
			if((ip -> fm)[i][1] == ((ip -> move)[1] - '0')) {
				return 1;
			}
		}
		i++;
	}
	return 0;
}
