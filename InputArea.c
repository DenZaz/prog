#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "scLib.h"
#include "myReadKey.h"
#include "inputArea.h"
#include "UserInterface.h"
#include "myTerm.h"
#include "myBigChars.h"

void displayBox(char *title, int type) {
    mt_setbgColor(RED);
    mt_setfgColor(BLACK);
    bc_box(10, 8, 3, 65);
    mt_gotoXY(11, 9);
    printf("                                                               ");
    mt_gotoXY(10, 10);
    printf(title);
    mt_gotoXY(11, 9);
    printf("INPUT VALUE: ");

    if (type == 1) {
        scanf("%d", &accumValue);
    }

    else if (type == 2) {
        scanf("%d", &opCounter);
        if(opCounter >= 0 && opCounter < MEM_COUNT) memoryPointer = opCounter;
        else
            sc_regSet(F_BOUNDS, 1);
    }

    else if (type == 3) {
        int com = 0, oper = 0, value;
        sc_memoryGet(memoryPointer, &value);
        sc_commandDecode(value, &com, &oper);
        mt_gotoXY(11, 9);
        printf("ENCODE(COMAND, OPERAND): ");
        scanf("%d %d", &com, &oper);
        sc_commandEncode(com, oper, &value);
        sc_memorySet(memoryPointer, value); 
    }

    mt_setfgColor(DEFAULT);
    mt_setbgColor(DEFAULT);
}

void clearInput()
{
    int term = open(TERM, O_RDWR);

    int i;
    mt_gotoXY (25, 1);
    for (i = 0; i < 80; ++i)
        write (term, " ", 1);
    mt_gotoXY (25, 1);

    close (term);
}
