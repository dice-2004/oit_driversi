// module

#include <ncurses.h>
#include <unistd.h>

#include "start_game.h"
#include "game_init_dis.h"
#include "game_run.h"
#include "game_judge.h"
#include "../define.h"

void start_game(void){
    init_pair(WHITE, COLOR_WHITE, COLOR_GREEN);
    init_pair(BLACK, COLOR_BLACK, COLOR_GREEN);
    init_pair(12, COLOR_BLACK, COLOR_WHITE);
    init_pair(13,COLOR_WHITE, COLOR_BLUE);
    init_pair(14, COLOR_YELLOW, COLOR_BLACK);
    clear();
    noecho();
    cbreak();
    int pass_flag = 0;
    Go[4][4] = 1;
    Go[4][3] = -1;
    Go[3][4] = -1;
    Go[3][3] = 1;
    game_init_dis();
    keypad(stdscr, TRUE);

    while (true) {
        int ch = getch();
        if(ch == ESCAPE){
            mvprintw(0, 0, "ESCAPEキーが押されました。ゲームを終了します。");
            refresh();
            return;
        }else if(pass_flag == 3){
            break;
        }else if(pass_flag == -1){
            return;
        }
        // pass_flag = game_run();
    }


}
