#include "chess_declaration.h"
#include <string.h>
#include "functions_chess.h"
#include <stdlib.h>
#include <ncurses.h>
void store_future_move_king(int px, int py, int i, int j, int fm[][2], char ***pp) {
int k = fm[11][0];
	if(pp[i][j][0] == '\0' || pp[px][py][0] != pp[i][j][0]) {
		fm[k][0] = i;
		fm[k][1] = j;
		fm[11][0] = fm[11][0] + 1;
	}
}

void future_move_king(int px, int py, int fm[][2], char ***pp) {			//Input present co - ordinates of the piece
	fm[11][0] = 0;
	if(check_in_board(px + 1, py)) {
		store_future_move_king(px, py, px + 1, py, fm, pp);
	}
	if(check_in_board(px + 1, py + 1)) {
		store_future_move_king(px, py, px + 1, py + 1, fm, pp);
	}
	if(check_in_board(px, py + 1)) {
		store_future_move_king(px, py, px, py + 1, fm, pp);
	}
	if(check_in_board(px - 1, py + 1)) {
		store_future_move_king(px, py, px - 1, py + 1, fm, pp);
	}
	if(check_in_board(px - 1, py)) {
		store_future_move_king(px, py, px - 1, py, fm, pp);
	}
	if(check_in_board(px - 1, py - 1)) {
		store_future_move_king(px, py, px - 1, py - 1, fm, pp);
	}
	if(check_in_board(px, py - 1)) {
		store_future_move_king(px, py, px, py - 1, fm, pp);
	}
	if(check_in_board(px + 1, py - 1)) {
		store_future_move_king(px, py, px + 1, py - 1, fm, pp);
	}
}

void future_move_queen(int px, int py, int fm[][2], char ***pp) {
	int k = 0;				//Have to return k too.
	future_move_rook(px, py, fm, pp);
	k = fm[14][0];
	fm[14][0] = -1;
	future_move_bishop(px, py, fm, pp, k, 0);
	move(0,0);
}

void future_move_rook(int px, int py, int fm[][2], char ***pp) {
	int i, j, k = 0;
	j = py;
	for(i = px + 1; i < 8; i++) {
		if(pp[px][py][0] == pp[i][j][0])			//if same color piece
			break;
		else if(pp[i][j][0] == '\0') {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
		}
		else {							//if different color piece
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
			break;
		}
	}
	for(i = px - 1; i > -1; i--) {				//  down
		if(pp[px][py][0] == pp[i][j][0])		
			break;
		else if(pp[i][j][0] == '\0') {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
		}
		else {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
			break;
		}
	}
	i = px;
	for(j = py + 1; j < 8; j++) {				// -->
		if(pp[px][py][0] == pp[i][j][0])
			break;
		else if(pp[i][j][0] == '\0') {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
		}
		else  {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
			break;
		}
	}
	for(j = py - 1; j > -1; j--) {
		if(pp[px][py][0] == pp[i][j][0])
			break;
		else if(pp[i][j][0] == '\0') {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
		}
		else {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
			break;
		}
	}
	fm[14][0] = k;
}

void future_move_bishop(int px, int py, int fm[][2], char ***pp, int k, int isbishop) {		//Storing all the future moves of bishop in fm
	//There should be a condition where after every move it checks for a check.
	//Initialise fm than add to it.
	int i;
	int j;
	for(i = px + 1, j = py + 1;i < 8 && j < 8;i++, j++) {
		if(pp[px][py][0] == pp[i][j][0])				//Checking if bishop and the piece on p[i][j] has same color
			break;
		else if(pp[i][j][0] == '\0'){				//If there is no piece
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
		}
		else{						//If both are of different color
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
			break;
		}
	}
	for(i = px - 1, j = py - 1; i > -1 && j > -1;i--, j--) {
		if(pp[px][py][0] == pp[i][j][0])
			break;
		else if(pp[i][j][0] == '\0'){
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
		}
		else  {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
			break;
		}
		
	}
	for(i = px + 1, j = py - 1; i < 8 && j > -1; i++, j--) {
		if(pp[px][py][0] == pp[i][j][0])
			break;
		else if(pp[i][j][0] == '\0') {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
		}
		else {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
			break;
		}
	}
	for(i = px - 1, j = py + 1; i > -1 && j < 8; i--, j++) {
		if(pp[px][py][0] == pp[i][j][0])
			break;
		else if(pp[i][j][0] == '\0') {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
		}
		else {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
			break;
		}
	}
	if(isbishop){
		fm[13][0] = k;
	}
	else
		fm[26][0] = k;
}

