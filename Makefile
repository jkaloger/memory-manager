# Makefile For COMP30023 Project 1
# Jack Kaloger 2017

## CC  = Compiler.
## CFLAGS = Compiler flags.
CC	= gcc
CFLAGS =	-Wall -Wextra -std=gnu99 -g


## OBJ = Object files.
## SRC = Source files.
## EXE = Executable name.

SRC =		main.c swap.c queue.c list.c process.h
OBJ =		main.o swap.o queue.o list.o process.o
EXE = 		swap

## Top level target is executable.
$(EXE):	$(OBJ)
		$(CC) $(CFLAGS) -o $(EXE) $(OBJ) -lm


## Clean: Remove object files and core dump files.
clean:
		/bin/rm $(OBJ) 

## Clobber: Performs Clean and removes executable file.

clobber: clean
		/bin/rm $(EXE) 

## Dependencies
main.o:	swap.h process.h list.h queue.h
swap.o:	swap.h
list.h: process.h
list.o: list.h
queue.h: list.h
queue.o: queue.h
