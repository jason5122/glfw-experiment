cmake_minimum_required(VERSION 3.10)
project(glfw-experiment)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# https://github.com/Dav1dde/glad/issues/186
add_subdirectory(glad/)

add_executable(glfw-experiment glfw_experiment.cpp)
target_link_libraries(glfw-experiment OpenGL::GL glfw glad)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
