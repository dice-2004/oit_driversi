#ifndef SCREEN_HELP_H
#define SCREEN_HELP_H
#include "../define.h"
int screen_help(void);
extern int center_y;
extern int center_x;
extern char help_text[FILE_LINE][FILE_CHARS];
extern FILE *fp;
#endif
