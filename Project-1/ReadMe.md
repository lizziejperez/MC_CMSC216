# Project: Simulated CPU
## Overview
Implement an assembly language interpreter for a simple simulated CPU.
## Objectives
- Create a "simple" program in C
- Begin to build familiarity with Assembly opcodes
- Consider the distinction between registers and memory
- Process input from Standard Input (STDIN)
## Description
### Introduction
Programs run on computers by having the hardware (or system software) execute basic operations called instructions.
Many languages (such as Java) represent the program to be executed as byte codes which are very similar to machine
instructions.
In this assignment, you will build an interpreter for a simple machine language.

At their lowest level, computers operate by manipulating information stored in registers and memory.
Registers and memory are like variables in C or Java; in fact inside the computer that is how variables get stored.
In addition to data, memory also stores the instructions to execute.
The basic operation of a computer is to read an instruction from memory, execute it and then move to the instruction stored in the next memory location.
Typical instructions will read one or more values (called operands) from memory and produce a result into another register or memory location.
For example, an instruction might add the values stored in two registers, R3 and R4 and then store the result in the register R5.
Other instructions might just move data from one place to another (between registers or between a register and a memory location).
A final type of instruction, called a branch instruction, is used to change what instruction is executed next (to allow executing if and looping statements).
### The Simulated CPU
The simulated computer has a memory that contains 2^6 (64) words of memory, each 64-bits long.

In addition to memory, the computer has 16 registers that can be used to hold values, and a program counter.
One of the registers is special.
R0 is hardwired to 0 and writing to it is legal, but does not change its value, but reading from it always returns 0.
PC is the "Program Counter" and always contains the address of the next instruction to execute.
PC can be read like a normal register, but can only be modified using special instructions (B and BEQ), any other attempt to modify it is an Invalid Instruction (including using it as the register value of Branch) R1-R15 are General Purpose Registers, and can be read or written.

For this project, you should assume that the program text (your code) is in a separate memory from the program data (in other words, your computer is a Harvard Architecture). Assume that each instruction takes up only one memory address in the program memory.
You can implement this memory any way you see fit, but you need to be able to execute instructions based on the PC and order the instructions were entered.
For example, the following program is a simple loop that increments R1 infinitely:
```MOV R1 0x0
MOV R2 0x1
ADD R1 R2
B 0x2
STOP
```
### What to do
Create a C program called "asm" that acts as an interpreter for a simple assembly language.
Your program should accept upper or lowercase input from STDIN (the default input location in C); the input stream will have the following format:
```<string opcode> <int operand1> <int operand2>
<string opcode> <int operand1> <int operand2> <int operand3>
...
<string opcode> <int operand1> <int operand2>
<EOF>
```
UPDATE: You can assume that the maximum program lenght is 1024 intructions.

EOF is represented on Unix systems as <cntl-d>.
All integer values in this project are to be input and output in hexadecimal format (e.g. 0x14 is the hexadecimal representation of the decimal number 20).
The only exception is registers names where are specified as the letter 'R' followed by a decimal integer (e.g. R15 is the 16th register since we start counting at 0).
Before exiting your program should dump all registers (including PC) and it's memory to STDOUT (the default output location in C) in the following format:
```
<register R0> <value>
<register R1> <value>
...
<register R14> <value>
<register R15> <value>

<register PC> <value>

<byte aligned address>: [mem 0x0] [mem 0x1] ... [mem 0x7]
...
<byte aligned address>: [mem 0x38] [mem 0x39] ... [mem 0x3F]
```
Include with your project a test input file "fib.s" that fills memory with the first 64 Fibonacci numbers.
### Description of Opcodes
```
MOV <register> <constant>
```
Copies the supplied constant into the register location.
## Compiling your program
Please use gcc to compile and submit your program. Specifically use the following command to compile your program:
```
gcc -Wall -pedantic-errors -Werror <filename.c> -o asm
```
