#include <stdio.h>
#include <stdlib.h>
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
#include "CU.h"
#include "myTerm.h"

struct termios oldState, termState;

int CU()
{
	int term = open(TERM, O_RDWR);
	int flag_MEM, flag_ZERO, flag_WRONG, value = 0, command = 0, operand = 0, res;

	if ((sc_memoryGet(memoryPointer, &value) == 0) && (sc_commandDecode(value, &command, &operand) == 0)) {
		switch(command) {
			case 10: //READ
				rk_myTermSave(&oldState);
				defaultTermSettings(&termState);
				tcsetattr(1, TCSANOW, &termState);
				alarm(0);
				int input;
				printf("INPUT VALUE: ");
				scanf("%d", &input);
				sc_memorySet(operand, input);
				rk_myTermRestore(&oldState);
				timerStart();
				++memoryPointer;
				clearInput();
			break;

			case 11:  //WRITE
			
	                       rk_myTermSave(&oldState);
				defaultTermSettings(&termState);
				tcsetattr(1, TCSANOW, &termState);
				tcsetattr(1, TCSANOW, &termState);
				alarm(0);
				value=memArr[operand];
				printf("OUTPUT VALUE: %d", value);
				getchar();

				rk_myTermRestore(&oldState);
				timerStart();
				++memoryPointer;
				clearInput();

				break;

			case 20:  //LOAD
				accumValue= memArr[operand];
				++memoryPointer;
				break;

			case 21:  //STORE
				memArr[operand]=accumValue;
				accumValue*=0;
				++memoryPointer;
				break;

			case 40:  //JUMP
				memoryPointer = operand;
			break;

			case 41:   //JNEG
				if(accumValue<0){memoryPointer = operand;}
				else{sc_regSet(F_WRONG_COM, 1);}
				break;

			case 42:   //JZ
				if(accumValue==0x0000){memoryPointer = operand;}
				else{sc_regSet(F_WRONG_COM, 1);}
				break;
			
			case 43:  //HALT
				sc_regSet(F_ISRUN, 0);  
				break; 

			default:
			alu(command, operand);
			++memoryPointer;
			break;	
		}
	}				
	
		return 0;
}
