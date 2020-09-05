cmake_minimum_required(VERSION 3.14)
project(Rope)

set(CMAKE_CXX_STANDARD 14)

add_executable(Rope tests/main.cpp src/ImplicitTreap.cpp src/ImplicitTreap.h src/ImplicitTreapNode.cpp src/ImplicitTreapNode.h src/Rope.cpp src/Rope.h)