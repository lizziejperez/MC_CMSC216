# Makefile for uShell project

VERSION = 1
DRIVER = ./sdriver.pl
MSH = ./msh
MSHREF = ./mshref
MSHARGS = "-p"
CC = gcc
CFLAGS = -Wall -O2
FILES = $(MSH) ./myspin ./mysplit ./mystop ./myint

all: $(FILES)


##################
# Regression tests
##################

# Run tests using the student's shell program
test01:
	$(DRIVER) -t trace01.txt -s $(MSH) -a $(MSHARGS)
test02:
	$(DRIVER) -t trace02.txt -s $(MSH) -a $(MSHARGS)
test03:
	$(DRIVER) -t trace03.txt -s $(MSH) -a $(MSHARGS)
test04:
	$(DRIVER) -t trace04.txt -s $(MSH) -a $(MSHARGS)
test05:
	$(DRIVER) -t trace05.txt -s $(MSH) -a $(MSHARGS)
test06:
	$(DRIVER) -t trace06.txt -s $(MSH) -a $(MSHARGS)
test07:
	$(DRIVER) -t trace07.txt -s $(MSH) -a $(MSHARGS)
test08:
	$(DRIVER) -t trace08.txt -s $(MSH) -a $(MSHARGS)
test09:
	$(DRIVER) -t trace09.txt -s $(MSH) -a $(MSHARGS)
test10:
	$(DRIVER) -t trace10.txt -s $(MSH) -a $(MSHARGS)
test11:
	$(DRIVER) -t trace11.txt -s $(MSH) -a $(MSHARGS)
test12:
	$(DRIVER) -t trace12.txt -s $(MSH) -a $(MSHARGS)
test13:
	$(DRIVER) -t trace13.txt -s $(MSH) -a $(MSHARGS)
test14:
	$(DRIVER) -t trace14.txt -s $(MSH) -a $(MSHARGS)
test15:
	$(DRIVER) -t trace15.txt -s $(MSH) -a $(MSHARGS)
test16:
	$(DRIVER) -t trace16.txt -s $(MSH) -a $(MSHARGS)

# Run the tests using the reference shell program
rtest01:
	$(DRIVER) -t trace01.txt -s $(MSHREF) -a $(MSHARGS)
rtest02:
	$(DRIVER) -t trace02.txt -s $(MSHREF) -a $(MSHARGS)
rtest03:
	$(DRIVER) -t trace03.txt -s $(MSHREF) -a $(MSHARGS)
rtest04:
	$(DRIVER) -t trace04.txt -s $(MSHREF) -a $(MSHARGS)
rtest05:
	$(DRIVER) -t trace05.txt -s $(MSHREF) -a $(MSHARGS)
rtest06:
	$(DRIVER) -t trace06.txt -s $(MSHREF) -a $(MSHARGS)
rtest07:
	$(DRIVER) -t trace07.txt -s $(MSHREF) -a $(MSHARGS)
rtest08:
	$(DRIVER) -t trace08.txt -s $(MSHREF) -a $(MSHARGS)
rtest09:
	$(DRIVER) -t trace09.txt -s $(MSHREF) -a $(MSHARGS)
rtest10:
	$(DRIVER) -t trace10.txt -s $(MSHREF) -a $(MSHARGS)
rtest11:
	$(DRIVER) -t trace11.txt -s $(MSHREF) -a $(MSHARGS)
rtest12:
	$(DRIVER) -t trace12.txt -s $(MSHREF) -a $(MSHARGS)
rtest13:
	$(DRIVER) -t trace13.txt -s $(MSHREF) -a $(MSHARGS)
rtest14:
	$(DRIVER) -t trace14.txt -s $(MSHREF) -a $(MSHARGS)
rtest15:
	$(DRIVER) -t trace15.txt -s $(MSHREF) -a $(MSHARGS)
rtest16:
	$(DRIVER) -t trace16.txt -s $(MSHREF) -a $(MSHARGS)


# clean up
clean:
	rm -f $(FILES) *.o *~


