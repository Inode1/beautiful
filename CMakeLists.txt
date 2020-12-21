cmake_minimum_required(VERSION 2.8)

set(PROJECT beutiful)

project(${PROJECT})

set (MAJOR_VERSION  0)
set (MINOR_VERSION  1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(${PROJECT}_TESTS "Enable tests for ${PROJECT}" On)

include_directories(src)

add_executable(${PROJECT} beutiful.cpp)

if(${PROJECT}_TESTS)
    add_subdirectory(test)
    add_dependencies(${PROJECT} unit_test)
endif()
