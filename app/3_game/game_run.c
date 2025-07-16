//  module
#include <string.h>

#include "game_run.h"
#include "run_function.h"
#include "game_serch_placeable.h"
#include "game_algo.h"
#include "../define.h"
#include "../boolean.h"
// mode > HOST 先攻、黒 > GUEST  後攻、白 > CPUの場合自分が黒
int game_run(void){
    if(mode == HOST || mode == CPU){
        // HOST or CPU
        game_serch_placeable(GO_BLACK);
        // x,y,pass_flag
        int select_area_flag[3] = {-1, -1, 0};
        select_area_flag[2] = currentflag;

        if(currentflag == 0){
            run_select_area(select_area_flag);
            if(select_area_flag[0] == -1 && select_area_flag[1] == -1){
                return -1; //異常終了
            }else{
                run_update_area(select_area_flag, GO_BLACK);
                run_update_display();
            }
        }
        // else パス
        if(mode == HOST){
            // HOST
            run_SeRe_data(select_area_flag, SEND); // #1と通信
        }

        if(select_area_flag[2] == 1 && preflag == 1){
            return 1; // どちらもパス
        }
        preflag = currentflag;
    }else{
        // GUEST
        preflag = currentflag;
        int select_area_flag[3] = {-1, -1, 0};
        run_SeRe_data(select_area_flag, RECEIVE); // #1と通信
        currentflag = select_area_flag[2];
        if(select_area_flag[0] == -1 && select_area_flag[1] == -1){
            return -1;
        }else if(currentflag == 0){
            run_update_area(select_area_flag, GO_BLACK);
            run_update_display();
            currentflag = select_area_flag[2];

        }else if(currentflag == 1){
            if (preflag == 1){
                // どちらもパス
                return 1;
            }else{
                // 相手がpass
                preflag = currentflag;
            }
        }else if(select_area_flag[2] == -1){
            // disconnect
            return -1;
        }
    }
    // メッセージ表示

    if(mode == GUEST){
        game_serch_placeable(GO_WHITE);
        int select_area_flag[3] = {-1, -1, 0};
        select_area_flag[2] = currentflag;
        if(currentflag == 0){
            run_select_area(select_area_flag);
            if(select_area_flag[0] == -1 && select_area_flag[1] == -1){
                return -1; //異常終了
            }else{
                run_update_area(select_area_flag, GO_WHITE);
                run_update_display();
            }
        }
        if(mode == GUEST){
            // GUEST
            run_SeRe_data(select_area_flag, SEND); // #2と通信
        }

        if(select_area_flag[2] == 1 && preflag == 1){
            return 1; // どちらもパス
        }
        preflag = currentflag;
    }else if(mode == HOST){
        // HOST
        preflag = currentflag;
        int select_area_flag[3] = {-1, -1, 0};
        run_SeRe_data(select_area_flag, RECEIVE); // #2と通信
        currentflag = select_area_flag[2];
        if(select_area_flag[0] == -1 && select_area_flag[1] == -1){
            return -1;
        }else if (condition(currentflag == 0)){
            run_update_area(select_area_flag, GO_WHITE);
            run_update_display();
            currentflag = select_area_flag[2];
        }else if (currentflag == 1){
            if (preflag == 1){
                // どちらもパス
                return 1;
            }else{
                // 相手がpass
                preflag = currentflag;
            }
        }else if(select_area_flag[2] == -1){
            // disconnect
            return -1;
        }
    }else if(mdoe == CPU){
        // CPU
        game_search_placeable(GO_WHITE);
        int select_area_flag[3] = {-1, -1, 0};
        select_area_flag[2] = currentflag;
        if(currentflag == 0){
            game_algo(select_area_flag);
            if(select_area_flag[0] == -1 && select_area_flag[1] == -1){
                return -1; //異常終了
            }else{
                run_update_area(select_area_flag, GO_WHITE);
                run_update_display();
            }
        }

        if(select_area_flag[2] == 1 && preflag == 1){
            return 1; // どちらもパス
        }
    }
    return 0;
}
