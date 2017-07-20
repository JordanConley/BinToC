CFLAGS += -Wall -Wextra -pedantic -ansi 

all: bin2c

bin2c: bin2c.o

bin2c.o: bin2c.c

