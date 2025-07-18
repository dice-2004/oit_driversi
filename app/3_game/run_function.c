// function
#include <ncurses.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#include "run_function.h"
#include "game_judge.h"
#include "game_tips.h"
// #include "../define.h"
#include "../boolean.h"


#define CURSOR_PAIR_W 15
#define CURSOR_PAIR_B 16

// ヘルプ関数
void draw_cursor(int y, int x, boolean is_cursor) {
    int screen_y = Go_S_y + y * 2;
    int screen_x = Go_S_x + x * 4 + 1;


    if (Go[y][x] == GO_BLACK) {
        if(!is_cursor){
            attron(COLOR_PAIR(BLACK));
        }else {
            attron(COLOR_PAIR(CURSOR_PAIR_B));
        }
        mvprintw(screen_y, screen_x, "●");
        if(!is_cursor){
            attroff(COLOR_PAIR(BLACK));
        }else {
            attroff(COLOR_PAIR(CURSOR_PAIR_B));
        }
    } else if (Go[y][x] == GO_WHITE) {
        if(!is_cursor){
            attron(COLOR_PAIR(WHITE));
        }else {
            attron(COLOR_PAIR(CURSOR_PAIR_W));
        }
        mvprintw(screen_y, screen_x, "●");
        if(!is_cursor){
            attroff(COLOR_PAIR(WHITE));
        }else {
            attroff(COLOR_PAIR(CURSOR_PAIR_W));
        }
    } else {
        if(!is_cursor){
            attron(COLOR_PAIR(BLACK));
        }else {
            attron(COLOR_PAIR(CURSOR_PAIR_B));
        }
        mvprintw(screen_y, screen_x, "　");
        if(!is_cursor){
            attroff(COLOR_PAIR(BLACK));
        }else {
            attroff(COLOR_PAIR(CURSOR_PAIR_B));
        }
    }

    move(screen_y, screen_x + 1);
    refresh();
}


void run_select_area(int select_area[]) {
    cbreak();
    noecho();
    keypad(stdscr, TRUE);


    select_area[0] = 3; // 初期位置x
    select_area[1] = 3; // 初期位置y
    int old_x, old_y;

    draw_cursor(select_area[1], select_area[0], true);

    while(true){
        int ch = getch();

        old_x = select_area[0];
        old_y = select_area[1];

        switch(ch){
            case KEY_UP:
                if(select_area[1] > 0) select_area[1]--; else beep();
                break;
            case KEY_DOWN:
                if(select_area[1] < 7) select_area[1]++; else beep();
                break;
            case KEY_LEFT:
                if(select_area[0] > 0) select_area[0]--; else beep();
                break;
            case KEY_RIGHT:
                if(select_area[0] < 7) select_area[0]++; else beep();
                break;
            case SPACE:
                game_tips();
                break;
            case ENTER:

                if(placeable_GO[select_area[1]][select_area[0]] == 1) {
                    draw_cursor(select_area[1], select_area[0], false);
                    return;
                } else {
                    beep();
                }
                break;
        }


        if (old_x != select_area[0] || old_y != select_area[1]) {
            draw_cursor(old_y, old_x, false); // 古いカーソル
            draw_cursor(select_area[1], select_area[0], true); // 新しいカーソル
        }
        refresh();
    }
}

void run_update_area(int coordinate[],int player){
    Go[coordinate[1]][coordinate[0]] = player;

    for (int i = 0; i < 8;i++){
        int turn_counter = 0;
        int nx = coordinate[0] + dx[i];
        int ny = coordinate[1] + dy[i];
        while(true){
            if(nx < 0 || nx >= 8 || ny < 0 || ny >= 8 || Go[ny][nx] == GO_EMPTY) {
                turn_counter = 0;
                break;
            }
            if(Go[ny][nx] == player) {
                break;
            }
            if(Go[ny][nx] == -player) {
                turn_counter++;
                nx += dx[i];
                ny += dy[i];
            }
        }

        if(turn_counter > 0) {
            nx = coordinate[0];
            ny = coordinate[1];
            for(int j = 0; j < turn_counter; j++) {
                ny += dy[i];
                nx += dx[i];
                Go[ny][nx] = player;
            }
        }
    }
}

void run_update_display(void){
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(Go[i][j] == GO_BLACK) {
                attron(COLOR_PAIR(BLACK));
                mvprintw(Go_S_y + i * 2, Go_S_x + j * 4 + 1, "●");
                attroff(COLOR_PAIR(BLACK));
            } else if(Go[i][j] == GO_WHITE) {
                attron(COLOR_PAIR(WHITE));
                mvprintw(Go_S_y + i * 2, Go_S_x + j * 4 + 1, "●");
                attroff(COLOR_PAIR(WHITE));
            } else {
                attron(COLOR_PAIR(BLACK));
                mvprintw(Go_S_y + i * 2, Go_S_x + j * 4 + 1, "　");
                attroff(COLOR_PAIR(BLACK));
            }
            refresh();
        }
    }


    attroff(COLOR_PAIR(BLACK));
    attroff(A_BOLD);
    int count[2] = {0, 0}; // count[0] = 黒, count[1] = 白
    count_stone(count);
    attron(COLOR_PAIR(13));
    mvprintw(6,46,"　黒 : %2d　", count[0]);
    mvprintw(7,46,"　白 : %2d　", count[1]);
    attroff(COLOR_PAIR(13));
}

void run_SeRe_data(int coordinate[],int mode){
    const size_t data_size = sizeof(int) * 3;

    if(mode == SEND){
        int serialized_data[3];
        for(int i = 0; i < 3; i++){
            serialized_data[i] = htonl(coordinate[i]);
        }
        if(write(connection_fd, serialized_data, data_size) == -1) {
            coordinate[2] = -1; // エラー
        }
    } else if(mode == RECEIVE){
        int serialized_data[3];
        ssize_t body = read(connection_fd, serialized_data, data_size);
        if(body <= 0){
            coordinate[2] = -2; // エラーまたは切断
        }else{
            for (int i = 0; i < 3; i++){
                coordinate[i] = ntohl(serialized_data[i]);
            }
        }
    }
}

void update_log_area(void) {
    char log_buffer[LOG_AREA_WIDTH];
    const char* player_name;


    if (current_move.player_color == GO_BLACK) {
        player_name = "黒";
    } else {
        player_name = "白";
    }

    if (current_move.is_pass) {
        sprintf(log_buffer, "%sがパスしました", player_name);
    } else {
        char col_char = 'A' + current_move.x;
        int row_num = current_move.y + 1;
        sprintf(log_buffer, "%sが%c%dに置かれました", player_name, col_char, row_num);
    }


    for (int i = 0; i < LOG_AREA_HEIGHT - 3; i++) {
        strcpy(log_area_data[i], log_area_data[i + 1]);
    }

    strncpy(log_area_data[LOG_AREA_HEIGHT - 3], log_buffer, LOG_AREA_WIDTH - 1);
    log_area_data[LOG_AREA_HEIGHT - 3][LOG_AREA_WIDTH - 1] = '\0';


    for (int i = 0; i < LOG_AREA_HEIGHT - 2; i++) {
        mvprintw(LOG_AREA_Y + 1 + i, LOG_AREA_X + 3, "%-32s", " ");
    }

    for (int i = 0; i < LOG_AREA_HEIGHT - 2; i++) {
        mvprintw(LOG_AREA_Y + 1 + i, LOG_AREA_X + 3, "%s", log_area_data[i]);
    }
    refresh();
}
