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
	int player;
	char piece[4];		//color + r1 + \0
	char move[3];
	int px;
	int py;
	int enum_piece;
	int (*fm)[2];
}input;
char ***pp;
char *chess_piece[32];
king wk, bk;
queen wq, bq;
bishop wb1, wb2, bb1, bb2;
knight wn1, wn2, bn1, bn2;
rook wr1, wr2, br1, br2;
pawn wp1, wp2, wp3, wp4, wp5, wp6, wp7, wp8;
pawn bp1, bp2, bp3, bp4, bp5, bp6, bp7, bp8;
#endif
