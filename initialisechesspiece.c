/*			Copyright 2016 Shreyas Dhoot
	This file is part of Chess 2.0.
	Chess 2.0 is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Chess 2.0 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Chess 2.0.  If not, see <http://www.gnu.org/licenses/>. */

#include <stdio.h>
#include "chess_declaration.h"
#include "functions_chess.h"
#include <string.h>
#include <stdlib.h>
void initpos() {				//Initialise position at the start.
	int i;
	int j;
	pp = (char ***)malloc(sizeof(char **) * 8);
	for(i = 0;i < 8;i++) {			//malloc chessboard
		pp[i] = (char **)malloc(sizeof(char *) * 8);
		for(j = 0;j < 8;j++) {
			pp[i][j] = (char *)malloc(sizeof(char) * 4);
			pp[i][j][0] = '\0';
		}
	}
	strcpy(pp[0][0], "wr1"); strcpy(pp[7][0], "br1");	//initialise chess piece to their resp. position
	strcpy(pp[0][1], "wn1"); strcpy(pp[7][1], "bn1");
	strcpy(pp[0][2], "wb1"); strcpy(pp[7][2], "bb1");
	strcpy(pp[0][3], "wq");  strcpy(pp[7][3], "bq");
	strcpy(pp[0][4], "wk");  strcpy(pp[7][4], "bk");
	strcpy(pp[0][5], "wb2"); strcpy(pp[7][5], "bb2");
	strcpy(pp[0][6], "wn2"); strcpy(pp[7][6], "bn2");
	strcpy(pp[0][7], "wr2"); strcpy(pp[7][7], "br2");

	strcpy(pp[1][0], "wp1"); strcpy(pp[6][0], "bp1");
	strcpy(pp[1][1], "wp2"); strcpy(pp[6][1], "bp2");
	strcpy(pp[1][2], "wp3"); strcpy(pp[6][2], "bp3");
	strcpy(pp[1][3], "wp4"); strcpy(pp[6][3], "bp4");
	strcpy(pp[1][4], "wp5"); strcpy(pp[6][4], "bp5");
	strcpy(pp[1][5], "wp6"); strcpy(pp[6][5], "bp6");
	strcpy(pp[1][6], "wp7"); strcpy(pp[6][6], "bp7");
	strcpy(pp[1][7], "wp8"); strcpy(pp[6][7], "bp8");
}

void init_chess_piece() {						//inittialise chess piece (enum)
	int i;
	for(i = 0; i < 32; i++) {
		chess_piece[i] = (char *)malloc(3);
	}
	strcpy(chess_piece[0], "r1");	strcpy(chess_piece[16], "r1");
	strcpy(chess_piece[1], "n1");	strcpy(chess_piece[17], "n1");
	strcpy(chess_piece[2], "b1");	strcpy(chess_piece[18], "b1");
	strcpy(chess_piece[3], "k");	strcpy(chess_piece[19], "k");
	strcpy(chess_piece[4], "q");	strcpy(chess_piece[20], "q");
	strcpy(chess_piece[5], "b2");	strcpy(chess_piece[21], "b2");
	strcpy(chess_piece[6], "n2");	strcpy(chess_piece[22], "n2");
	strcpy(chess_piece[7], "r2");	strcpy(chess_piece[23], "r2");

	strcpy(chess_piece[8], "p1");	strcpy(chess_piece[24], "p1");
	strcpy(chess_piece[9], "p2");	strcpy(chess_piece[25], "p2");
	strcpy(chess_piece[10], "p3");	strcpy(chess_piece[26], "p3");
	strcpy(chess_piece[11], "p4");	strcpy(chess_piece[27], "p4");
	strcpy(chess_piece[12], "p5");	strcpy(chess_piece[28], "p5");
	strcpy(chess_piece[13], "p6");	strcpy(chess_piece[29], "p6");
	strcpy(chess_piece[14], "p7");	strcpy(chess_piece[30], "p7");
	strcpy(chess_piece[15], "p8");	strcpy(chess_piece[31], "p8");
}
//Initialising all the future moves.
void init_fm_king(int fm[][2]) {
	int i;
	for(i = 0; i < 12; i++) {
		fm[i][0] = -1;
		fm[i][1] = -1;
	}
}

void init_fm_queen(int fm[][2]) {
	int i;
	for(i = 0;i < 28;i++) {
		fm[i][0] = -1;
		fm[i][1] = -1;
	}
}

