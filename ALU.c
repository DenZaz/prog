#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "scLib.h"
#include "myReadKey.h"
#include "inputArea.h"
#include "UserInterface.h"
#include "myTerm.h"
#include "ALU.h"


int alu(int command, int operand)
{	
	int flag_MEM, flag_ZERO, flag_WRONG;
	int value = 0;
	int invers=0;


	switch (command) {
				
		case 30: //ADD
                 accumValue += memArr[operand];
		break;

		case 31: //SUB
			accumValue -= memArr[operand];
			break;
		case 32: //DIVIDE
			if (operand != 0) accumValue /= memArr[operand];
			else sc_regSet(F_ZERO, 1);
			break;
		case 33: //MUL
			accumValue *= memArr[operand];
			break;
		case 51: //NOT
			invers=~accumValue & 0b1111111111111111;
			sc_memorySet(operand, invers);
			break;

		
		default:
            sc_regSet(F_WRONG_COM, 1);   
            alarm(0);         
			break;			
	}
	
	sc_regGet(F_BOUNDS, &flag_MEM);
	sc_regGet(F_ZERO, &flag_ZERO);
	sc_regGet(F_WRONG_COM, &flag_WRONG);
	
	if (flag_MEM || flag_ZERO || flag_WRONG) {
		sc_regSet(F_IGNORE_FLAG, 1);
		return -1;
	}
	else
		return 0;
}
