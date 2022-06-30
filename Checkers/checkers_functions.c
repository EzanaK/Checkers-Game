/*
 *Checkers functions
 */

#include "checkers.h"
#include <stdio.h>

void initialize_board() {
    // Puts pieces in initial positions
    int y;
    int x;
    for (y = 0; y < BOARD_SIZE; y++) {
        for (x = 0; x < BOARD_SIZE; x++) {
            if (y < 3) {
                if (y % 2) {
                    if (x % 2) {
                        the_board[y][x] = EMPTY;
                    } else {
                        the_board[y][x] = RED;
                    }
                } else {
                    if (x % 2) {
                        the_board[y][x] = RED;
                    } else {
                        the_board[y][x] = EMPTY;
                    }
                }
            }
            else if (y >=3 && y <=4) {
                the_board[y][x] = EMPTY;
            }
            else {
                if (y % 2) {
                    if (x % 2) {
                        the_board[y][x] = EMPTY;
                    } else {
                        the_board[y][x] = WHITE;
                    }
                } else {
                    if (x % 2) {
                        the_board[y][x] = WHITE;
                    } else {
                        the_board[y][x] = EMPTY;
                    }
                }
            }
        }
    }
}

void print_board() {
    // Prints checkers board
    printf("   0   1   2   3   4   5   6   7 \n");
    int row;
    int row_label = 0;
    for (row = 2; row <= 18; row++) {
        if (row % 2 == 0) {
            printf(" |---|---|---|---|---|---|---|---|\n");
            continue;
        }
        else {
            printf("%d", row_label);
            row_label++;
            int j;
            for (j = 0; j < BOARD_SIZE; j++) {
                printf("|");
                print_piece((row - 3) / 2, j);
            }
            printf("|\n");
        }
    }
    printf("\n");
}

void print_piece(i, j) {
    // Prints individual checkers piece
    int piece = the_board[i][j];
    switch (piece) {
        case EMPTY :
            printf("   ");
            break;
        case RED :
            printf(" r ");
            break;
        case WHITE :
            printf(" w ");
            break;
        case RED_KING :
            printf(" R ");
            break;
        case WHITE_KING :
            printf(" W ");
            break;
    }
}

int jump_exists(int color) {
    // Determines if a jump is available for a player
    int y;
    int x;
    for (y = 0; y < BOARD_SIZE; y++) {
        for (x = 0; x < BOARD_SIZE; x++) {
            if (the_board[y][x] == color || the_board[y][x] == color + 2) {
                if (is_jumper(x, y)) {
                    return TRUE;
                }
            }
            else {
                continue;
            }
        }
    }
    return FALSE;
}

int is_jumper(int x, int y) {
    // Determines if a piece can make a jump
    switch (the_board[y][x]) {
        case EMPTY:
            break;
        case RED:
            if (is_in_bound(x - 1,y + 1)) {
                if (the_board[y + 1][x - 1] == opponent_piece(x, y) || the_board[y + 1][x - 1] == opponent_king(x, y)) {
                    if (is_in_bound(x - 2, y + 2)) {
                        if (the_board[y + 2][x - 2] == EMPTY) {
                            return TRUE;
                        }
                    }
                }
            }
            if (is_in_bound(x + 1,y + 1)) {
                if (the_board[y + 1][x + 1] == opponent_piece(x, y) || the_board[y + 1][x + 1] == opponent_king(x, y)) {
                    if (is_in_bound(x + 2, y + 2)) {
                        if (the_board[y + 2][x + 2] == EMPTY) {
                            return TRUE;
                        }
                    }
                }
            }
            break;
        case RED_KING:
        case WHITE_KING:
            if (is_in_bound(x - 1,y + 1)) {
                if (the_board[y + 1][x - 1] == opponent_piece(x, y) || the_board[y + 1][x - 1] == opponent_king(x, y)) {
                    if (is_in_bound(x - 2, y + 2)) {
                        if (the_board[y + 2][x - 2] == EMPTY) {
                            return TRUE;
                        }
                    }
                }
            }
            if (is_in_bound(x + 1,y + 1)) {
                if (the_board[y + 1][x + 1] == opponent_piece(x, y) || the_board[y + 1][x + 1] == opponent_king(x, y)) {
                    if (is_in_bound(x + 2, y + 2)) {
                        if (the_board[y + 2][x + 2] == EMPTY) {
                            return TRUE;
                        }
                    }
                }
            }
        case WHITE:
            if (is_in_bound(x - 1,y - 1)) {
                if (the_board[y - 1][x - 1] == opponent_piece(x, y) || the_board[y - 1][x - 1] == opponent_king(x, y)) {
                    if (is_in_bound(x - 2, y - 2)) {
                        if (the_board[y - 2][x - 2] == EMPTY) {
                            return TRUE;
                        }
                    }
                }
            }
            if (is_in_bound(x + 1,y - 1)) {
                if (the_board[y - 1][x + 1] == opponent_piece(x, y) || the_board[y - 1][x + 1] == opponent_king(x, y)) {
                    if (is_in_bound(x + 2, y - 2)) {
                        if (the_board[y - 2][x + 2] == EMPTY) {
                            return TRUE;
                        }
                    }
                }
            }
            break;
    }
    return FALSE;
}

