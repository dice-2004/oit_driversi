// module
#include <ncurses.h>
#include "game_judge.h"
#include "../define.h"

void count_stone(int count[]);
void display_result(int count[]);

//  mode > HOST,CUP 黒 > GUEST 白
void game_judge(void) {
    int count[2] = {0, 0}; // count[0] = 黒, count[1] = 白
    count_stone(count);
    display_result(count);

}

void count_stone(int count[]){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Go[i][j] == 1) {
                count[0]++;
            } else if (Go[i][j] == -1) {
                count[1]++;
            }
        }
    }
}

void display_result(int count[]){
    if(mode == HOST || mode == CPU) {
        if(count[0] > count[1]) {
            attron(COLOR_PAIR(1));
            mvprintw(center_y-1, center_x, "　　　　　");
            mvprintw(center_y, center_x, "　勝利！　");
            mvprintw(center_y+1, center_x, "　　　　　");
            attroff(COLOR_PAIR(1));
        } else if(count[0] < count[1]) {
            attron(COLOR_PAIR(2));
            mvprintw(center_y-1, center_x, "　　　　　　");
            mvprintw(center_y, center_x, "　敗北...　 ");
            mvprintw(center_y+1, center_x, "　　　　　　");
            attroff(COLOR_PAIR(2));
        } else {
            attron(COLOR_PAIR(3));
            mvprintw(center_y-1, center_x, "　　　　　　");
            mvprintw(center_y, center_x, "　引き分け　");
            mvprintw(center_y+1, center_x, "　　　　　　");
            attroff(COLOR_PAIR(3));
        }
    } else if(mode == GUEST) {
        if(count[0] > count[1]) {
            attron(COLOR_PAIR(2));
            mvprintw(center_y-1, center_x, "　　　　　　");
            mvprintw(center_y, center_x, "　敗北...　 ");
            mvprintw(center_y+1, center_x, "　　　　　　");
            attroff(COLOR_PAIR(2));
        } else if(count[0] < count[1]) {
            attron(COLOR_PAIR(1));
            mvprintw(center_y-1, center_x, "　　　　　");
            mvprintw(center_y, center_x, "　勝利！　");
            mvprintw(center_y+1, center_x, "　　　　　");
            attroff(COLOR_PAIR(1));
        } else {
            attron(COLOR_PAIR(3));
            mvprintw(center_y-1, center_x, "　　　　　　");
            mvprintw(center_y, center_x, "　引き分け　");
            mvprintw(center_y+1, center_x, "　　　　　　");
            attroff(COLOR_PAIR(3));
        }

    }
}
