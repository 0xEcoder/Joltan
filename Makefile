CC = gcc
CFLAGS = -Wall -O2
SRC = $(wildcard src/*.c)


OUT = bin/app

# Platform-specific libraries
ifeq ($(OS),Windows_NT)
    LIBS = -lopengl32 -lglew32 -lgdi32 -luser32 -lkernel32
else ifeq ($(shell uname),Darwin)
    LIBS = -framework OpenGL -lglfw -lGLEW
else
    LIBS = -lGL -lglfw -lGLEW -lGL
endif

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(OUT)

clean:
	rm -rf $(OUT)

run: $(OUT)
	./$(OUT)