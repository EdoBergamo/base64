CFLAGS=-Wall -ggdb -std=c11 -pedantic
LIBS=-lreadline

main: ./src/main.c
	$(CC) $(CFLAGS) ./src/main.c -o ./bin/base64 $(LIBS)
