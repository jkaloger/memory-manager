# Jack Kaloger 758278
# Makefile For COMP30023 Project 1 2017

## CC  = Compiler.
## CFLAGS = Compiler flags.
CC	= gcc
CFLAGS =	-Wall -Wextra -std=gnu99 -g


## OBJ = Object files.
## SRC = Source files.
## EXE = Executable name.

SRC =		main.c swap.c queue.c list.c process.c memory.c schedule.c 
OBJ =		main.o swap.o queue.o list.o process.o memory.o schedule.o 
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
main.o:	swap.h process.h list.h queue.h memory.h schedule.h
swap.h: memory.h list.h queue.h
swap.o:	swap.h
list.h: process.h
list.o: list.h
queue.h: list.h
queue.o: queue.h
memory.h: list.h queue.h
memory.o: memory.h
schedule.h: queue.h
schedule.o: schedule.h
