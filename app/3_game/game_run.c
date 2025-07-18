#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include "game_run.h"
#include "run_function.h"
#include "game_serch_placeable.h"
#include "game_algo.h"
// #include "../define.h"
// #include "../boolean.h"

int game_run(void){
    int select_area_flag[3] = {-1, -1, 0};
    int opponent_move[3] = {-1, -1, 0};

    if (mode == HOST || mode == CPU) {
        // host or CPU
        game_search_placeable(GO_BLACK);
        if (preflag == 1 && currentflag == 1) {
            return 1;
        }

        select_area_flag[2] = currentflag;
        if (currentflag == 0) { // 置ける
            run_select_area(select_area_flag);
            run_update_area(select_area_flag, GO_BLACK);
            run_update_display();
        }
// log
        current_move.player_color = GO_BLACK;
        current_move.x = select_area_flag[0];
        current_move.y = select_area_flag[1];
        current_move.is_pass = (currentflag == 1);
        update_log_area();


        preflag = currentflag;

        if (mode == HOST) {
            run_SeRe_data(select_area_flag, SEND);
        }
    }


    if (mode == GUEST) {
        // GUEST
        run_SeRe_data(opponent_move, RECEIVE);
        if(opponent_move[2] < 0) return -1;

// log
        current_move.player_color = GO_BLACK;
        current_move.x = opponent_move[0];
        current_move.y = opponent_move[1];
        current_move.is_pass = (opponent_move[2] == 1);
        update_log_area();

        if (opponent_move[2] == 0) {
            run_update_area(opponent_move, GO_BLACK);
            run_update_display();
        }

        preflag = opponent_move[2];
        game_search_placeable(GO_WHITE);

        if (preflag == 1 && currentflag == 1) {
            select_area_flag[2] = 1;
            run_SeRe_data(select_area_flag, SEND);
            return 1;
        }

        select_area_flag[2] = currentflag;
        if (currentflag == 0) { // 置ける
            run_select_area(select_area_flag);
            run_update_area(select_area_flag, GO_WHITE);
            run_update_display();
        }

// log
        current_move.player_color = GO_WHITE;
        current_move.x = select_area_flag[0];
        current_move.y = select_area_flag[1];
        current_move.is_pass = (currentflag == 1);
        update_log_area();


        run_SeRe_data(select_area_flag, SEND);

    } else { // HOST or CPU
        if (mode == HOST) {
            run_SeRe_data(opponent_move, RECEIVE);
            if(opponent_move[2] < 0) return -1;
            currentflag = opponent_move[2];
        } else { // CPU
            game_search_placeable(GO_WHITE);
        }

        if (preflag == 1 && currentflag == 1) {
            return 1;
        }

        if (currentflag == 0) { // 置ける
            if (mode == HOST) {
                run_update_area(opponent_move, GO_WHITE);
            } else { // CPU
                game_algo(opponent_move);
                run_update_area(opponent_move, GO_WHITE);
            }
            run_update_display();
        }

// log
        current_move.player_color = GO_WHITE;
        current_move.x = opponent_move[0];
        current_move.y = opponent_move[1];
        current_move.is_pass = (currentflag == 1);
        update_log_area();


        preflag = currentflag;
    }

    return 0;
}
