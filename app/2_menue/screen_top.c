// module
#include <ncurses.h>

#include "screen_top.h"
#include "../boolean.h"
#include "../define.h"

void display_top(int position);

int screen_top(void) {
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    clear();
    timeout(0);
    int position = 1;
    while (true) {
        int ch = getch();
        switch(ch){
            case KEY_UP: //↑
                if (position > 1) {
                    position--;
                }else{
                    beep();
                }
                break;
            case KEY_DOWN: //↓
                if (position < 3) {
                    position++;
                }else{
                    beep();
                }
                break;
            case ENTER: //enter
                if (position == 1){ //start
                    return OPPONENT;
                }else if (position == 2){ //help
                    return HELP;
                }else if (position == 3){ //exit
                    mode = EXIT;
                    return EXIT;
                }
                break;
            case ESCAPE: // escape
                return EXIT;
            case SPACE: // space
                return OPPONENT;
                default:
                break;
        }
        display_top(position);

    }

}

void display_top(int position){
    attron(A_BOLD);
    attron(COLOR_PAIR(4));
    mvprintw(2, center_x-4, " Driversi");
    mvprintw(29, 135-28, " 矢印キーで操作、Enterで決定");
    attroff(COLOR_PAIR(4));
    attroff(A_BOLD);
    counter++;
    if(counter % 20000 == 0 && flag==1){
        flag = 0;
        counter = 0;
    }
    else if(counter % 20000 == 0 && flag==0){
        flag = 1;
        counter = 0;
    }
    if(position == 1 && flag == 1){
        attron(COLOR_PAIR(1));
        mvprintw(center_y-5, center_x-10, "　　　　　　　　　　　");
        mvprintw(center_y-4, center_x-10, "　　対戦相手を選択　　");
        mvprintw(center_y-3, center_x-10, "　　　　　　　　　　　");
        attroff(COLOR_PAIR(1));
    }else{
        attron(COLOR_PAIR(2));
        mvprintw(center_y-5, center_x-10, "　　　　　　　　　　　");
        mvprintw(center_y-4, center_x-10, "　　対戦相手を選択　　");
        mvprintw(center_y-3, center_x-10, "　　　　　　　　　　　");
        attroff(COLOR_PAIR(2));
    }
    if(position == 2 && flag == 1){
        attron(COLOR_PAIR(1));
        mvprintw(center_y-1, center_x-10, "　　　　　　　　　　　");
        mvprintw(center_y,   center_x-10, "　　　　ヘルプ　　　　");
        mvprintw(center_y+1, center_x-10, "　　　　　　　　　　　");
        attroff(COLOR_PAIR(1));
    }else   {
        attron(COLOR_PAIR(2));
        mvprintw(center_y-1, center_x-10, "　　　　　　　　　　　");
        mvprintw(center_y,   center_x-10, "　　　　ヘルプ　　　　");
        mvprintw(center_y+1, center_x-10, "　　　　　　　　　　　");
        attroff(COLOR_PAIR(2));
    }
    if(position == 3 && flag == 1){
        attron(COLOR_PAIR(1));
        mvprintw(center_y+3, center_x-10, "　　　　　　　　　　　");
        mvprintw(center_y+4, center_x-10, "　　　　 終了 　　　　");
        mvprintw(center_y+5, center_x-10, "　　　　　　　　　　　");
        attroff(COLOR_PAIR(1));
    }else{
        attron(COLOR_PAIR(2));
        mvprintw(center_y+3, center_x-10, "　　　　　　　　　　　");
        mvprintw(center_y+4, center_x-10, "　　　　 終了 　　　　");
        mvprintw(center_y+5, center_x-10, "　　　　　　　　　　　");
        attroff(COLOR_PAIR(2));
    }
    refresh();
    return;
}
