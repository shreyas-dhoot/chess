#ifndef __CHECK__H
#define __CHECK_H

void store_future_move_king(int, int, int, int, int [][2], char ***);
void future_move_king(int, int, int [][2], char ***);
void future_move_queen(int, int, int [][2], char ***);
void future_move_rook(int, int, int [][2], char ***);
void future_move_bishop(int, int, int [][2],char ***, int, int);
void store_future_move_knight(int, int,int, int, int [][2], char ***);
void future_move_knight(int, int, int [][2], char ***);
void store_future_move_pawn(int, int, int, int, int [][2], char ***);
void future_move_pawn(int, int, int [][2], char ***, int player);
int check_ifknight(int, int, int, input *, char ***);
void check_before_turn(input *, char ***, int);
int check_in_board(int , int );
int check_chess_piece(int , char *);
int generate_future_move(input *);
int check_chess_move(input *);
int initialise_future_move(input *);
int check_chess_ifmove(input *ip);
#endif
