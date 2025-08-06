#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#include "start_game.h"
#include "game_init_dis.h"
#include "game_run.h"
#include "game_judge.h"
#include "../define.h"
#include "../boolean.h"


#define CURSOR_PAIR 15

// ヘルパー関数
boolean is_board_full() {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (Go[y][x] == GO_EMPTY) {
                return false;
            }
        }
    }
    return true;
}


void start_game(void){
    init_pair(WHITE, COLOR_WHITE, COLOR_GREEN);
    init_pair(BLACK, COLOR_BLACK, COLOR_GREEN);
    init_pair(12, COLOR_BLACK, COLOR_WHITE);
    init_pair(13,COLOR_WHITE, COLOR_BLUE);
    init_pair(14, COLOR_YELLOW, COLOR_BLACK);
    init_pair(15, COLOR_WHITE, COLOR_RED);
    init_pair(16, COLOR_BLACK, COLOR_RED);
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    // 初期化
    memset(Go, GO_EMPTY, sizeof(Go));
    Go[4][4] = 1;
    Go[4][3] = -1;
    Go[3][4] = -1;
    Go[3][3] = 1;

    game_init_dis();
        timeout(0);


    while (true) {

        int ch = getch();
        if (ch == ESCAPE) {
            mvprintw(2, 0, "ゲームを中断します...");
            refresh();
            sleep(1);
            return;
        }

        int result = game_run();


        boolean game_over = false;


        if (result == 1) {
            move(0, 0);
            clrtoeol();
            mvprintw(0, 0, "両者パスのため、ゲームを終了します。");
            game_over = true;
        }

        else if (result == -1) {
            move(0, 0);
            clrtoeol();
            mvprintw(0, 0, "通信エラーが発生しました。ゲームを終了します。");
            refresh();
            sleep(2);
            return;
        }

        else if (is_board_full()) {
            move(0, 0);
            clrtoeol();
            mvprintw(0, 0, "盤面が埋まりました。ゲームを終了します。");
            game_over = true;
        }

        if (game_over) {
            refresh();
            sleep(2);
            break;
        }
        napms(100);
    }


    game_judge();
    timeout(-1);
    getch();
}
