#ifndef MYTERM_H
#define MYTERM_H

#include <sys/ioctl.h>

#define CLR_SCR "\E[H\E[J"
#define GOTO "\E[%d;%dH"
#define BG_COLOR "\E[4%dm"
#define FG_COLOR "\E[3%dm"
#define DEFAULT_COLOR "\e[0m"

#define TERM "/dev/tty"

enum Color {DEFAULT = 9, BLACK = 0, WHITE = 7, GREEN = 2, RED = 1};

int mt_clrscr();
int mt_gotoXY(int, int);
int mt_getScreenSize(int*, int*);
int mt_setfgColor(enum Color);
int mt_setbgColor(enum Color);

#endif