void store_future_move_knight(int px, int py, int i, int j, int fm[][2], char ***pp) {
	int k = fm[8][0];
	if(pp[i][j][0] == '\0' || pp[px][py][0] != pp[i][j][0]) {
		fm[k][0] = i;
		fm[k][1] = j;
		(fm[8][0])++;
	}
}
void future_move_knight(int px, int py, int fm[][2], char ***pp) {
	fm[8][0] = 0;
	if(check_in_board(px + 1, py + 2)) {
		store_future_move_knight(px, py, px + 1, py + 2, fm, pp);
	}
	if(check_in_board(px + 2, py + 1)) {
		store_future_move_knight(px, py, px + 2, py + 1, fm, pp);
	}
	if(check_in_board(px + 2, py - 1)) {
		store_future_move_knight(px, py, px + 2, py - 1, fm, pp);
	}
	if(check_in_board(px + 1, py - 2)) {
		store_future_move_knight(px, py, px + 1, py - 2, fm, pp);
	}
	if(check_in_board(px - 1, py - 2)) {
		store_future_move_knight(px, py, px - 1, py - 2, fm, pp);
	}
	if(check_in_board(px - 2, py - 1)) {
		store_future_move_knight(px, py, px - 2, py - 1, fm, pp);
	}
	if(check_in_board(px - 2, py + 1)) {
		store_future_move_knight(px, py, px - 2, py + 1, fm, pp);
	}
	if(check_in_board(px - 1, py + 2)) {
		store_future_move_knight(px, py, px - 1, py + 2, fm, pp);
	}
	
}
void store_future_move_pawn(int px, int py, int i, int j, int fm[][2], char ***pp) {
	int k = fm[4][0];
	if(py == j) {
		if(pp[i][j][0] == '\0') {
			fm[k][0] = i;
			fm[k][1] = j;
			(fm[4][0])++;
		}
	}
	else {
		if(pp[px][py][0] != pp[i][j][0] && pp[i][j][0] != '\0') {
			fm[k][0] = i;
			fm[k][1] = j;
			(fm[4][0])++;
		}
	}
}

void future_move_pawn(int px, int py, int fm[][2], char ***pp, int player) {
	fm[4][0] = 0;
	if(player == 1){
		if(check_in_board(px + 1, py + 1)) {
			store_future_move_pawn(px, py, px + 1, py + 1, fm, pp);
		}
		if(check_in_board(px + 1, py)) {
			store_future_move_pawn(px, py, px + 1, py, fm, pp);
		}
		if(check_in_board(px + 1, py - 1)) {
			store_future_move_pawn(px, py, px + 1, py - 1, fm, pp);
		}
		if(px == 1) {
			if(pp[px + 2][py][0] == '\0' && pp[px + 1][py][0] == '\0') {
				int x = fm[4][0];
				fm[x][0] = px + 2;
				fm[x][1] = py;
				(fm[4][0])++;
			}
		}
	}
	else {
		if(check_in_board(px - 1, py - 1)) {
			store_future_move_pawn(px, py, px - 1, py - 1, fm, pp);
		}
		if(check_in_board(px - 1, py)) {
			store_future_move_pawn(px, py, px - 1, py, fm, pp);
		}
		if(check_in_board(px - 1, py + 1)) {
			store_future_move_pawn(px, py, px - 1, py + 1, fm, pp);
		}
		if(px == 6) {
			if(pp[px - 2][py][0] == '\0' && pp[px - 1][py][0] == '\0') {
				int x = fm[4][0];
				fm[x][0] = px - 2;
				fm[x][1] = py;
				(fm[4][0])++;
			}
		}
	}
}

int check_ifknight(int i, int j,int ifm, input *ip, char ***pp) {
	if((check_in_board(i, j) && ip -> player == 1 && pp[i][j][0] == 'b' && pp [i][j][1] == 'n') || (check_in_board(i, j) && ip -> player == 0 && pp[i][j][0] == 'w' && pp [i][j][1] == 'n')) {
		ip -> fm[ifm][0] = -2;
		ip -> fm[ifm][1] = -2;
		return 1;
	}
	return 0;
}

