#include <ncurses.h>
#include <unistd.h>

#include "game_init_dis.h"

#include "../define.h"

void game_init_dis(void){
    int h = -1;
    int w = -1;
    attron(A_BOLD);
    attron(COLOR_PAIR(BLACK));

        while (h < 16){
            while (w < 16){
                if (h == -1 && w == -1){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_ULCORNER);
                }else if (h == 15 && w == -1){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_URCORNER);
                }else if (h == -1 && w == 15){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_LLCORNER);
                }else if (h == 15 && w == 15){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_LRCORNER);
                }else if (w == -1 && h % 2 == 1){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_TTEE);
                }else if (w == 15 && h % 2 == 1){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_BTEE);
                }else if (h == -1 && w % 2 == 1){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_LTEE);
                }else if (h == 15 && w % 2 == 1){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_RTEE);
                }else if (h == -1)  {
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_VLINE);
                }else if (h == 15){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_VLINE);
                }else if (w == -1){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_HLINE);
                }else if (w == 15){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_HLINE);
                }else if (h % 2 == 1 && w % 2 == 1){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_PLUS);
                }else if (h % 2 == 1){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_VLINE);
                }else if (w % 2 == 1){
                    mvaddch(Go_S_y + w, Go_S_x + h, ACS_HLINE);
                }else{
                    mvprintw(Go_S_y + w, Go_S_x + h, "　");
                }
                w++;
            }
            w = -1;
            h++;
        }
    attroff(COLOR_PAIR(BLACK));
    for (int i = 0; i < 8;i++){
        mvprintw(Go_S_y+i*2, Go_S_x -3, "%d", i + 1);
    }
    for (int i = 0; i < 8;i++){
        mvprintw(Go_S_y-2, Go_S_x + i*4+2, "%c", i + 'A');
    }

    attron(COLOR_PAIR(12));
    mvprintw(2, 95, "　　　　　　　　　　　　　　 ");
    mvprintw(3,95,"　↑↓→←   : 移動　　　　　");
    mvprintw(4,95,"　Enter　　  : 決定　　　　　");
    mvprintw(5,95,"　Space　　  : マスのヘルプ　");
    mvprintw(6,95,"　Escape　　 : おわる　　　　");
    mvprintw(7, 95, "　　　　　　　　　　　　　　 ");
    attroff(COLOR_PAIR(12));
    attron(COLOR_PAIR(13));
    int black_count = 0;
    int white_count = 0;
    mvprintw(5, 46, "　　　　 　");
    mvprintw(6,46,"　黒 : %2d　", black_count);
    mvprintw(7,46,"　白 : %2d　", white_count);
    mvprintw(8, 46, "　　　 　　");
    attroff(COLOR_PAIR(13));
    attron(COLOR_PAIR(14));
    mvprintw(MESSAGE_AREA_Y-1, MESSAGE_AREA_X*2 + 1, "メッセージエリア");
    mvprintw(LOG_AREA_Y-1, LOG_AREA_X + 1, "ログエリア");
    mvaddch(MESSAGE_AREA_Y, MESSAGE_AREA_X, ACS_ULCORNER);
    mvaddch(MESSAGE_AREA_Y, MESSAGE_AREA_X + MESSAGE_AREA_WIDTH - 1, ACS_URCORNER);
    mvaddch(MESSAGE_AREA_Y + MESSAGE_AREA_HEIGHT - 1, MESSAGE_AREA_X, ACS_LLCORNER);
    mvaddch(MESSAGE_AREA_Y + MESSAGE_AREA_HEIGHT - 1, MESSAGE_AREA_X + MESSAGE_AREA_WIDTH - 1, ACS_LRCORNER);
    for (int i = 1; i < MESSAGE_AREA_WIDTH - 1; i++) {
        mvaddch(MESSAGE_AREA_Y, MESSAGE_AREA_X + i, ACS_HLINE);
        mvaddch(MESSAGE_AREA_Y + MESSAGE_AREA_HEIGHT - 1, MESSAGE_AREA_X + i, ACS_HLINE);
    }

    mvaddch(LOG_AREA_Y, LOG_AREA_X, ACS_ULCORNER);
    mvaddch(LOG_AREA_Y, LOG_AREA_X + LOG_AREA_WIDTH - 1, ACS_URCORNER);
    mvaddch(LOG_AREA_Y + LOG_AREA_HEIGHT - 1, LOG_AREA_X, ACS_LLCORNER);
    mvaddch(LOG_AREA_Y + LOG_AREA_HEIGHT - 1, LOG_AREA_X + LOG_AREA_WIDTH - 1, ACS_LRCORNER);
    for (int i = 1; i < LOG_AREA_WIDTH - 1; i++) {
        mvaddch(LOG_AREA_Y, LOG_AREA_X + i, ACS_HLINE);
        mvaddch(LOG_AREA_Y + LOG_AREA_HEIGHT - 1, LOG_AREA_X + i, ACS_HLINE);
    }

    attroff(COLOR_PAIR(14));
    attroff(A_BOLD);


    refresh();
    attron(A_BOLD);
    attron(COLOR_PAIR(WHITE));
    mvprintw(Go_S_y+4*2 ,Go_S_x+3*3+4, "●");

    attroff(COLOR_PAIR(WHITE));
    attron(COLOR_PAIR(BLACK));
    mvprintw(Go_S_y+3*2 ,Go_S_x+3*3+4, "●");

    attroff(COLOR_PAIR(BLACK));
    refresh();
    attron(COLOR_PAIR(WHITE));
    mvprintw(Go_S_y+3*2 ,Go_S_x+4*3+5, "●");

    attroff(COLOR_PAIR(WHITE));
    attron(COLOR_PAIR(BLACK));
    mvprintw(Go_S_y+4*2 ,Go_S_x+4*3+5, "●");

    attroff(COLOR_PAIR(BLACK));
    refresh();
}