int is_in_bound(int x, int y) {
    // Determines if given index is in bounds of the board
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return FALSE;
    }
    return TRUE;
}

int check_move(int color, int x_from, int y_from, int x_to, int y_to, int jump) {
    // Checks if the players move is valid
    if (is_in_bound(x_from, y_from) == FALSE || is_in_bound(x_to, y_to) == FALSE) {
        return INVALID_MOVE;
    }
    if (the_board[y_from][x_from] != color && the_board[y_from][x_from] != color + 2) {
        return INVALID_MOVE;
    }
    if (jump) { // Jump is available and must be performed
        if (check_jump(x_from, y_from, x_to, y_to,y_to - y_from) == INVALID_MOVE) {
            return INVALID_MOVE;
        }
    }
    else {
        if (check_step(x_from, y_from, x_to, y_to,y_to - y_from) == INVALID_MOVE) {
            return INVALID_MOVE;
        }
    }
    return VALID_MOVE;
}

int check_jump(int x_from, int y_from, int x_to, int y_to, int dir) {
    // Checks if the entered move is a valid jumping move
    int piece = the_board[y_from][x_from];
    if (the_board[y_to][x_to] != EMPTY) {
        return INVALID_MOVE;
    }
    if (x_to - x_from != 2 && x_to - x_from != -2) {
        return INVALID_MOVE;
    }
    if (dir == 2) {
        // Piece is moving in positive y direction
        if (piece == WHITE){
            return INVALID_MOVE;
        }
        if (x_to - x_from == -2 && the_board[y_from + 1][x_from - 1] != opponent_piece(x_from, y_from) && the_board[y_from + 1][x_from - 1] != opponent_king(x_from, y_from)) {
            return INVALID_MOVE;
        }
        else if (x_to - x_from == 2 && the_board[y_from + 1][x_from + 1] != opponent_piece(x_from, y_from) && the_board[y_from + 1][x_from + 1] != opponent_king(x_from, y_from)) {
            return INVALID_MOVE;
        }
    }
    else if (dir == -2) {
        // Piece is moving in negative y direction
        if (piece == RED){
            return INVALID_MOVE;
        }
        if (x_to - x_from == -2 && the_board[y_from - 1][x_from - 1] != opponent_piece(x_from, y_from) && the_board[y_from - 1][x_from - 1] != opponent_king(x_from, y_from)) {
            return INVALID_MOVE;
        }
        else if (x_to - x_from == 2 && the_board[y_from - 1][x_from + 1] != opponent_piece(x_from, y_from) && the_board[y_from - 1][x_from + 1] != opponent_king(x_from, y_from)) {
            return INVALID_MOVE;
        }
    }
    else {
        return INVALID_MOVE;
    }
    return VALID_MOVE;
}

int check_step(int x_from, int y_from, int x_to, int y_to, int dir) {
    // Checks if the entered move is a valid stepping move
    int piece = the_board[y_from][x_from];
    if (the_board[y_to][x_to] != EMPTY) {
        return INVALID_MOVE;
    }
    if (x_to - x_from != 1 && x_to - x_from != -1) {
        return INVALID_MOVE;
    }
    if (dir == 1 && piece == WHITE) {
        return INVALID_MOVE;
    }
    else if (dir == -1 && piece == RED) {
        return INVALID_MOVE;
        }
    else if (dir != -1 && dir != 1){
        return INVALID_MOVE;
    }
    return VALID_MOVE;
}

void move_piece(int color, int x_from, int y_from, int x_to, int y_to,int jump) {
    // Performs entered move and modifies board
    color = the_board[y_from][x_from];
    the_board[y_from][x_from] = EMPTY;
    if (jump) {
        // Removes piece being jumped
        if (y_to - y_from == -2 && x_to - x_from == 2) {
            the_board[y_from - 1][x_from + 1] = EMPTY;
        }
        else if (y_to - y_from == -2 && x_to - x_from == -2) {
            the_board[y_from - 1][x_from - 1] = EMPTY;
        }
        else if (y_to - y_from == 2 && x_to - x_from == -2) {
            the_board[y_from + 1][x_from - 1] = EMPTY;
        }
        else if (y_to - y_from == 2 && x_to - x_from == 2) {
            the_board[y_from + 1][x_from + 1] = EMPTY;
        }
    }
    if (y_to == 7 && color == RED) {
        the_board[y_to][x_to] = RED_KING;
    }
    else if (y_to == 0 && color == WHITE) {
        the_board[y_to][x_to] = WHITE_KING;
    }
    else {
        the_board[y_to][x_to] = color;
    }
}

int opponent_piece(int x, int y) {
    // Determines the opponents normal piece
    if (the_board[y][x] == WHITE || the_board[y][x] == WHITE_KING) {
        return RED;
    }
    else {
        return WHITE;
    }
}

int opponent_king(int x, int y) {
    // Determines the opponents king piece
    if (the_board[y][x] == WHITE || the_board[y][x] == WHITE_KING) {
        return RED_KING;
    }
    else {
        return WHITE_KING;
    }
}