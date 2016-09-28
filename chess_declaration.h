typedef struct king {
	int col;		//color 1 for white 0 for black
	int *fm[11];		//Future moves
	int cp[2];		//Current position
}king;
typedef struct queen {
	int col;
	int *fm[28];
	int cp[2];		//Current position
}queen;

typedef struct bishop {
	int col;
	int cp[2];		//Current position
	int *fm[14];
}bishop;
typedef struct rook {
	int col;
	int cp[2];		//Current position
	int *fm[15];
}rook;
typedef struct knight {
	int col;
	int cp[2];		//Current position
	int *fm[9];
}knight;
typedef struct pawn {
	int col
	int cp[2];		//Current position
	int *fm[4];
}