void init_fm_bishop(int fm[][2]) {
	int i;
	for(i = 0;i < 14;i++) {
		fm[i][0] = -1;
		fm[i][1] = -1;
	}
}

void init_fm_rook(int fm[][2]) {
	int i;
	for(i = 0;i < 15;i++) {
		fm[i][0] = -1;
		fm[i][1] = -1;
	}
}

void init_fm_knight(int fm[][2]) {
	int i;
	for(i = 0;i < 9;i++) {
		fm[i][0] = -1;
		fm[i][1] = -1;
	}
}

void init_fm_pawn(int fm[][2]) {
	int i;
	for(i = 0; i < 5;i++) {
		fm[i][0] = -1;
		fm[i][1] = -1;
	}
}

void initpiece() {	
							//Initializing all the attributes of the pieces.
	wr1.cp[0] = 0;	wp1.cp[0] = 1;  br1.cp[0] = 7;  bp1.cp[0] = 6;
	wr1.cp[1] = 0;  wp1.cp[1] = 0;  br1.cp[1] = 0;  bp1.cp[1] = 0;
	wn1.cp[0] = 0;  wp2.cp[0] = 1;  bn1.cp[0] = 7;  bp2.cp[0] = 6;
	wn1.cp[1] = 1;  wp2.cp[1] = 1;  bn1.cp[1] = 1;  bp2.cp[1] = 1;
	wb1.cp[0] = 0;  wp3.cp[0] = 1;  bb1.cp[0] = 7;  bp3.cp[0] = 6;
	wb1.cp[1] = 2;  wp3.cp[1] = 2;  bb1.cp[1] = 2;  bp3.cp[1] = 2;
	wq.cp[0] = 0;   wp4.cp[0] = 1;  bq.cp[0] = 7;   bp4.cp[0] = 6;
	wq.cp[1] = 3;   wp4.cp[1] = 3;  bq.cp[1] = 3;   bp4.cp[1] = 3;
	wk.cp[0] = 0;   wp5.cp[0] = 1;  bk.cp[0] = 7;   bp5.cp[0] = 6;
	wk.cp[1] = 4;   wp5.cp[1] = 4;  bk.cp[1] = 4;   bp5.cp[1] = 4;
	wb2.cp[0] = 0;  wp6.cp[0] = 1;  bb2.cp[0] = 7;  bp6.cp[0] = 6;
	wb2.cp[1] = 5;  wp6.cp[1] = 5;  bb2.cp[1] = 5;  bp6.cp[1] = 5;
	wn2.cp[0] = 0;  wp7.cp[0] = 1;  bn2.cp[0] = 7;  bp7.cp[0] = 6;
	wn2.cp[1] = 6;  wp7.cp[1] = 6;  bn2.cp[1] = 6;  bp7.cp[1] = 6;
	wr2.cp[0] = 0;  wp8.cp[0] = 1;  br2.cp[0] = 7;  bp8.cp[0] = 6;
	wr2.cp[1] = 7;  wp8.cp[1] = 7;  br2.cp[1] = 7;  bp8.cp[1] = 7;
	
	init_fm_king(wk.fm);
	init_fm_king(bk.fm);

	init_fm_queen(wq.fm);
	init_fm_queen(bq.fm);

	init_fm_bishop(wb1.fm);
	init_fm_bishop(wb2.fm);
	init_fm_bishop(bb1.fm);
	init_fm_bishop(bb2.fm);

	init_fm_rook(wr1.fm);
	init_fm_rook(wr2.fm);
	init_fm_rook(br1.fm);
	init_fm_rook(br2.fm);

	init_fm_knight(wn1.fm);
	init_fm_knight(wn2.fm);
	init_fm_knight(bn1.fm);
	init_fm_knight(bn2.fm);

	init_fm_pawn(wp1.fm);
	init_fm_pawn(wp2.fm);
	init_fm_pawn(wp3.fm);
	init_fm_pawn(wp4.fm);
	init_fm_pawn(wp5.fm);
	init_fm_pawn(wp6.fm);
	init_fm_pawn(wp7.fm);
	init_fm_pawn(wp8.fm);

	init_fm_pawn(bp1.fm);
	init_fm_pawn(bp2.fm);
	init_fm_pawn(bp3.fm);
	init_fm_pawn(bp4.fm);
	init_fm_pawn(bp5.fm);
	init_fm_pawn(bp6.fm);
	init_fm_pawn(bp7.fm);
	init_fm_pawn(bp8.fm);
}
