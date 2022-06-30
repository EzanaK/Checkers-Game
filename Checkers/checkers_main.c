/*
 * Ezana Kebede
 * 02/17/21
 * ENEE150
 * Checkers game
*/

#include "checkers.h"
#include <stdio.h>
#include <stdlib.h>

int the_board[BOARD_SIZE][BOARD_SIZE];

int main() {
    initialize_board();
    int turn = 0;
    int color;
    while (TRUE) {
        // Game control
        int multiple_jumps = TRUE;
        int jump_count = 0; // > 1 if consecutive jumps can be made by one piece
        int multi_jump_x; // x value of multi-jump piece
        int multi_jump_y; // y value of multi-jump piece
        while (multiple_jumps) {
            // Repeats if multiple jumps are available
            print_board();
            if (turn % 2) {
                color = WHITE;
                printf("WHITE's move:  ");
            } else {
                color = RED;
                printf("RED's move:  ");
            }
            fflush(stdout);
            int x_from, y_from, x_to, y_to;
            scanf("%d %d %d %d", &x_from, &y_from, &x_to, &y_to);
            if (x_from == 0 && y_from == 0 && x_to == 0 && y_to == 0) {
                exit(0);
            }
            int jump_ability = jump_exists(color);
            int move_validity = check_move(color, x_from, y_from, x_to, y_to, jump_ability);
            if (jump_count > 0 && (x_from != multi_jump_x || y_from != multi_jump_y)) {
                move_validity = INVALID_MOVE;
            }
            while (move_validity == INVALID_MOVE) {
                // Loops until a valid move is given
                printf("INVALID MOVE.  TRY AGAIN!!\n");
                if (turn % 2) {
                    color = WHITE;
                    printf("WHITE's move:  ");
                } else {
                    color = RED;
                    printf("RED's move:  ");
                }
                fflush(stdout);
                scanf("%d %d %d %d", &x_from, &y_from, &x_to, &y_to);
                if (x_from == 0 && y_from == 0 && x_to == 0 && y_to == 0) {
                    exit(0);
                }
                move_validity = check_move(color, x_from, y_from, x_to, y_to, jump_ability);
                if (jump_count > 0 && (x_from != multi_jump_x || y_from != multi_jump_y)) {
                    move_validity = INVALID_MOVE;
                }
            }
            move_piece(color, x_from, y_from, x_to, y_to, jump_ability);
            printf("\n");
            if (jump_ability == TRUE && is_jumper(x_to, y_to)) { // Determines if multiple jumps are available
                multiple_jumps = TRUE;
                jump_count++;
                multi_jump_x = x_to;
                multi_jump_y = y_to;
            } else {
                multiple_jumps = FALSE;
            }
        }
        turn++; // Changes turn
    }
}
