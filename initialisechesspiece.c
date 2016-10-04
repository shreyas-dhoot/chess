#include <stdio.h>
#include "chess_declaration.h"
#include <string.h>
#include <stdlib.h>
king wk, bk;
queen wq, bq;
bishop wb1, wb2, bb1, bb2;
knight wn1, wn2, bn1, bn2;
rook wr1, wr2, br1, br2;
pawn wp1, wp2, wp3, wp4, wp5, wp6, wp7, wp8;
pawn bp1, bp2, bp3, bp4, bp5, bp6, bp7, bp8;

int check_in_board(int i, int j) {				//Checking if (i, j) is a valid position or not
	if(i > 7 || i < 0 || j < 0 || j > 7)
		return 0;
	else
		return 1;
}

void initpos() {				//Position at the start.
	int i;
	int j;
	pp = (char ***)malloc(sizeof(char **) * 8);
	for(i = 0;i < 8;i++) {
		pp[i] = (char **)malloc(sizeof(char *) * 8);
		for(j = 0;j < 8;j++) {
			pp[i][j] = (char *)malloc(sizeof(char) * 4);
			pp[i][j][0] = '\0';
		}
	}
	strcpy(pp[0][0], "wr1"); strcpy(pp[7][0], "br1");
	strcpy(pp[0][1], "wn1"); strcpy(pp[7][1], "bn1");
	strcpy(pp[0][2], "wb1"); strcpy(pp[7][2], "bb1");
	strcpy(pp[0][3], "wk");  strcpy(pp[7][3], "bk");
	strcpy(pp[0][4], "wq");  strcpy(pp[7][4], "bq");
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

void init_fm_king(int **fm) {
	int i;
	for(i = 0; i < 11; i++) {
		fm[i][0] = -1;					//Initialising all the future moves.
	}
}

void init_fm_queen(int **fm) {
	int i;
	for(i = 0;i < 28;i++) {
		fm[i][0] = -1;
	}
}

void init_fm_bishop(int **fm) {
	int i;
	for(i = 0;i < 14;i++) {
		fm[i][0] = -1;
	}
}

void init_fm_rook(int **fm) {
	int i;
	for(i = 0;i < 15;i++) {
		fm[i][0] = -1;
	}
}

void init_fm_knight(int **fm) {
	int i;
	for(i = 0;i < 9;i++) {
		fm[i][0] = -1;
	}
}

void init_fm_pawn(int **fm) {
	int i;
	for(i = 0; i < 4;i++) {
		fm[i][0] = -1;
	}
}

void initpiece() {							//Initializing all the attributes of the pieces.
	wk.col = 1;	wr1.col = 1;	wp7.col = 1;			//Initializing color
	bk.col = 0;	wr2.col = 1;	wp8.col = 1;
	wb1.col = 1;	br1.col = 0;	bp1.col = 0;
	wb2.col = 1;	br2.col = 0;	bp2.col = 0;
	bb1.col = 0;	wp1.col = 1;	bp3.col = 0;
	bb2.col = 0;	wp2.col = 1;	bp4.col = 0;
	wn1.col = 1;	wp3.col = 1;	bp5.col = 0;
	wn2.col = 1;	wp4.col = 1;	bp6.col = 0;
	bn1.col = 0;	wp5.col = 1;	bp7.col = 0;
	bn2.col = 0;	wp6.col = 1;	bp8.col = 0;
	int i;
	for(i = 0;i < 11;i++) {						//Allocating memory for future moves.
		wk.fm[i] = (int *)malloc(sizeof(int) * 2);		//One move contains 2 cordinates
		bk.fm[i] = (int *)malloc(sizeof(int) * 2);
	}
	init_fm_king(wk.fm);
	init_fm_king(bk.fm);
	for(i = 0;i < 28;i++) {
		wq.fm[i] = (int *)malloc(sizeof(int) * 2);
		bq.fm[i] = (int *)malloc(sizeof(int) * 2);
	}
	init_fm_queen(wq.fm);
	init_fm_queen(bq.fm);
	for(i = 0;i < 14;i++) {
		wb1.fm[i] = (int *)malloc(sizeof(int) * 2);
		wb2.fm[i] = (int *)malloc(sizeof(int) * 2);
		bb1.fm[i] = (int *)malloc(sizeof(int) * 2);
		bb2.fm[i] = (int *)malloc(sizeof(int) * 2);
	}
	init_fm_bishop(wb1.fm);
	init_fm_bishop(wb2.fm);
	init_fm_bishop(bb1.fm);
	init_fm_bishop(bb2.fm);
	for(i = 0;i < 15;i++) {
		wr1.fm[i] = (int *)malloc(sizeof(int) * 2);
		wr2.fm[i] = (int *)malloc(sizeof(int) * 2);
		br1.fm[i] = (int *)malloc(sizeof(int) * 2);
		br2.fm[i] = (int *)malloc(sizeof(int) * 2);
	}
	init_fm_rook(wr1.fm);
	init_fm_rook(wr2.fm);
	init_fm_rook(br1.fm);
	init_fm_rook(br2.fm);
	for(i = 0;i < 9;i++) {
		wn1.fm[i] = (int *)malloc(sizeof(int) * 2);
		wn2.fm[i] = (int *)malloc(sizeof(int) * 2);
		bn1.fm[i] = (int *)malloc(sizeof(int) * 2);
		bn2.fm[i] = (int *)malloc(sizeof(int) * 2);
	}
	init_fm_knight(wn1.fm);
	init_fm_knight(wn2.fm);
	init_fm_knight(bn1.fm);
	init_fm_knight(bn2.fm);
	for(i = 0;i < 4;i++) {
		wp1.fm[i] = (int *)malloc(sizeof(int) * 2);	
		wp2.fm[i] = (int *)malloc(sizeof(int) * 2);
		wp3.fm[i] = (int *)malloc(sizeof(int) * 2);
		wp4.fm[i] = (int *)malloc(sizeof(int) * 2);
		wp5.fm[i] = (int *)malloc(sizeof(int) * 2);
		wp6.fm[i] = (int *)malloc(sizeof(int) * 2);
		wp7.fm[i] = (int *)malloc(sizeof(int) * 2);
		wp8.fm[i] = (int *)malloc(sizeof(int) * 2);
		bp1.fm[i] = (int *)malloc(sizeof(int) * 2);
		bp2.fm[i] = (int *)malloc(sizeof(int) * 2);
		bp3.fm[i] = (int *)malloc(sizeof(int) * 2);
		bp4.fm[i] = (int *)malloc(sizeof(int) * 2);
		bp5.fm[i] = (int *)malloc(sizeof(int) * 2);
		bp6.fm[i] = (int *)malloc(sizeof(int) * 2);
		bp7.fm[i] = (int *)malloc(sizeof(int) * 2);
		bp8.fm[i] = (int *)malloc(sizeof(int) * 2);
	}
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
