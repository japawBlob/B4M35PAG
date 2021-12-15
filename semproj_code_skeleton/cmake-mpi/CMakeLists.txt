cmake_minimum_required(VERSION 3.5)
project(SemProjStorage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(MPI)
include_directories(${MPI_INCLUDE_PATH})

add_executable(Storage ../src/Storage.cpp ../src/Utils.h)
target_compile_options(Storage PRIVATE ${MPI_CXX_COMPILE_FLAGS})
target_link_libraries(Storage ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS})

add_executable(InstanceGenerator ../src/InstanceGenerator.cpp ../src/Utils.h)