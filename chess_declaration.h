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

#ifndef __DECLERATION__H
#define __DECLERATION__H
typedef struct king {
	int fm[12][2];		//Future moves
	int cp[2];		//Current position
}king;
typedef struct queen {
	int fm[28][2];
	int cp[2];		//Current position
}queen;

typedef struct bishop {
	int fm[14][2];
	int cp[2];		//Current position
}bishop;
typedef struct rook {
	int fm[15][2];
	int cp[2];		//Current position
}rook;
typedef struct knight {
	int fm[9][2];
	int cp[2];		//Current position
}knight;
typedef struct pawn {
	int fm[5][2];
	int cp[2];		//Current position
}pawn;
typedef struct input {		
	int player;		//stores if white's or black's chance
	char piece[4];		//color + r1 + \0
	char move[3];		//stores move of the inputed piece
	int px;			//stores present x cordinate of inputed piece
	int py;			//stores present y cordinate of inputed piece
	int enum_piece;		//stores enum of inputed piece
	int (*fm)[2];		//points to future move of input piece
}input;
char ***pp;			// chessboard
char *chess_piece[32];		//enum of chess pieces
king wk, bk;			//structure of chess pieces
queen wq, bq;
bishop wb1, wb2, bb1, bb2;
knight wn1, wn2, bn1, bn2;
rook wr1, wr2, br1, br2;
pawn wp1, wp2, wp3, wp4, wp5, wp6, wp7, wp8;
pawn bp1, bp2, bp3, bp4, bp5, bp6, bp7, bp8;
#endif
