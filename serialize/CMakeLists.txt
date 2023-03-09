cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
project(serialize VERSION 1.0.0)

add_executable(serialize
                src/Serializable.hpp
                src/ListNode.hpp
                src/ListRand.hpp
                src/ListRand.cpp
                src/Main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})