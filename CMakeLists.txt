cmake_minimum_required(VERSION 3.14)
project(Rope)
set(CMAKE_CXX_STANDARD 14)

add_executable(Rope tests/main.cpp src/ImplicitTreap-inl.h src/ImplicitTreap.h src/ImplicitTreapNode-inl.h src/ImplicitTreapNode.h include/Rope-inl.h include/Rope.h src/RopeIterator-inl.h src/RopeConstIterator-inl.h)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,10000000")
