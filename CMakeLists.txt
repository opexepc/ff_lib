cmake_minimum_required(VERSION 3.10)
project(ff VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ff STATIC
    src/check.cpp
    src/copy.cpp
    src/create.cpp
    src/find.cpp
    src/get.cpp
    src/print.cpp
    src/read.cpp
    src/remove.cpp
    src/utils.cpp
    src/write.cpp
)

install(TARGETS ff DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

target_include_directories(ff PUBLIC include)
