CC = gcc
CFLAGS = -Wall -O2

SRC = $(wildcard src/*.c)
OUT = bin/app

LINUXLIBS = -lglfw -lGLEW -lGL
MACLIBS   = -lglfw -lGLEW -framework OpenGL

linux:
	$(CC) $(CFLAGS) $(SRC) $(LINUXLIBS) -o $(OUT)

mac:
	$(CC) $(CFLAGS) $(SRC) $(MACLIBS) -o $(OUT)

clean:
	rm -rf $(OUT)

