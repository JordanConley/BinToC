all: bin2c

bin2c: main.c
	cc -ansi -pedantic -Wall -Wextra main.c -o bin2c

