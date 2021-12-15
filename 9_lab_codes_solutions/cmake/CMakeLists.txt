cmake_minimum_required(VERSION 3.5)
project(LabMPI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(MPI)
include_directories(${MPI_INCLUDE_PATH})

add_executable(HelloWorld ../src/HelloWorld.cpp)
target_compile_options(HelloWorld PRIVATE ${MPI_CXX_COMPILE_FLAGS})
target_link_libraries(HelloWorld ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS})

add_executable(Iddqd ../src/Iddqd.cpp)
target_compile_options(Iddqd PRIVATE ${MPI_CXX_COMPILE_FLAGS})
target_link_libraries(Iddqd ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS})

add_executable(Idkfa ../src/Idkfa.cpp)
target_compile_options(Idkfa PRIVATE ${MPI_CXX_COMPILE_FLAGS})
target_link_libraries(Idkfa ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS})

add_executable(VectorNormalization ../src/VectorNormalization.cpp ../src/Utils.hpp)
target_compile_options(VectorNormalization PRIVATE ${MPI_CXX_COMPILE_FLAGS})
target_link_libraries(VectorNormalization ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS})
