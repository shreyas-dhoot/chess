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
#include <string.h>
#include "chess_declaration.h"
#include "functions_chess.h"
#include "initialise.h"
#include <ncurses.h>

int check_in_board(int i, int j) {				//Checking if (i, j) is a valid position or not
	if(i > 7 || i < 0 || j < 0 || j > 7)
		return 0;
	else
		return 1;
}

void print_chess_piece() {
	int i;
	move(3,0);
	clrtoeol();
	move(4,0);
	clrtoeol();
	move(5,0);
	clrtoeol();
	move(3,0);
	for(i = 0 ; i < 32; i++) {
		printw("(%d : %s) ", i, chess_piece[i]);
	}
	getch();
	refresh();
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
		case 0: ip -> fm = wr1.fm;
			future_move_rook(ip -> px, ip -> py, wr1.fm, pp);
				break;
		case 1: ip -> fm = wn1.fm;
			future_move_knight(ip -> px, ip -> py, wn1.fm, pp);
				break;
		case 2: ip -> fm = wb1.fm;
			future_move_bishop(ip -> px, ip -> py, wb1.fm, pp, 0, 1);
				break;
		case 3: ip -> fm = wk.fm;
			future_move_king(ip -> px, ip -> py, wk.fm, pp);
				break;
		case 4: ip -> fm = wq.fm;
			future_move_queen(ip -> px, ip -> py, wq.fm, pp);
				break;
		case 5: ip -> fm = wb2.fm;
			future_move_bishop(ip -> px, ip -> py, wb2.fm, pp, 0, 1);
				break;
		case 6: ip -> fm = wn2.fm;
			future_move_knight(ip -> px, ip -> py, wn2.fm, pp);
				break;
		case 7: ip -> fm = wr2.fm;
			future_move_rook(ip -> px, ip -> py, wr2.fm, pp);
				break;
		case 8: ip -> fm = wp1.fm;
			future_move_pawn(ip -> px, ip -> py, wp1.fm, pp, ip -> player);
				break;
		case 9: ip -> fm = wp2.fm;
			future_move_pawn(ip -> px, ip -> py, wp2.fm, pp, ip -> player);
				break;
		case 10: ip -> fm = wp3.fm;
			future_move_pawn(ip -> px, ip -> py, wp3.fm, pp, ip -> player);
				break;
		case 11: ip -> fm = wp4.fm;
			future_move_pawn(ip -> px, ip -> py, wp4.fm, pp, ip -> player);
				break;
		case 12: ip -> fm = wp5.fm;
			 future_move_pawn(ip -> px, ip -> py, wp5.fm, pp, ip -> player);
				break;
		case 13: ip -> fm = wp6.fm;
			 future_move_pawn(ip -> px, ip -> py, wp6.fm, pp, ip -> player);
				break;
		case 14: ip -> fm = wp7.fm;
			future_move_pawn(ip -> px, ip -> py, wp7.fm, pp, ip -> player);
				break;
		case 15: ip -> fm = wp8.fm;
			 future_move_pawn(ip -> px, ip -> py, wp8.fm, pp, ip -> player);
				break;
		case 16: ip -> fm = br1.fm;
			 future_move_rook(ip -> px, ip -> py, br1.fm, pp);
				break;
		case 17: ip -> fm = bn1.fm;
			 future_move_knight(ip -> px, ip -> py, bn1.fm, pp);
				break;
		case 18: ip -> fm = bb1.fm;
			 future_move_bishop(ip -> px, ip -> py, bb1.fm, pp, 0, 1);
				break;
		case 19: ip -> fm = bk.fm;
			 future_move_king(ip -> px, ip -> py, bk.fm, pp);
				break;
		case 20: ip -> fm = bq.fm;
			 future_move_queen(ip -> px, ip -> py, bq.fm, pp);
				break;
		case 21: ip -> fm = bb2.fm;
			 future_move_bishop(ip -> px, ip -> py, bb2.fm, pp, 0, 1);
				break;
		case 22: ip -> fm = bn2.fm;
			 future_move_knight(ip -> px, ip -> py, bn2.fm, pp);
				break;
		case 23: ip -> fm = br2.fm;
			 future_move_rook(ip -> px, ip -> py, br2.fm, pp);
				break;
		case 24: ip -> fm = bp1.fm;
			 future_move_pawn(ip -> px, ip -> py, bp1.fm, pp, ip -> player);
				break;
		case 25: ip -> fm = bp2.fm;
			 future_move_pawn(ip -> px, ip -> py, bp2.fm, pp, ip -> player);
				break;
		case 26: ip -> fm = bp3.fm;
			 future_move_pawn(ip -> px, ip -> py, bp3.fm, pp, ip -> player);
				break;
		case 27: ip -> fm = bp4.fm;
			 future_move_pawn(ip -> px, ip -> py, bp4.fm, pp, ip -> player);
				break;
		case 28: ip -> fm = bp5.fm;
			 future_move_pawn(ip -> px, ip -> py, bp5.fm, pp, ip -> player);
				break;
		case 29: ip -> fm = bp6.fm;
			 future_move_pawn(ip -> px, ip -> py, bp6.fm, pp, ip -> player);
				break;
		case 30: ip -> fm = bp7.fm;
			 future_move_pawn(ip -> px, ip -> py, bp7.fm, pp, ip -> player);
				break;
		case 31: ip -> fm = bp8.fm;
			 future_move_pawn(ip -> px, ip -> py, bp8.fm, pp, ip -> player);
				break;
		default: return 0;
	}
	return 1;
}

