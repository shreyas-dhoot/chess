//There should be a condition where after every move it checks for a check and if it is within the chess.
	//Initialise fm than add moves to it.
//store k in the last box.
//k will store no. of moves.
//future moves correct only for white pieces
#include "chess_declaration.h"
#include "functions_chess.h"
#include <stdlib.h>
#include <ncurses.h>
void store_future_move_king(int px, int py, int i, int j, int fm[][2], char ***pp) {
	int k = fm[11][0];
	if(pp[i][j][0] == '\0' || pp[px][py][0] != pp[i][j][0]) {
		fm[k][0] = i;
		fm[k][1] = j;
		(fm[11][0])++;
	}
}

int **future_move_king(int px, int py, int fm[][2], char ***pp) {			//Input present co - ordinates of the piece
	int **temp_pointer;
	temp_pointer = (int **)malloc(sizeof(int *) * 2);
	temp_pointer[0] = fm[0];
	temp_pointer[1] = fm[1];

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
	int i;
	for(i = 0; i < 11; i++)
			printw("(%d, %d), ", fm[i][0], fm[i][1]);
	return temp_pointer;
}

int **future_move_queen(int px, int py, int fm[][2], char ***pp) {
	int **temp_pointer;
	temp_pointer = (int **)malloc(sizeof(int *) * 2);
	temp_pointer[0] = fm[0];
	temp_pointer[1] = fm[1];

	int i, j, k = 0;				//Have to return k too.
	future_move_rook(px, py, fm, pp);
	k = fm[14][0];
	fm[14][0] = -1;
	future_move_bishop(px, py, fm, pp, k, 0);
	for(i = 0; i < 27; i++)
			printw("(%d, %d), ", fm[i][0], fm[i][1]);
	return temp_pointer;
}

int **future_move_rook(int px, int py, int fm[][2], char ***pp) {
	int **temp_pointer;
	temp_pointer = (int **)malloc(sizeof(int *) * 2);
	temp_pointer[0] = fm[0];
	temp_pointer[1] = fm[1];

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
		else {
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
	for(i = 0; i < 15; i++)
			printw("(%d, %d), ", fm[i][0], fm[i][1]);
	return temp_pointer;
}

int **future_move_bishop(int px, int py, int fm[][2], char ***pp, int k, int isbishop) {		//Storing all the future moves of bishop in fm
	//There should be a condition where after every move it checks for a check.
	//Initialise fm than add to it.
	int **temp_pointer;
	temp_pointer = (int **)malloc(sizeof(int *) * 2);
	temp_pointer[0] = fm[0];
	temp_pointer[1] = fm[1];


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
		else {							//If both are of different color
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
		else {
			fm[k][0] = i;
			fm[k][1] = j;
			k++;
			break;
		}
		
	}
	for(i = px + 1, j = px - 1; i < 8 && j > -1; i++, j--) {
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
	for(i = px - 1, j = px + 1; i > -1 && j < 8; i--, j++) {
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
		for(i = 0; i < 14; i++)
			printw("(%d, %d), ", fm[i][0], fm[i][1]);
	}
	else
		fm[26][0] = k;
	
	return temp_pointer;
}

void store_future_move_knight(int px, int py, int i, int j, int fm[][2], char ***pp) {
	int k = fm[8][0];
	if(pp[i][j][0] == '\0' || pp[px][py][0] != pp[i][j][0]) {
		fm[k][0] = i;
		fm[k][1] = j;
		(fm[8][0])++;
	}
}
int **future_move_knight(int px, int py, int fm[][2], char ***pp) {
	int **temp_pointer;
	temp_pointer = (int **)malloc(sizeof(int *) * 2);
	temp_pointer[0] = fm[0];
	temp_pointer[1] = fm[1];


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
	int i;
	for(i = 0; i < 9; i++)
		printw("(%d, %d), ", fm[i][0], fm[i][1]);
	refresh();
	getch();
	return temp_pointer;
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

int **future_move_pawn(int px, int py, int fm[][2], char ***pp) {
	int **temp_pointer;
	temp_pointer = (int **)malloc(sizeof(int *) * 2);
	temp_pointer[0] = fm[0];
	temp_pointer[1] = fm[1];

	fm[4][0] = 0;
	if(check_in_board(px + 1, py + 1)) {
		store_future_move_pawn(px, py, px + 1, py + 1, fm, pp);
	}
	if(check_in_board(px + 1, py)) {
		store_future_move_pawn(px, py, px + 1, py, fm, pp);
	}
	if(check_in_board(px + 1, py - 1)) {
		store_future_move_pawn(px, py, px + 1, py - 1, fm, pp);
	}
	int i;
	for(i = 0; i < 5; i++)
		printw("(%d, %d), ", fm[i][0], fm[i][0]);
	return temp_pointer;
}
