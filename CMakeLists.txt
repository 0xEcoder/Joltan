cmake_minimum_required(VERSION 3.20)
project(Joltan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB SRC "src/*.cpp")

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
    set(LIBS glfw GLEW GL m)
endif()

# Add executable
add_executable(${OUT} ${SRC})

# Link libraries
target_link_libraries(${OUT} PRIVATE ${LIBS})