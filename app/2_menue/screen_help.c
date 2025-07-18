// module
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#include "screen_help.h"
#include "../boolean.h"
// #include "../define.h"



void display_help(void);

int screen_help(void){
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    clear();
    timeout(0);
    int line = 0;
    fp=fopen(FILE_NAME, "r");
    if(fp == NULL) {
        mvprintw(center_y, center_x, "ヘルプを表示できません");
        refresh();
        sleep(2);
        return TOP;
    }
    while(fgets(help_text[line], FILE_CHARS, fp) != NULL && line < FILE_LINE) {
        help_text[line][strcspn(help_text[line], "\n")] = 0;
        line++;
    }


    display_help();

    while (true) {
        int ch = getch();
        if (ch == ENTER) { // enter
            return TOP;
        }
    }
}

void display_help(void){
    clear();
    attron(A_BOLD);
    mvprintw(2, center_x-4, "  ヘルプ  ");
    attron(A_BOLD);
    for (int i = 0; i < FILE_LINE; i++) {
        if(i==0 || i==10){
            attron(COLOR_PAIR(3));
        }else{
            attron(COLOR_PAIR(4));
        }
        mvprintw(center_y + i-10, center_x-37, "%s", help_text[i]);
        if(i==0 || i==10){
            attroff(COLOR_PAIR(3));
        }else{
            attroff(COLOR_PAIR(4));
        }
    }
    attroff(A_BOLD);
}
