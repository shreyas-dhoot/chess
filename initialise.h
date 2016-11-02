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

#ifndef __INITIALISE__H
#define __INITIALISE__H

void initpos();
void init_chess_piece();
void init_fm_king(int fm[][2]);
void init_fm_queen(int fm[][2]);
void init_fm_bishop(int fm[][2]);
void init_fm_rook(int fm[][2]);
void init_fm_knight(int fm[][2]);
void init_fm_pawn(int fm[][2]);
void initpiece();
/*WINDOW *create_newwin(int, int, int, int, int, int, int);
input *input_piece(WINDOW *, int, int, input *);
void input_move(WINDOW *, input *);
input *find_present_cordinates(input *);*/
#endif
