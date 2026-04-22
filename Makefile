# -------------------------
# Compiler and flags
# -------------------------
CC = g++
CFLAGS = -Wall -O2

# -------------------------
# Sources and output
# -------------------------
SRC = $(wildcard src/*.cpp)
BIN = bin
OUT = $(BIN)/Joltan

# -------------------------
# Shaders
# -------------------------
SHADERS_SRC = src/shaders
SHADERS_DST = $(BIN)/Joltan/shaders

# -------------------------
# Libraries
# -------------------------
ifeq ($(OS),Windows_NT)
    LIBS = -lopengl32 -lglew32 -lgdi32
    MKDIR = mkdir
    COPY = cp -r
    RM = rm -rf
else
    UNAME_S := $(shell uname -s)

    ifeq ($(UNAME_S),Darwin)
        LIBS = -framework OpenGL -lglfw -lGLEW
    else
        LIBS = -lGL -lglfw -lGLEW
    endif

    MKDIR = mkdir -p
    COPY = cp -r
    RM = rm -rf
endif

# -------------------------
# Build
# -------------------------
all: $(OUT)

$(OUT): $(SRC)
	@echo "Building..."
	$(MKDIR) -p $(BIN)
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(OUT)

	@echo "Copying shaders..."
	$(MKDIR) -p $(SHADERS_DST)
	$(COPY) $(SHADERS_SRC)/* $(SHADERS_DST)/

# -------------------------
# Run
# -------------------------
run: $(OUT)
	./$(OUT)

# -------------------------
# Clean
# -------------------------
clean:
	$(RM) $(BIN)