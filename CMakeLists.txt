cmake_minimum_required(VERSION 3.14)
project(Rope)

set(CMAKE_CXX_STANDARD 14)

add_executable(Rope src/main.cpp src/Rope.h src/Rope.cpp src/ImplicitTreap.cpp src/ImplicitTreap.h src/ImplicitTreapNode.cpp src/ImplicitTreapNode.h)