// module
#include <ncurses.h>
#include <locale.h>
#include <unistd.h>

#include "boolean.h"
#include "1_size/set_size.h"
#include "2_menue/handle_menue.h"
#include "3_game/start_game.h"
#include "define.h"

// 1-> コンピュータ 5 -> ホスト 6 -> ゲスト mode
int main(int argc, char *argv[]) {
    if (argc>1){
        fprintf(stderr, "オプションはありません。\n");
        return 1;
    }

    setlocale(LC_ALL, "");
    initscr();
    while(true){
        set_size();
        handle_menue();
        if( mode == EXIT){
            break;
        }
        start_game();
    }
    endwin();
    return 0;
}
