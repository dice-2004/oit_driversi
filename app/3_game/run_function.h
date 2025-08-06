#ifndef RUN_FUNCTION_H
#define RUN_FUNCTION_H
#include "../define.h"

void run_select_area(int select_area[]);
void run_update_area(int coordinate[],int player);
void run_update_display(void);
void run_SeRe_data(int coordinate[],int mode);
void update_log_area(void);
extern int Go[8][8];
extern int Go_S_x;
extern int Go_S_y;
extern int placeable_GO[8][8];
extern int dx[8];
extern int dy[8];
extern int connection_fd;
extern char log_area_data[LOG_AREA_HEIGHT - 2][LOG_AREA_WIDTH];
extern MoveData current_move;
#endif
