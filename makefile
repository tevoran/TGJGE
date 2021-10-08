CC=gcc
CFLAGS=-o test -g
LIBS=-lSDL2 -lGL -lGLEW -lm
HEADERS=-I src/ -I vendor/stb/
SRC=*.c src/*.c

build: $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBS) $(HEADERS)

run:
	./test