CC = gcc
CFLAGS = -Wall -O2
SRC = $(wildcard src/*.c) \
      src/external/glew/src/glew.c \
      $(wildcard src/external/glfw/src/*.c)

OUT = bin/app

# Platform-specific libraries
ifeq ($(OS),Windows_NT)
    LIBS = -lopengl32
else ifeq ($(shell uname),Darwin)
    LIBS = -framework OpenGL
else
    LIBS = -lGL
endif

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -I src/external/glew/include -I src/external/glfw/include -o $(OUT)

clean:
	rm -rf $(OUT)

run: $(OUT)
	./$(OUT)