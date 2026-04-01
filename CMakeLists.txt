cmake_minimum_required(VERSION 3.20)
project(Joltan C)

set(CMAKE_C_STANDARD 11)

# Source files
file(GLOB SRC "src/*.c")

# Output binary
set(OUT app)

# Platform-specific libraries
if(WIN32)
    # Windows: Bundled MinGW
    set(LIBS glfw3 glew32 opengl32)
elseif(APPLE)
    # macOS frameworks
    set(LIBS glfw GLEW "-framework OpenGL")
else()
    # Linux
    set(LIBS glfw GLEW GL)
endif()

# Add executable
add_executable(${OUT} ${SRC})

# Link libraries
target_link_libraries(${OUT} PRIVATE ${LIBS})