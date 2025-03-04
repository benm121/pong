cmake_minimum_required(VERSION 3.5)

project(project VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    include
    /usr/local/include/glad
    /usr/include/GLFW
)

target_link_libraries(${PROJECT_NAME} OpenGL::GL glad glfw dl pthread)

