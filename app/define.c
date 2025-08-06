#include "define.h"
#include <stdio.h>
int mode = 0;

int center_y;
int center_x;
int counter = 0;
int flag = 0; // 1-> on, 0-> off

FILE *fp;
char help_text[FILE_LINE][FILE_CHARS];
int connection_fd = -1;

int Go[8][8] = {0}; // 0: 空き, 1: 黒, -1: 白
int Go_S_x = 10;
int Go_S_y = 3;
int placeable_GO[8][8] = {0};
// Aは＋１
// Bは＋２
// Cは＋３
// A,B,Cは3倍
// 1,2,3は2倍

const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int currentflag = 0; // 1-> pass, 0-> not pass
int preflag = 0; // 1-> pass, 0-> not pass
char log_area_data[LOG_AREA_HEIGHT - 2][LOG_AREA_WIDTH] = {0};

// 現在の手の情報を格納するグローバル構造体
MoveData current_move;
