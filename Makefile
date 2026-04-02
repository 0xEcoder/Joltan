# -------------------------
# Compiler and flags
# -------------------------
CC = g++
CFLAGS = -Wall -O2

# -------------------------
# Sources and output
# -------------------------
SRC = $(wildcard src/*.cpp)
FOLDER_NAME = Joltan
BIN = bin
OUT = $(BIN)/$(FOLDER_NAME)/$(FOLDER_NAME)

# Shaders folder
SHADERS_SRC = src/shaders
SHADERS_DST = $(BIN)/$(FOLDER_NAME)/shaders

# -------------------------
# Platform-specific libraries
# -------------------------
ifeq ($(OS),Windows_NT)
    LIBS = -lopengl32 -lglew32 -lgdi32 -luser32 -lkernel32 -lm
else ifeq ($(shell uname),Darwin)
    LIBS = -framework OpenGL -lglfw -lGLEW -lm
else
    LIBS = -lGL -lglfw -lGLEW -lm
endif

# -------------------------
# Default target
# -------------------------
all: $(OUT)

# -------------------------
# Build binary
# -------------------------
$(OUT): $(SRC)
	@echo "Building $(OUT)..."
	mkdir -p $(BIN)/$(FOLDER_NAME)
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(OUT)
	@echo "Copying shaders into $(FOLDER_NAME)..."
	mkdir -p $(SHADERS_DST)
	cp -rf $(SHADERS_SRC)/* $(SHADERS_DST)/

# -------------------------
# Clean
# -------------------------
clean:
	@echo "Cleaning $(BIN)..."
	rm -rf $(BIN)

# -------------------------
# Run
# -------------------------
run: $(OUT)
	@echo "Running $(OUT)..."
	./$(OUT)