int initialise_future_move(input *ip) {
	int x, y;
	x = (ip -> move[0]) - '0';
	y = (ip -> move[1]) - '0';
	switch(ip -> enum_piece) {
		case 0:  wr1.cp[0] = x;
			 wr1.cp[1] = y;
			 ip -> fm = wr1.fm;
			 init_fm_rook(wr1.fm);
				break;
		case 1:  wn1.cp[0] = x;
			 wn1.cp[1] = y;
			 ip -> fm = wn1.fm;
			 init_fm_knight(wn1.fm);
				break;
		case 2:  wb1.cp[0] = x;
			 wb1.cp[1] = y;
			 ip -> fm = wb1.fm;
			 init_fm_bishop(wb1.fm);
				break;
		case 3:  wk.cp[0] = x;
			 wk.cp[1] = y;
			 ip -> fm = wk.fm;
			 init_fm_king(wk.fm);
				break;
		case 4:  wq.cp[0] = x;
			 wq.cp[1] = y;
			 ip -> fm = wq.fm;
			 init_fm_queen(wq.fm);
				break;
		case 5:  wb2.cp[0] = x;
			 wb2.cp[1] = y;
			 ip -> fm = wb2.fm;
			 init_fm_bishop(wb2.fm);
				break;
		case 6:  wn2.cp[0] = x;
			 wn2.cp[1] = y;
			 ip -> fm = wn2.fm;
			 init_fm_knight(wn2.fm);
				break;
		case 7:  wr2.cp[0] = x;
			 wr2.cp[1] = y;
			 ip -> fm = wr2.fm;
			 init_fm_rook(wr2.fm);
				break;
		case 8:  wp1.cp[0] = x;
			 wp1.cp[1] = y;
			 ip -> fm = wp1.fm;
			 init_fm_pawn(wp1.fm);
				break;
		case 9:  wp2.cp[0] = x;
			 wp2.cp[1] = y;
			 ip -> fm = wp2.fm;
			 init_fm_pawn(wp2.fm);
				break;
		case 10: wp3.cp[0] = x;
			 wp3.cp[1] = y; 
			 ip -> fm = wp3.fm;
			 init_fm_pawn(wp3.fm);
				break;
		case 11: wp4.cp[0] = x;
			 wp4.cp[1] = y;
			 ip -> fm = wp4.fm;
			 init_fm_pawn(wp4.fm);
				break;
		case 12: wp5.cp[0] = x;
			 wp5.cp[1] = y;
			 ip -> fm = wp5.fm;
			 init_fm_pawn(wp5.fm);
				break;
		case 13: wp6.cp[0] = x;
			 wp6.cp[1] = y;
			 ip -> fm = wp6.fm;
			 init_fm_pawn(wp6.fm);
				break;
		case 14: wp7.cp[0] = x;
			 wp7.cp[1] = y; 
			 ip -> fm = wp7.fm;
			 init_fm_pawn(wp7.fm);
				break;
		case 15: wp8.cp[0] = x;
			 wp8.cp[1] = y;
			 ip -> fm = wp8.fm;
			 init_fm_pawn(wp8.fm);
				break;
		case 16: br1.cp[0] = x;
			 br1.cp[1] = y;
			 ip -> fm = br1.fm;
			 init_fm_rook(br1.fm);
				break;
		case 17: bn1.cp[0] = x;
			 bn1.cp[1] = y;
			 ip -> fm = bn1.fm;
			 init_fm_knight(bn1.fm);
				break;
		case 18: bb1.cp[0] = x;
			 bb1.cp[1] = y;
			 ip -> fm = bb1.fm;
			 init_fm_bishop(bb1.fm);
				break;
		case 19: bk.cp[0] = x;
			 bk.cp[1] = y; 
			 ip -> fm = bk.fm;
			 init_fm_king(bk.fm);
				break;
		case 20: bq.cp[0] = x;
			 bq.cp[1] = y;
			 ip -> fm = bq.fm;
			 init_fm_queen(bq.fm);
				break;
		case 21: bb2.cp[0] = x;
			 bb2.cp[1] = y;
			 ip -> fm = bb2.fm;
			 init_fm_bishop(bb2.fm);
				break;
		case 22: bn2.cp[0] = x;
			 bn2.cp[1] = y;
			 ip -> fm = bn2.fm;
			 init_fm_knight(bn2.fm);
				break;
		case 23: br2.cp[0] = x;
			 br2.cp[1] = y;
			 ip -> fm = br2.fm;
			 init_fm_rook(br2.fm);
				break;
		case 24: bp1.cp[0] = x;
			 bp1.cp[1] = y;
			 ip -> fm = bp1.fm;
			 init_fm_pawn(bp1.fm);
				break;
		case 25: bp2.cp[0] = x;
			 bp2.cp[1] = y;
			 ip -> fm = bp2.fm;
			 init_fm_pawn(bp2.fm);
				break;
		case 26: bp3.cp[0] = x;
			 bp3.cp[1] = y;
			 ip -> fm = bp3.fm;
			 init_fm_pawn(bp3.fm);
				break;
		case 27: bp4.cp[0] = x;
			 bp4.cp[1] = y;
			 ip -> fm = bp4.fm;
			 init_fm_pawn(bp4.fm);
				break;
		case 28: bp5.cp[0] = x;
			 bp5.cp[1] = y;
			 ip -> fm = bp5.fm;
			 init_fm_pawn(bp5.fm);
				break;
		case 29: bp6.cp[0] = x;
			 bp6.cp[1] = y;
			 ip -> fm = bp6.fm;
			 init_fm_pawn(bp6.fm);
				break;
		case 30: bp7.cp[0] = x;
			 bp7.cp[1] = y;
			 ip -> fm = bp7.fm;
			 init_fm_pawn(bp7.fm);
				break;
		case 31: bp8.cp[0] = x;
			 bp8.cp[1] = y;
			 ip -> fm = bp8.fm;
			 init_fm_pawn(bp8.fm);
				break;
		default: return 0;
	}
	return 1;
}

int check_chess_move(input *ip) {
	int i = 0;
	while((ip -> fm)[i][1] != -1) {
		if(ip -> fm[i][1] == -2) {
			i++;
			continue;
		}
		if((ip -> fm)[i][0] == ((ip -> move)[0] - '0')) {
			if((ip -> fm)[i][1] == ((ip -> move)[1] - '0')) {
				return 1;
			}
		}
		i++;
	}
	if(i == 0)
		return -1;
	return 0;
}

int check_chess_ifmove(input *ip) {
	int i = 0;
	while(1) {
	if(ip -> fm[i][1] == -2) {
		i++;
		continue;
	}
	if((ip -> fm)[i][1] == -1)
		return 0;
	return 1;
	i++;
	}
}
