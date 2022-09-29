CC = gcc
CFLAGS = -O2

afdtool: main.o
	$(CC) $(CFLAGS) -o afdtool main.o

main.o: main.c operacoes.h
	$(CC) $(CFLAGS) -c main.c

.PHONY: clean

clean:
	rm -f main.o