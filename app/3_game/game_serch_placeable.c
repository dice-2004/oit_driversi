
#include <string.h>

#include   "game_serch_placeable.h"
#include "../define.h"
#include "../boolean.h"

void game_search_placeable(int Go_mode) {
    memset(placeable_GO, 0, sizeof(placeable_GO));
    currentflag = 1;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(Go[i][j] != GO_EMPTY){
                continue;
            }
            for(int d=0; d<8; d++){
                int nx = i + dx[d];
                int ny = j + dy[d];
                if(nx < 0 || nx >= 8 || ny < 0 || ny >= 8 || Go[nx][ny] != -Go_mode){
                    continue;
                }
                nx += dx[d];
                ny += dy[d];
                while(true){
                    if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8 || Go[nx][ny] == GO_EMPTY) {
                        break;
                    }
                    if (Go[nx][ny] == Go_mode) {
                        placeable_GO[i][j] = 1;
                        currentflag = 0;
                        break;
                    }
                    nx += dx[d];
                    ny += dy[d];
                }
            }
        }
    }
}
