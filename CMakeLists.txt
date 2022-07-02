cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_COMPILER gcc)

add_compile_options(-std=c11)

project(GenericsWindow)

include_directories(./include)

set(HEAD_FILES
    ./include/test_generics.h)

set(SOURCE_FILES
    ./src/test_generics.c)

add_executable(${PROJECT_NAME} ${HEAD_FILES} ${SOURCE_FILES})
