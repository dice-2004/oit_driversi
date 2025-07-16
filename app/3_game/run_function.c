// function
#include <ncurses.h>
#include <unistd.h>

#include "run_function.h"
#include "game_tips.h"
#include "../define.h"
#include ""


void run_select_area(int select_area[]) {
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    select_area[0] = 0; // x
    select_area[1] = 0; // y
    while(true){
        int ch = getch();
        switch(ch){
            case KEY_UP:
                if(select_area[1] > 0) {
                    select_area[1]--;
                } else {
                    beep();
                }
            case KEY_DOWN:
                if(select_area[1] < 7) {
                    select_area[1]++;
                } else {
                    beep();
                }
            case KEY_LEFT:
                if(select_area[0] > 0) {
                    select_area[0]--;
                } else {
                    beep();
                }
            case KEY_RIGHT:
                if(select_area[0] < 7) {
                    select_area[0]++;
                } else {
                    beep();
                }
            case SPACE:

            case ENTER:
                if(placeable_GO[select_area[1]][select_area[0]] == 0) {
                    return;
                } else {
                    // 置けない
                    beep();
                }
        }
    }
}

void run_update_area(int coordinate[],int player){
    Go[coordinate[1]][coordinate[0]] = player;

    for (int i = 0; i < 8;i++){
        int turn_counter = 0;
        int nx = coordinate[0] + dx[i];
        int ny = coordinate[1] + dy[i];
        while(true){
            if(nx < 0 || nx >= 8 || ny < 0 || ny >= 8 || Go[nx][ny] == GO_EMPTY) {
                turn_counter = 0;
                break;
            }
            if(Go[nx][ny] == player) {
                break;
            }
            if(Go[nx][ny] == -player) {
                turn_counter++;
                nx += dx[i];
                ny += dy[i];
            }
        }

        if(turn_counter > 0) {
            nx = coordinate[0];
            ny = coordinate[1];
            for(int j = 0; j < turn_counter; j++) {
                nx += dx[i];
                ny += dy[i];
                Go[nx][ny] = player;
            }
        }
    }
}

void run_update_display(void){
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(Go[i][j] == GO_BLACK) {
                attron(COLOR_PAIR(BLACK));
                mvprintw(Go_S_y + i * 2, Go_S_x + j * 3 + (j+1), "●");
                attroff(COLOR_PAIR(BLACK));
            } else if(Go[i][j] == GO_WHITE) {
                attron(COLOR_PAIR(WHITE));
                mvprintw(Go_S_y + i * 2, Go_S_x + j * 3 + (j+1), "●");
                attroff(COLOR_PAIR(WHITE));
            } else {
                mvprintw(Go_S_y + i * 2, Go_S_x + j * 3 + (j+1), "　");
            }
        }
    }
}

// return x,y,pass_flag mode flag --> 1:pass, 0: not pass -1:error -2:disconnect
int* run_SeRe_data(int coordinate[],int mode){
    const size_t data_size = sizeof(int) * 3;

    if(mode == SEND){
        int serialized_data[3];
        for(int i = 0; i < 3; i++){
            serialized_data[i] = htonl(coordinate[i]);
        }
        if(write(connection_fd, serialized_data, data_size) == -1) {
            // error
            coordinate[0] = -1;
            coordinate[1] = -1;
            coordinate[2] = -1;
        }
    } else if(mode == RECEIVE){
        int serialized_data[3];
        ssize_t body = read(connection_fd, serialized_data, data_size);
        if(body == -1){
            // error
            serialized_data[0] = -1;
            serialized_data[1] = -1;
            serialized_data[2] = -1;
        }else if(body == 0){
            // disconnect
            serialized_data[0] = -2;
            serialized_data[1] = -2;
            serialized_data[2] = -2;
        }else{
            for (int i = 0; i < 3; i++){
                serialized_data[i] = ntohl(serialized_data[i]);
            }
        }
    }
    return coordinate;
}
