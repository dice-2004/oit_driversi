// module
#include <ncurses.h>


#include "screen_opponent.h"
#include "../boolean.h"
#include "../define.h"

void display_opponent(int position);

int screen_opponent(void) {
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
                if (position < 2) {
                    position++;
                }else{
                    beep();
                }
                break;
            case ENTER: //enter
                if (position == 1){

                    mode = CPU;
                    return EXIT;
                }else if (position == 2){
                    return CONNECT;
                }
                break;
            case ESCAPE: // escape
                return TOP;
            default:
                break;
        }
        display_opponent(position);
    }
}

void display_opponent(int position) {
    attron(A_BOLD);
    attron(COLOR_PAIR(4));
    mvprintw(28, 135-28, " 矢印キーで操作、Enterで決定");
    mvprintw(29, 135-29, " Escapeでメインメニューに戻る");
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
        mvprintw(center_y-3, center_x-10, "　　　　　　　　　　　");
        mvprintw(center_y-2, center_x-10, "　　コンピュータと　　");
        mvprintw(center_y-1, center_x-10, "　　　　　　　　　　　");
        attroff(COLOR_PAIR(1));
    } else {
        attron(COLOR_PAIR(2));
        mvprintw(center_y-3, center_x-10, "　　　　　　　　　　　");
        mvprintw(center_y-2, center_x-10, "　　コンピュータと　　");
        mvprintw(center_y-1, center_x-10, "　　　　　　　　　　　");
        attroff(COLOR_PAIR(2));
    }

    if(position == 2 && flag == 1){
        attron(COLOR_PAIR(1));
        mvprintw(center_y+1, center_x-10, "　　　　　　　　　　　");
        mvprintw(center_y+2, center_x-10, "　　　 だれかと 　　　");
        mvprintw(center_y+3, center_x-10, "　　　　　　　　　　　");
        attroff(COLOR_PAIR(1));
    } else {
        attron(COLOR_PAIR(2));
        mvprintw(center_y+1, center_x-10, "　　　　　　　　　　　");
        mvprintw(center_y+2, center_x-10, "　　　 だれかと 　　　");
        mvprintw(center_y+3, center_x-10, "　　　　　　　　　　　");
        attroff(COLOR_PAIR(2));
    }
}
