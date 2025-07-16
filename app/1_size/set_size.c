// module
#include <ncurses.h>
#include <string.h>

#include "../boolean.h"
#include "set_size.h"
#include "../define.h"




boolean size_resize(void);


void set_size(void) {

    initscr();
    noecho();
    curs_set(0);
    getmaxyx(stdscr, LINES, COLS);
    if (LINES == SIZE_Y && COLS == SIZE_X) {
        return;
    }


    while (true) {
        if (size_resize()) {
            break;
        }
    }
    return;
}


boolean size_resize(void) {
    clear();

    const char *msg1 = " 画面サイズを設定します。";
    const char *msg2 = "136×30に合わせてください";
    char coords_msg[50];
    sprintf(coords_msg, "横: %d, 縦: %d", COLS, LINES);


    int center_y = LINES / 2;
    int center_x1 = (COLS - strlen(msg1)) / 2;
    int center_x2 = (COLS - strlen(msg2)) / 2;
    int center_x_coords = (COLS - strlen(coords_msg)) / 2;

    mvprintw(center_y - 1, center_x1+6, "%s", msg1);
    mvprintw(center_y,     center_x2+5, "%s", msg2);
    mvprintw(center_y + 1, center_x_coords+1, "%s", coords_msg);

    refresh();

    getch();


    if (LINES == SIZE_Y && COLS == SIZE_X) {
        return true;
    }
    return false;
}
