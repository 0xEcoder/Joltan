cmake_minimum_required(VERSION 3.20)
project(Joltan C)

set(CMAKE_C_STANDARD 11)

# Project sources + external libraries
file(GLOB SRC "src/*.c")
file(GLOB GLEW_SRC "src/external/glew/src/glew.c")
file(GLOB GLFW_SRC "src/external/glfw/src/*.c")

add_executable(app ${SRC} ${GLEW_SRC} ${GLFW_SRC})

# Include directories
target_include_directories(app PRIVATE
        src
        src/external/glew/include
        src/external/glfw/include
)

# Link OpenGL
if(WIN32)
    target_link_libraries(app PRIVATE opengl32)
elseif(APPLE)
    target_link_libraries(app PRIVATE "-framework OpenGL")
else()
    target_link_libraries(app PRIVATE GL)
endif()