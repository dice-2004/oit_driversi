#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include "game_tips.h"
#include "game_algo.h"
#include "../define.h"

// 残り
static int tips_remaining = 5;


static char tip_messages[MESSAGE_AREA_HEIGHT - 2][MESSAGE_AREA_WIDTH];

// サポート関数
static void update_tip_messages(const char* msg) {

    for (int i = 0; i < MESSAGE_AREA_HEIGHT - 3; i++) {
        strcpy(tip_messages[i], tip_messages[i + 1]);
    }

    strncpy(tip_messages[MESSAGE_AREA_HEIGHT - 3], msg, MESSAGE_AREA_WIDTH - 1);
    tip_messages[MESSAGE_AREA_HEIGHT - 3][MESSAGE_AREA_WIDTH - 1] = '\0';


    for (int i = 0; i < MESSAGE_AREA_HEIGHT - 2; i++) {
        mvprintw(MESSAGE_AREA_Y + 1 + i, MESSAGE_AREA_X*2+2, "%-32s", " ");
    }

    for (int i = 0; i < MESSAGE_AREA_HEIGHT - 2; i++) {
        mvprintw(MESSAGE_AREA_Y + 1 + i, MESSAGE_AREA_X*2+2, "%s", tip_messages[i]);
    }
    refresh();
}



void game_tips(void) {
    if (tips_remaining <= 0) {
        update_tip_messages("ヒントはもう使えません。");
        beep();
        return;
    }

    int best_move[3] = {-1, -1, 0};


    game_algo(best_move);

    char msg_buffer[MESSAGE_AREA_WIDTH];

    if (best_move[0] == -1) {

        sprintf(msg_buffer, "ヒント: 置ける場所がありません。");
    } else {
        char col_char = 'A' + best_move[0];
        int row_num = best_move[1] + 1;


        sprintf(msg_buffer, "ヒント: %c%dが良い手です。(残り%d回)", col_char, row_num, tips_remaining - 1);

        tips_remaining--;
    }

    update_tip_messages(msg_buffer);
}
