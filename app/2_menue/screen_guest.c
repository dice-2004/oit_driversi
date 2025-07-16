// module
#include <ncurses.h>
#include <unistd.h>


#include "screen_guest.h"
#include "observe_connection.h"
#include "../boolean.h"
#include "../define.h"

void display_guest(void);

int screen_guest(void){
    display_guest();
    boolean result =observe_connection(GUEST);
    curs_set(0);
    clear();
    if (result) {

        mvprintw(center_y, center_x-9, "接続に成功しました！");
        refresh();
        sleep(3);
        clear();
        mode = GUEST;
        return EXIT;
    } else {
        mvprintw(center_y, center_x-9, "接続に失敗しました。");
        refresh();
        sleep(3);
        clear();
        return TOP;
    }
}

void display_guest() {
    clear();
    attron(A_BOLD);
    attron(COLOR_PAIR(4));
    mvprintw(29, 135-68, "相手のプレイヤーは「ホストになる」を選択しホストIDを取得して下さい");
    attroff(COLOR_PAIR(4));
    attroff(A_BOLD);

    mvprintw(center_y-3, center_x-18, "相手のホストIDを入力してください: ");
    refresh();
    return;
}