void check_before_turn(input *ip, char ***pp, int if_check_before_turn) {
	if(if_check_before_turn) {
		int ifm = 0, iflag = -1;
		char temp_killed_piece[4];
		int i, j, enum_piece;
		char temp_piece[4];
		int kx, ky;
		int temp_fmx, temp_fmy;
		while(ip -> fm[ifm][1] != -1) {
			pp[ip ->px][ip -> py][0] ='\0';
			temp_fmx = ip -> fm[ifm][0];
			temp_fmy = ip -> fm[ifm][1];
			temp_killed_piece[0] = '\0';
			if(pp[ip -> fm[ifm][0]][ip -> fm[ifm][1]][0] != '\0') {
				strcpy(temp_killed_piece, pp[ip -> fm[ifm][0]][ip -> fm[ifm][1]]);
				strcpy(pp[ip -> fm[ifm][0]][ip -> fm[ifm][1]],ip -> piece);
				temp_killed_piece[0] = temp_killed_piece[1];
				if(temp_killed_piece[2] == '\0')
					temp_killed_piece[1] = '\0';
				else{
					temp_killed_piece[1] = temp_killed_piece[2];
					temp_killed_piece[2] = '\0';
				}
				if(ip -> player == 1)
					iflag = check_chess_piece(0, temp_killed_piece);
				else
					iflag = check_chess_piece(1, temp_killed_piece);
				if(iflag == -1) {
					printw("Killed piece is %s", temp_killed_piece);
					refresh();
					getch();
				}
				chess_piece[iflag][0] = '\0';
			}
			else {
				strcpy(pp[ip -> fm[ifm][0]][ip -> fm[ifm][1]],ip -> piece);
			}
			if(ip -> piece[1] == 'k') {
				kx = temp_fmx;
				ky = temp_fmy;
			}
			else {
				if(ip -> player == 1) {
					kx = wk.cp[0]; 
					ky = wk.cp[1];
				}
				else {
					kx = bk.cp[0];
					ky = bk.cp[1];
				}
			}
				//check for knight
			i = kx + 2;
			j = ky + 1;
			if(check_ifknight(i, j, ifm, ip, pp))
				break;
			i = kx + 2;
			j = ky - 1;	
			if(check_ifknight(i, j, ifm, ip, pp))
				break;
			i = kx - 2;
			j = ky + 1;
			if(check_ifknight(i, j, ifm, ip, pp))
				break;
			i = kx - 2;
			j = ky - 1;
			if(check_ifknight(i, j, ifm, ip, pp))
				break;
			j = ky + 2;
			i = kx + 1;
			if(check_ifknight(i, j, ifm, ip, pp))
				break;
			j = ky + 2;
			i = kx - 1;
			if(check_ifknight(i, j, ifm, ip, pp))
				break;
			j = ky - 2;
			i = kx + 1;
			if(check_ifknight(i, j, ifm, ip, pp))
				break;
			j = ky - 2;
			i = kx - 1;
			if(check_ifknight(i, j, ifm, ip, pp))
				break;
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
						ip -> fm[ifm][0] = -2;
						ip -> fm[ifm][1] = -2;
					}
					if(enum_piece == 18 || enum_piece == 20 || enum_piece == 21 || enum_piece == 2 || enum_piece == 4 || enum_piece == 5) {
						ip -> fm[ifm][0] = -2;
						ip -> fm[ifm][1] = -2;
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
						ip -> fm[ifm][0] = -2;
						ip -> fm[ifm][1] = -2;
					}
					if(enum_piece == 18 || enum_piece == 20 || enum_piece == 21 || enum_piece == 2 || enum_piece == 4 || enum_piece == 5) {
						ip -> fm[ifm][0] = -2;
						ip -> fm[ifm][1] = -2;
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
						ip -> fm[ifm][0] = -2;
						ip -> fm[ifm][1] = -2;
					}
					if(enum_piece == 18 || enum_piece == 20 || enum_piece == 21 || enum_piece == 2 || enum_piece == 4 || enum_piece == 5) {
						ip -> fm[ifm][0] = -2;
						ip -> fm[ifm][1] = -2;
					}
					break;
				}
			}

			for(i = kx + 1, j = ky + 1; i < 8 && j < 8; i++, j++) {
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
						ip -> fm[ifm][0] = -2;
						ip -> fm[ifm][1] = -2;
					}
					else if(enum_piece == 18 || enum_piece == 20 || enum_piece == 21 || enum_piece == 2 || enum_piece == 4 || enum_piece == 5) {
						ip -> fm[ifm][0] = -2;
						ip -> fm[ifm][1] = -2;
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
						ip -> fm[ifm][0] = -2;
						ip -> fm[ifm][1] = -2;
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
						ip -> fm[ifm][0] = -2;
						ip -> fm[ifm][1] = -2;
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
						ip -> fm[ifm][0] = -2;
						ip -> fm[ifm][1] = -2;
					}
					break;
				}
			}
			j = ky;
			for(i = kx + 1;i < 8;i++) {
				
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
						ip -> fm[ifm][0] = -2;
						ip -> fm[ifm][1] = -2;
					}
					break;
				}
			}
			if(iflag != -1) {
				char a[4];
				if(ip -> player == 1) {
					a[0] = 'b';
				}
				else {
					a[0] = 'w';
				}
				a[1] = '\0';
				strcat(a, temp_killed_piece);
				pp[temp_fmx][temp_fmy][0] =  '\0';
				strcat(pp[temp_fmx][temp_fmy], a);
				strcpy(chess_piece[iflag], temp_killed_piece);
			}
			else
				pp[temp_fmx][temp_fmy][0] = '\0';
			iflag = -1;
			ifm++;
		}
		strcpy(pp[ip -> px][ip -> py], ip -> piece);
	}
}
