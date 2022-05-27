# Project: C to Assembly Language
## Overview
Convert a number of C-subroutines into VisUAL compatible ARM Assembly Language.
### Objectives
- Understand Assembly language code
- Explore the difference between higher-level language and Assembly
## Description
### Introduction
The ARM architecture has quickly become the go-to platform for mobile and embedded systems.
ARM supports a software toolchain built around the Unified Assembler Language (UAL).
In this project you will use a subset of the ARM assembly code that is compatible with the VisUAL ARM emulator system.
### What to do
Your task is to write Assembly language programs which correspond to provided C programs.
- change.c - Computes the number of dollars, quarters, nickels, dimes, and pennies are required to provide correct change.
   * The amount of change is set in main.
   * Your assembly language version should start with the amount of change in R3, with dollars, quarters, dimes, nickels, and pennies stored in 4 byte values in: FP-4, FP-8, FP-12, FP-16, and FP-20.
- concat.c - Concatenates 2 strings.
   * Your assembly language version should start with two strings in R3 and R1 with their lengths in R2 and R0, respectively.
   * Allocate enough room from both strings and the subsequent null from the heap, then copy each string into the newly allocated memory and return the address in R0.
- hamming.c - Uses hamming code parity to correct errors in a 16-bit value.
   * The input value for correction should be assumed to be in R3, and the corrected 16-bit value should be output to R0.
## Running the code
Use the VisUAL ARM emulator to test the code.
You can download VisUAL at: https://salmanarif.bitbucket.io/visual/downloads.html
