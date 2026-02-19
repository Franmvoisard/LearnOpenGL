cmake_minimum_required(VERSION 4.1)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(LearnOpenGL main.cpp "libraries/glad/src/glad.c"
        src/rendering/shader.h
        src/rendering/shader.cpp)

target_include_directories(LearnOpenGL PRIVATE "libraries/glfw-3.4.bin.WIN64/include")
target_include_directories(LearnOpenGL PRIVATE "libraries/glad/include")

target_link_libraries(LearnOpenGL PRIVATE "${CMAKE_SOURCE_DIR}/libraries/glfw-3.4.bin.WIN64/lib-vc2022/glfw3.lib")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})