#ifndef __INITIALISE__H
#define __INITIALISE_H

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