#ifndef RUN_FUNCTION_H
#define RUN_FUNCTION_H

int* run_select_area(int select_area[]);
void run_update_area(int coordinate[],int player);
void run_update_display(void);
void run_SeRe_data(int coordinate[],int mode);
extern int Go[8][8];
extern int Go_S_x;
extern int Go_S_y;
extern int placeable_GO[8][8];
extern int dx[8];
extern int dy[8];

#endif
