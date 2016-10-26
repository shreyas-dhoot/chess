#include "chess_declaration.h"
#include <stdlib.h>
#include <ncurses.h>
#include "functions_chess.h"
#include "initialise.h"
#include <string.h>
int isempty(int fm[][2], int n) {
	int i;
	for(i = 0; i < n - 1; i++) {
		if(fm[i][1] != -1 && fm[i][1] != -2) {
			return 0;
		}
		else if(fm[i][1] == -1) {
			return 1;
		}
	}
	return 1;
}
int checkmate(int ifcheck, input *iip) {
	input *ip;
	ip = (input *)malloc(sizeof(input));
	int k;
	if(ifcheck) {
		if(iip -> player == 1) {
			ip -> player = 1;
			if(chess_piece[0][0] != '\0') {
				future_move_rook(wr1.cp[0], wr1.cp[1], wr1.fm, pp);
				ip -> fm = wr1.fm;
				strcpy(ip -> piece, "wr1");
				ip -> px = wr1.cp[0];
				ip -> py = wr1.cp[1];
				check_before_turn(ip, pp, 1);
				k = isempty(wr1.fm, 15);
	//			printw("%d ", k);
	//			refresh();
				init_fm_rook(wr1.fm);
	//			printw("wr1 ");
	//			refresh();
	//			getch();
				if(k == 0)
					return 0;
			}
			if(chess_piece[1][0] != '\0') {
			future_move_knight(wn1.cp[0], wn1.cp[1], wn1.fm, pp);
			ip -> fm = wn1.fm;
			strcpy(ip -> piece, "wn1");
			ip -> px = wn1.cp[0];
			ip -> py = wn1.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wn1.fm, 9);
	//		printw("%d ", k);
	//		refresh();
			init_fm_knight(wn1.fm);
	//		printw("wn1 ");
	//		refresh();
	//		getch();
			if(k == 0)
				return 0;
			}
			if(chess_piece[2][0] != '\0') {
			future_move_bishop(wb1.cp[0], wb1.cp[1], wb1.fm, pp, 0, 1);
			ip -> fm = wb1.fm;
			strcpy(ip -> piece, "wb1");
			ip -> px = wb1.cp[0];
			ip -> py = wb1.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wb1.fm, 14);
	//		printw("%d ", k);
	//		refresh();
			init_fm_bishop(wb1.fm);
	//		printw("wb1 ");
	//		refresh();
	//		getch();
			if(k == 0)
				return 0;
			}
			if(chess_piece[3][0] != '\0') {
			future_move_king(wk.cp[0], wk.cp[1], wk.fm, pp);
			ip -> fm = wk.fm;
			strcpy(ip -> piece, "wk");
			ip -> px = wk.cp[0];
			ip -> py = wk.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wk.fm, 12);
	//		printw("%d ", k);
	//		refresh();
			init_fm_king(wk.fm);
	//		printw("wk ");
	//		refresh();
	//		getch();
			if(k == 0)
				return 0;
			}
			if(chess_piece[4][0] != '\0') {
			future_move_queen(wq.cp[0], wq.cp[1], wq.fm, pp);
			ip -> fm = wq.fm;
			strcpy(ip -> piece, "wq");
			ip -> px = wq.cp[0];
			ip -> py = wq.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wq.fm, 28);
	//		printw("%d ", k);
	//		refresh();
			init_fm_queen(wq.fm);
	//		printw("wq ");
	//		refresh();
	//		getch();
			if(k == 0)
				return 0;
			}
			if(chess_piece[5][0] != '\0') {
			future_move_bishop(wb2.cp[0], wb2.cp[1], wb2.fm, pp, 0, 1);
			ip -> fm = wb2.fm;
			strcpy(ip -> piece, "wb2");
			ip -> px = wb2.cp[0];
			ip -> py = wb2.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wb2.fm, 14);
	//		printw("%d ", k);
	//		refresh();
			init_fm_bishop(wb2.fm);
	//		printw("wb2 ");
	//		refresh();
	//		getch();
			if(k == 0)
				return 0;
			}
			if(chess_piece[6][0] != '\0') {
			future_move_knight(wn2.cp[0], wn2.cp[1], wn2.fm, pp);
			ip -> fm = wn2.fm;
			strcpy(ip -> piece, "wn2");
			ip -> px = wn2.cp[0];
			ip -> py = wn2.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wn2.fm, 9);
	//		printw("%d ", k);
			init_fm_knight(wn2.fm);
	//		printw("wn2 ");
	//		refresh();
	//		getch();
			if(k == 0)
				return 0;
			}
			if(chess_piece[7][0] != '\0') {
			future_move_rook(wr2.cp[0], wr2.cp[1], wr2.fm, pp);
			ip -> fm = wr2.fm;
			strcpy(ip -> piece, "wr2");
			ip -> px = wr2.cp[0];
			ip -> py = wr2.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wr2.fm, 15);
	//		printw("%d ", k);
	//		refresh();
			init_fm_rook(wr2.fm);
	//		printw("wr2 ");
	//		refresh();
	//		getch();
			if(k == 0)
				return 0;
			}
			if(chess_piece[8][0] != '\0') {
			future_move_pawn(wp1.cp[0], wp1.cp[1], wp1.fm, pp, ip -> player);
			ip -> fm = wp1.fm;
			strcpy(ip -> piece, "wp1");
			ip -> px = wp1.cp[0];
			ip -> py = wp1.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wp1.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(wp1.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[9][0] != '\0') {
			future_move_pawn(wp2.cp[0], wp2.cp[1], wp2.fm, pp, ip -> player);
			ip -> fm = wp2.fm;
			strcpy(ip -> piece, "wp2");
			ip -> px = wp2.cp[0];
			ip -> py = wp2.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wp2.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(wp2.fm);
	//		printw("wp2 ");
	//		refresh();
	//		getch();
			if(k == 0)
				return 0;
			}
			if(chess_piece[10][0] != '\0') {
			future_move_pawn(wp3.cp[0], wp3.cp[1], wp3.fm, pp, ip -> player);
			ip -> fm = wp3.fm;
			strcpy(ip -> piece, "wp3");
			ip -> px = wp3.cp[0];
			ip -> py = wp3.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wp3.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(wp3.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[11][0] != '\0') {
			future_move_pawn(wp4.cp[0], wp4.cp[1], wp4.fm, pp, ip -> player);
			ip -> fm = wp4.fm;
			strcpy(ip -> piece, "wp4");
			ip -> px = wp4.cp[0];
			ip -> py = wp4.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wp4.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(wp4.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[12][0] != '\0') {
			future_move_pawn(wp5.cp[0], wp5.cp[1], wp5.fm, pp, ip -> player);
			ip -> fm = wp5.fm;
			strcpy(ip -> piece, "wp5");
			ip -> px = wp5.cp[0];
			ip -> py = wp5.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wp5.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(wp5.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[13][0] != '\0') {
			future_move_pawn(wp6.cp[0], wp6.cp[1], wp6.fm, pp, ip -> player);
			ip -> fm = wp6.fm;
			strcpy(ip -> piece, "wp6");
			ip -> px = wp6.cp[0];
			ip -> py = wp6.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wp6.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(wp6.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[14][0] != '\0') {
			future_move_pawn(wp7.cp[0], wp7.cp[1], wp7.fm, pp, ip -> player);
			ip -> fm = wp7.fm;
			strcpy(ip -> piece, "wp7");
			ip -> px = wp7.cp[0];
			ip -> py = wp7.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wp7.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(wp7.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[15][0] != '\0') {
			future_move_pawn(wp8.cp[0], wp8.cp[1], wp8.fm, pp, ip -> player);
			ip -> fm = wp8.fm;
			strcpy(ip -> piece, "wp8");
			ip -> px = wp8.cp[0];
			ip -> py = wp8.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(wp8.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(wp8.fm);
			if(k == 0)
				return 0;
			}
			return 1;
		}
		else {	ip -> player = 0;
			if(chess_piece[16][0] != '\0') {
			future_move_rook(br1.cp[0], br1.cp[0], br1.fm, pp);
			ip -> fm = br1.fm;
			strcpy(ip -> piece, "br1");
			ip -> px = br1.cp[0];
			ip -> py = br1.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(br1.fm, 15);
	//		printw("%d ", k);
	//		refresh();
			init_fm_rook(br1.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[17][0] != '\0') {
			future_move_knight(bn1.cp[0], bn1.cp[1], bn1.fm, pp);
			ip -> fm = bn1.fm;
			strcpy(ip -> piece, "bn1");
			ip -> px = bn1.cp[0];
			ip -> py = bn1.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bn1.fm, 9);
	//		printw("%d ", k);
	//		refresh();
			init_fm_knight(bn1.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[18][0] != '\0') {
			future_move_bishop(bb1.cp[0], bb1.cp[1], bb1.fm, pp, 0, 1);
			ip -> fm = bb1.fm;
			strcpy(ip -> piece, "bb1");
			ip -> px = bb1.cp[0];
			ip -> py = bb1.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bb1.fm, 14);
	//		printw("%d ", k);
	//		refresh();
			init_fm_bishop(bb1.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[19][0] != '\0') {
			future_move_king(bk.cp[0], bk.cp[1], bk.fm, pp);
			ip -> fm = bk.fm;
			strcpy(ip -> piece, "bk");
			ip -> px = bk.cp[0];
			ip -> py = bk.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bk.fm, 12);
	//		printw("%d ", k);
	//		refresh();
			init_fm_king(bk.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[20][0] != '\0') {
			future_move_queen(bq.cp[0], bq.cp[1], bq.fm, pp);
			ip -> fm = bq.fm;
			strcpy(ip -> piece, "bq");
			ip -> px = bq.cp[0];
			ip -> py = bq.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bq.fm, 28);
	//		printw("%d ", k);
	//		refresh();
			init_fm_queen(bq.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[21][0] != '\0') {
			future_move_bishop(bb2.cp[0], bb2.cp[1], bb2.fm, pp, 0, 1);
			ip -> fm = bb2.fm;
			strcpy(ip -> piece, "bb2");
			ip -> px = bb2.cp[0];
			ip -> py = bb2.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bb2.fm, 14);
	//		printw("%d ", k);
	//		refresh();
			init_fm_bishop(bb2.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[22][0] != '\0') {
			future_move_knight(bn2.cp[0], bn2.cp[1], bn2.fm, pp);
			ip -> fm = bn2.fm;
			strcpy(ip -> piece, "bn2");
			ip -> px = bn2.cp[0];
			ip -> py = bn2.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bn2.fm, 9);
	//		printw("%d ", k);
	//		refresh();
			init_fm_knight(bn2.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[23][0] != '\0') {
			future_move_rook(br2.cp[0], br2.cp[1], br2.fm, pp);
			ip -> fm = br2.fm;
			strcpy(ip -> piece, "br2");
			ip -> px = br2.cp[0];
			ip -> py = br2.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(br2.fm, 15);
	//		printw("%d ", k);
	//		refresh();
			init_fm_rook(br2.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[24][0] != '\0') {
			future_move_pawn(bp1.cp[0], bp1.cp[1], bp1.fm, pp, ip -> player);
			ip -> fm = bp1.fm;
			strcpy(ip -> piece, "bp1");
			ip -> px = bp1.cp[0];
			ip -> py = bp1.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bp1.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(bp1.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[25][0] != '\0') {
			future_move_pawn(bp2.cp[0], bp2.cp[1], bp2.fm, pp, ip -> player);
			ip -> fm = bp2.fm;
			strcpy(ip -> piece, "bp2");
			ip -> px = bp2.cp[0];
			ip -> py = bp2.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bp2.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(bp2.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[26][0] != '\0') {
			future_move_pawn(bp3.cp[0],bp3.cp[1], bp3.fm, pp, ip -> player);
			ip -> fm = bp3.fm;
			strcpy(ip -> piece, "bp3");
			ip -> px = bp3.cp[0];
			ip -> py = bp3.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bp3.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(bp3.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[27][0] != '\0') {
			future_move_pawn(bp4.cp[0], bp4.cp[1], bp4.fm, pp, ip -> player);
			ip -> fm = bp4.fm;
			strcpy(ip -> piece, "bp4");
			ip -> px = bp4.cp[0];
			ip -> py = bp4.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bp4.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(bp4.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[28][0] != '\0') {
			future_move_pawn(bp5.cp[0], bp5.cp[1], bp5.fm, pp, ip -> player);
			ip -> fm = bp5.fm;
			strcpy(ip -> piece, "bp5");
			ip -> px = bp5.cp[0];
			ip -> py = bp5.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bp5.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(bp5.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[29][0] != '\0') {
			future_move_pawn(bp6.cp[0], bp6.cp[1], bp6.fm, pp, ip -> player);
			ip -> fm = bp6.fm;
			strcpy(ip -> piece, "bp6");
			ip -> px = bp6.cp[0];
			ip -> py = bp6.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bp6.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(bp6.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[30][0] != '\0') {
			future_move_pawn(bp7.cp[0], bp7.cp[1], bp7.fm, pp, ip -> player);
			ip -> fm = bp7.fm;
			strcpy(ip -> piece, "bp7");
			ip -> px = bp7.cp[0];
			ip -> py = bp7.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bp7.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(bp7.fm);
			if(k == 0)
				return 0;
			}
			if(chess_piece[31][0] != '\0') {
			future_move_pawn(bp8.cp[0], bp8.cp[1], bp8.fm, pp, ip -> player);
			ip -> fm = bp8.fm;
			strcpy(ip -> piece, "bp8");
			ip -> px = bp8.cp[0];
			ip -> py = bp8.cp[1];
			check_before_turn(ip, pp, 1);
			k = isempty(bp8.fm, 5);
	//		printw("%d ", k);
	//		refresh();
			init_fm_pawn(bp8.fm);
			if(k == 0)
				return 0;
			}
			return 1;
		}
	}
	else {
		return 0;
	}

}
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
	return 0;
}
