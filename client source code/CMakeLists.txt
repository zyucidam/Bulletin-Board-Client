cmake_minimum_required(VERSION 3.25)
project(BulletinBoardClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(BulletinBoardClient main.cpp Command.cpp Connect.cpp Command.h Connect.h)
target_link_libraries(BulletinBoardClient ws2_32)