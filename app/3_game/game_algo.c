#include <stdlib.h>
#include <time.h>

#include "game_algo.h"
#include"../define.h"


void game_algo(int select_area[]){
    typedef struct {
        int x;
        int y;
    } Point;

    Point corner_moves[4];
    int corner_count = 0;
    Point edge_moves[28];
    int edge_count = 0;
    Point other_moves[64];
    int other_count = 0;

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (placeable_GO[y][x] == 1) {
                // 角
                if ((x == 0 || x == 7) && (y == 0 || y == 7)) {
                    corner_moves[corner_count].x = x;
                    corner_moves[corner_count].y = y;
                    corner_count++;
                }
                // 辺
                else if (x == 0 || x == 7 || y == 0 || y == 7) {
                    edge_moves[edge_count].x = x;
                    edge_moves[edge_count].y = y;
                    edge_count++;
                }
                // その他
                else {
                    other_moves[other_count].x = x;
                    other_moves[other_count].y = y;
                    other_count++;
                }
            }
        }
    }

    if (corner_count > 0) {//角
        int choice = rand() % corner_count;
        select_area[0] = corner_moves[choice].x;
        select_area[1] = corner_moves[choice].y;
        return;
    }

    if (edge_count > 0) {// 辺
        int choice = rand() % edge_count;
        select_area[0] = edge_moves[choice].x;
        select_area[1] = edge_moves[choice].y;
        return;
    }

    if (other_count > 0) {　// その他
        int choice = rand() % other_count;
        select_area[0] = other_moves[choice].x;
        select_area[1] = other_moves[choice].y;
        return;
    }

    select_area[0] = -1;
    select_area[1] = -1;
    select_area[2] = 1;
}
