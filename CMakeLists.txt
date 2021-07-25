cmake_minimum_required(VERSION 3.15)
project(CP)

set(CMAKE_CXX_STANDARD 11)



set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -D_SHIT")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )




add_executable(A A.cpp)
add_executable(B B.cpp)
add_executable(C C.cpp)
add_executable(D D.cpp)
add_executable(E E.cpp)
add_executable(F F.cpp)
add_executable(G G.cpp)



add_executable(gen Tester/gen.cpp)
add_executable(main Tester/main.cpp)
add_executable(brute Tester/brute.cpp)

