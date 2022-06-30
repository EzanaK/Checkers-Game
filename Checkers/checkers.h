/*
 * checkers.h
 *
 Header file for Project 1
 *
 */

/* boolean constants */
#define TRUE 1
#define FALSE 0

/* check functions will return valid/invalid status of moves */
#define VALID_MOVE 1
#define INVALID_MOVE 2

/* each checker board square will encode its contents */
#define EMPTY 0
#define RED 1
#define WHITE 2
#define RED_KING 3
#define WHITE_KING 4

#define BOARD_SIZE 8
extern int the_board[BOARD_SIZE][BOARD_SIZE];

/* Required Functions */
void initialize_board();
void print_board();
void print_piece(int i, int j);
int jump_exists(int color);
void move_piece(int color, int x_from, int y_from, int x_to, int y_to,int jump);
int check_move(int color, int x_from, int y_from, int x_to, int y_to, int jump);
int check_jump(int x_from, int y_from, int x_to, int y_to, int dir);
int check_step(int x_from, int y_from, int x_to, int y_to, int dir);
int is_jumper(int x, int y);
int is_in_bound(int x, int y);
int opponent_piece(int x, int y);
int opponent_king(int x, int y);