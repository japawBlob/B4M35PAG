cmake_minimum_required(VERSION 3.5)
project(HW1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native")
endif()

add_executable(InstanceGenerator ../src/InstanceGenerator.cpp)
target_link_libraries(InstanceGenerator ${CMAKE_THREAD_LIBS_INIT} )

add_executable(LU ../src/LU.cpp)
target_link_libraries(LU ${CMAKE_THREAD_LIBS_INIT} )
