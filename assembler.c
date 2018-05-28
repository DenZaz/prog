#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <signal.h>
#include <time.h>
#include <sys/time.h>

#include "myBigChars.h"
#include "myTerm.h"
#include "myReadKey.h"
#include "UserInterface.h"
#include "scLib.h"
#include "inputArea.h"
#include "CU.h"
#include "ALU.h"

void assembler(){

	FILE *file;
	
	struct assembler {
		unsigned adress; 
    	        char comand[20]; 
		unsigned operand;
	};

	struct assembler trans[15];
	char i=0;
	file = fopen("assembler.sa", "r");

int value;

	while (fscanf (file, "%u%s%u", &(trans[i].adress), trans[i].comand, &(trans[i].operand)) != EOF) {

	memoryPointer = trans[i].adress;
        
	if(strcmp(trans[i].comand, "READ")==0){
		command=10;
				}
	else if(strcmp(trans[i].comand, "WRITE")==0){
		command=11;
				}
	else if(strcmp(trans[i].comand, "LOAD")==0){
		command=20;
				}
	else if(strcmp(trans[i].comand, "STORE")==0){
		command=21;
				}
	else if(strcmp(trans[i].comand, "ADD")==0){
		command=30;
				}
	else if(strcmp(trans[i].comand, "SUB")==0){
		command=31;
				}
	else if(strcmp(trans[i].comand, "DIVIDE")==0){
		command=32;
				}
	else if(strcmp(trans[i].comand, "MUL")==0){
		command=33;
				}
	else if(strcmp(trans[i].comand, "JUMP")==0){
		command=40;
				}
	else if(strcmp(trans[i].comand, "JNEG")==0){
		command=41;
				}
	else if(strcmp(trans[i].comand, "JZ")==0){
		command=42;
				}
	else if(strcmp(trans[i].comand, "HALT")==0){
		command=43;
				}
	else if(strcmp(trans[i].comand, "NOT")==0){
		command=51;
				}

	operand=trans[i].operand;

		

        sc_commandEncode(command, operand, &value);
        sc_memorySet(memoryPointer, value); 
      

	i++;
	}	
	return 0;
}
