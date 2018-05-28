#include "myTerm.h"

int mt_clrscr() {
	printf(CLR_SCR);

	return 0;
}

int mt_gotoXY(int newX, int newY) {
	printf(GOTO, newX, newY);

	return 0;
}

int mt_getScreenSize(int *x, int *y) {
	struct winsize ws;

	if (!ioctl(1, TIOCGWINSZ, &ws)) {
		*x = ws.ws_row;
		*y = ws.ws_col;

		return 0;
	}

	return -1;
}

int mt_setbgColor(enum Color color) {
	printf(BG_COLOR, color);

	return 0;
}

int mt_setfgColor(enum Color color) {
	printf(FG_COLOR, color);

	return 0;
}