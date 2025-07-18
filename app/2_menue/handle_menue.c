// module

#include <ncurses.h>

#include "handle_menue.h"
#include "screen_top.h"
#include "screen_opponent.h"
#include "screen_help.h"
#include "screen_connect.h"
#include "screen_host.h"
#include "screen_guest.h"
#include "../boolean.h"
// #include "../define.h"



void handle_menue(void){
    int target = 1;
    mode = 0;
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_YELLOW);
    clear();
    getmaxyx(stdscr, center_y, center_x);
    center_y /= 2;
    center_x /= 2;

    while (true) {
        switch (target) {
            case TOP:
                target = screen_top();
                break;
            case OPPONENT:
                target = screen_opponent();
                break;
            case HELP:
                target = screen_help();
                break;
            case CONNECT:
                target = screen_connect();
                break;
            case HOST:
                target = screen_host();
                break;
            case GUEST:
                target = screen_guest();
                break;
            case EXIT:
                return;
            default:
                break;
        }

    }
}
