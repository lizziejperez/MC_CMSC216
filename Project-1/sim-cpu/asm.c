#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_PRG_LEN 1024
#define LINE_LEN 26

char instr[MAX_PRG_LEN][LINE_LEN]; /* instructions */
long long int rgtr[16]; /* registers */
long long int mem[64]; /* memory */
int pc; /* program counter */
int cmp_flag; /* compare flag */

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

	cmp_flag = FALSE;
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

/*
** Gets the input and stores it in the instructions array (instr)
*/
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

/*
** Prints out the registers, pc, and memory stored
*/
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

/*
** Returns the register number (input) as an int
*/
int getReg(char input[3]) {
	char num[2];
	num[0] = input[1];
	num[1] = input[2];
	return (int) strtol(num, NULL, 10);
}

/*
** Returns the constant number (input) as an int
*/
long long int getConst(char input[16]) {
	return (long long int) strtol(input, NULL, 0);
}

/*
** Copies the supplied constant (c) into the register location (r)
*/
void mov(int r, long long int c) {
	if(r > 0) {
		rgtr[r] = c;
	}
	++pc;
}

/*
** Copies the value stored in the memory location (m) into register location (r)
*/
void ldr(int r, long long int m) {
	rgtr[r] = mem[m];
	++pc;
}

/*
** Copies the value stored in the memory location indecated by register (r2) into register location (r1)
*/
void ldi(int r1, int r2) {
	rgtr[r1] = mem[rgtr[r2]];
	++pc;
}

/*
** Copies the value stored in register (r) into memory location (m)
*/
void str(int r, long long int m) {
	mem[m] = rgtr[r];
	++pc;
}

/*
** Copies the value stored in register (r1) into memory location indicated by register (r2)
*/
void sti(int r1, int r2) {
	mem[rgtr[r2]] = rgtr[r1];
	++pc;
}

/*
** Adds the value stored in register (r2) to the value stored in register (r3) and stores the result into register (r1)
*/
void add(int r1, int r2, int r3) {
	rgtr[r1] = rgtr[r2] + rgtr[r3];
	++pc;
}

/*
** Multiplies the value stored in register (r2) to the value stored in register (r3) and stores the result into register (r1)
*/
void mul(int r1, int r2, int r3) {
	rgtr[r1] = rgtr[r2] * rgtr[r3];
	++pc;
}

/*
** Compares the value of register (r1) and register (r2), and sets the compare flag (cmp_flag) if they are equal,
** resets the compare flag (cmp_flag) if they are different
*/
void cmp(int r1, int r2) {
	if(rgtr[r1] == rgtr[r2]) {
		cmp_flag = TRUE;
	} else {
		cmp_flag = FALSE;
	}
	++pc;
}

/*
** Sets program counter (pc) to constant (c)
*/
void b(long long int c) {
	pc = c;
}

/*
** If the value of compare flag (cmp_flag) is NOT zero (false), sets the value of program counter (pc) to constant (c)
*/
void beq(long long int c) {
	if(cmp_flag != FALSE) {
		pc = c;
	} else {
		++pc;
	}
}