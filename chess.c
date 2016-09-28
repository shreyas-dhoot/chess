void input() {
	Select a piece.
	If moving the piece will result iin a check, then illegal move.
	Example if pp[x][y][1] == b //bishop
		call future moves of bishop by passing cordinates
	Highlight all the possible moves.
	Select a move.
	call verify_move and check if the move is one of the future move
	last
	initialise the future moves
	after moving initialize it to \0
	enter the new position into cp
	return the move.
}

int verify_move() {
}


