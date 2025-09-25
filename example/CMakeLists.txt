cmake_minimum_required(VERSION 3.10)
project(ff_example_app)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC "main.cpp")

add_executable(${PROJECT_NAME} ${SRC})

add_library(ff STATIC IMPORTED)
set_target_properties(ff PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../build/libff.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/../include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE ff)