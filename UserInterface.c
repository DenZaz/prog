#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "UserInterface.h"
#include "scLib.h"
#include "myTerm.h"
#include "myBigChars.h"

int command, operand, value;

void displayMemory() {
	int k = 2, i;
	bc_box(1, 1, 12, 62);
	mt_gotoXY(1, 28);
	printf("Memory");

	mt_gotoXY(2, 2);

	for (i = 1; i <= 100; i++) {
		sc_memoryGet(i - 1, &value);

		if (memoryPointer == i - 1) mt_setbgColor(RED);
		printf("+%04X ", value);
		mt_setbgColor(DEFAULT);

		if (i % 10 == 0 && i != 0) {k++; mt_gotoXY(k, 2);}
	}

	mt_gotoXY(25, 1);
}

void displayAccumulator() {
	bc_box(1, 63, 3, 18);
	mt_gotoXY(1, 65);
	printf("accumulator");
	mt_gotoXY(2, 69);

	if (accumValue >= 0) {printf("+%04X", accumValue); mt_gotoXY(2, 69);}
	else {printf("-%04X", (-1) * accumValue); mt_gotoXY(2, 69);}

	mt_gotoXY(25, 1);
}

void displayCounter() {
	bc_box(4, 63, 3, 18);
	mt_gotoXY(4, 65);
	printf("instructCounter");
	opCounter = memoryPointer;
	mt_gotoXY(5, 69);
	printf("+%04X", opCounter);

	mt_gotoXY(25, 1);
}

void displayOperation() {
	int com = 0, oper = 0, val = 0;
	bc_box(7, 63, 3, 18);
	mt_gotoXY(7, 65);
	printf("Operation");
	mt_gotoXY(8, 67);
	sc_memoryGet(memoryPointer, &val);
	if (val != 0) sc_commandDecode(val, &com, &oper);
	printf("+%02d : %02X", com, oper);

	mt_gotoXY(25, 1);
}

void displayFlags() {
	bc_box(10, 63, 3, 18);
	mt_gotoXY(10, 65);
	printf("Flags");

	int flagVal;
    mt_gotoXY(11, 65);
	sc_regGet(F_WRONG_COM, &flagVal); if (flagVal == 1) printf("E"); else printf("");
	mt_gotoXY(11, 68);
	sc_regGet(F_ISRUN, &flagVal); if (flagVal == 1) printf("T"); else printf("");
	mt_gotoXY(11, 69);
	sc_regGet(F_BOUNDS, &flagVal); if (flagVal == 1) printf("M"); else printf("");
	mt_gotoXY(11, 70);
	sc_regGet(F_ZERO, &flagVal); if (flagVal == 1) printf("O"); else printf("");
    
	mt_gotoXY(25, 1);
}

void displayMenu() {
	bc_box(13, 47, 10, 34);
	mt_gotoXY(13, 49);
	printf("Keys:");
	mt_gotoXY(15, 49);
	printf("l - load");
	mt_gotoXY(16, 49);
	printf("s - save");
	mt_gotoXY(17, 49);
	printf("r - run");
	mt_gotoXY(18, 49);
	printf("t - step");
	mt_gotoXY(19, 49);
	printf("i - reset");
	mt_gotoXY(20, 49);
	printf("F5 - accumulator");
	mt_gotoXY(21, 49);
	printf("F6 - instructionCounter");

	mt_gotoXY(25, 1);
}

void displayBigCharArea() {
	mt_gotoXY(13, 1);
	char buffer[20];
	int y = 2;
	bc_box(13, 1, 10, 46);
	mt_gotoXY(13, 5);

	BIG[0] = 0;
	BIG[1] = 0;

	sc_memoryGet(memoryPointer, &value);

	sprintf(buffer, "+%04X", value);

	int i;
	for (i = 0; i < 5; ++i, y += 9) {
		bc_setBig(BIG, buffer[i]);
		bc_printBigChar(BIG, 14, y, DEFAULT, DEFAULT);
	}
	mt_gotoXY(25, 1);
}

void showAll() {
	mt_clrscr();
	displayMemory();
	displayAccumulator();
	displayCounter();
	displayOperation();
	displayFlags();
	displayMenu();
	displayBigCharArea();
	mt_gotoXY(25, 1);
}
