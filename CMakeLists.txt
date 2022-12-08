cmake_minimum_required(VERSION 3.23)
project(Langford_OpenMP)

set(CMAKE_CXX_STANDARD 17)

add_executable(Langford_OpenMP main.cpp Langford_par.h Langford.h)

find_package(TBB)
#target_link_libraries(Langford_OpenMP TBB::tbb)

find_package(OpenMP)
target_compile_options(Langford_OpenMP PRIVATE ${OpenMP_C_FLAGS})
target_link_libraries(Langford_OpenMP PUBLIC TBB::tbb PRIVATE ${OpenMP_C_FLAGS})
add_definitions(-fopenmp -Wall)

