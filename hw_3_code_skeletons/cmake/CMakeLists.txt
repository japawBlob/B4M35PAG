cmake_minimum_required(VERSION 3.5)
project(HW3)

find_package(MPI)
include_directories(${MPI_INCLUDE_PATH})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -std=c++17 -march=native")
endif()

add_executable(HeatDiffusion ../src/HeatDiffusion.cpp)
target_compile_options(HeatDiffusion PRIVATE ${MPI_CXX_COMPILE_FLAGS})
target_link_libraries(HeatDiffusion ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS})
