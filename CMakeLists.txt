cmake_minimum_required(VERSION 3.20)
project(Joltan C)

set(CMAKE_C_STANDARD 11)

# Source files
file(GLOB SRC "src/*.c")

add_executable(app ${SRC})

# Libraries
if(WIN32)
    target_link_libraries(app PRIVATE glfw3 glew32 opengl32)
elseif(APPLE)
    target_link_libraries(app PRIVATE glfw GLEW "-framework OpenGL")
else()
    target_link_libraries(app PRIVATE glfw GLEW GL)
endif()