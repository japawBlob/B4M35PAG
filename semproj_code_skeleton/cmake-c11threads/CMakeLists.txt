cmake_minimum_required(VERSION 3.5)
project(SemProjStorage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads)

add_executable(Storage ../src/Storage.cpp ../src/Utils.h)
target_link_libraries(Storage ${CMAKE_THREAD_LIBS_INIT})

add_executable(InstanceGenerator ../src/InstanceGenerator.cpp ../src/Utils.h)