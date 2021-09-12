#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_PRG_LEN 1024
#define LINE_LEN 25

char instr[MAX_PRG_LEN][LINE_LEN];
long long int rgtr[16];
long long int mem[64];
int pc;
int COMPARE_FLAG;

void getInput();
void printOutput();
int getReg(char []);
long long int getConst(char []);
void mov(int, long long int);
void ldr(int, long long int);
void ldi(int, int);
void str(int, long long int);
void sti(int, int);
void add(int, int, int);
void mul(int, int, int);
void cmp(int, int);
void b(long long int);
void beq(long long int);

int main()
{
	getInput();

	COMPARE_FLAG = FALSE;
	pc = 0;
	int processing = TRUE;
	char line[LINE_LEN];
	char opcode[4];
	char *ptr;
	while (processing == TRUE) {
		rgtr[0] = 0;
		strcpy(line, instr[pc]);
		ptr = strtok(line, " ");
		strcpy(opcode, ptr);

		if(strncmp("stop", opcode, 4) == 0){
			processing = FALSE;
		}

		if(strncmp("b", opcode, 1)  == 0) {
			ptr = strtok(NULL, " ");
			long long int op1 = getConst(ptr);
			if(strncmp("beq", opcode, 3) == 0) {
				beq(op1);
			} else {
				b(op1);
			}
		}

		if(strncmp("mov", opcode, 3) == 0) {
			ptr = strtok(NULL, " ");
			int op1 = getReg(ptr);
			ptr = strtok(NULL, " ");
			long long int op2 = getConst(ptr);
			mov(op1, op2);
		}

		if(strncmp("ldr", opcode, 3) == 0) {
			ptr = strtok(NULL, " ");
			int op1 = getReg(ptr);
			ptr = strtok(NULL, " ");
			long long int op2 = getConst(ptr);
			ldr(op1, op2);
		}

		if(strncmp("ldi", opcode, 3) == 0) {
			ptr = strtok(NULL, " ");
			int op1 = getReg(ptr);
			ptr = strtok(NULL, " ");
			long long int op2 = getReg(ptr);
			ldi(op1, op2);
		}

		if(strncmp("str", opcode, 3) == 0) {
			ptr = strtok(NULL, " ");
			int op1 = getReg(ptr);
			ptr = strtok(NULL, " ");
			long long int op2 = getConst(ptr);
			str(op1, op2);
		}

		if(strncmp("sti", opcode, 3) == 0) {
			ptr = strtok(NULL, " ");
			int op1 = getReg(ptr);
			ptr = strtok(NULL, " ");
			int op2 = getReg(ptr);
			sti(op1, op2);
		}

		if(strncmp("add", opcode, 3) == 0) {
			ptr = strtok(NULL, " ");
			int op1 = getReg(ptr);
			ptr = strtok(NULL, " ");
			int op2 = getReg(ptr);
			ptr = strtok(NULL, " ");
			int op3 = getReg(ptr);
			add(op1, op2, op3);
		}

		if(strncmp("mul", opcode, 3) == 0) {
			ptr = strtok(NULL, " ");
			int op1 = getReg(ptr);
			ptr = strtok(NULL, " ");
			int op2 = getReg(ptr);
			ptr = strtok(NULL, " ");
			int op3 = getReg(ptr);
			mul(op1, op2, op3);
		}

		if(strncmp("cmp", opcode, 3) == 0) {
			ptr = strtok(NULL, " ");
			int op1 = getReg(ptr);
			ptr = strtok(NULL, " ");
			int op2 = getReg(ptr);
			cmp(op1, op2);
		}
	}

	printOutput();

	return 0;
}

void getInput() {
	int i = 0, getInput = TRUE;
	while(getInput == TRUE) {
		fgets(instr[i], LINE_LEN, stdin);
		if(strncmp(instr[i], "^D", 2) == 0) {
			getInput = FALSE;
		} else {
			for(int j = 0; instr[i][j]; j++) {
				instr[i][j] = tolower(instr[i][j]);
			}
			i++;
		}
	}
}

void printOutput() {
	for(int x = 0; x < 16; x++) {
		printf("register 0x%01X: 0x%012llX\n", x, rgtr[x]);
	}
	printf("register  PC: 0x%012X\n\n", pc);
	for(int x = 0; x < 64; x++) {
		if(x == 0) {
			printf("0x%02X: ", x);
		} else if((x%8) == 0) {
			printf("\n0x%02X: ", x);
		}
		printf("0x%012llX ", mem[x]);
	}
	printf("\n");
}

int getReg(char input[3]) {
	char num[2];
	num[0] = input[1];
	num[1] = input[2];
	return (int) strtol(num, NULL, 10);
}

long long int getConst(char input[16]) {
	return (long long int) strtol(input, NULL, 0);
}

void mov(int r, long long int c) {
	if(r > 0) {
		rgtr[r] = c;
	}
	++pc;
}

void ldr(int r, long long int m) {
	rgtr[r] = mem[m];
	++pc;
}

void ldi(int r1, int r2) {
	rgtr[r1] = mem[rgtr[r2]];
	++pc;
}

void str(int r, long long int m) {
	mem[m] = rgtr[r];
	++pc;
}

void sti(int r1, int r2) {
	mem[rgtr[r2]] = rgtr[r1];
	++pc;
}

void add(int r1, int r2, int r3) {
	rgtr[r1] = rgtr[r2] + rgtr[r3];
	++pc;
}

void mul(int r1, int r2, int r3) {
	rgtr[r1] = rgtr[r2] * rgtr[r3];
	++pc;
}

void cmp(int r1, int r2) {
	if(rgtr[r1] == rgtr[r2]) {
		COMPARE_FLAG = TRUE;
	} else {
		COMPARE_FLAG = FALSE;
	}
	++pc;
}

void b(long long int c) {
	pc = c;
}

void beq(long long int c) {
	if(COMPARE_FLAG != FALSE) {
		pc = c;
	} else {
		++pc;
	}
}