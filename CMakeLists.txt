cmake_minimum_required(VERSION 3.25)
project(priority_queues)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_CXX_STANDARD 23)

add_library(priority_queues INTERFACE)
add_library(priority_queues::priority_queues ALIAS priority_queues)
target_include_directories(priority_queues INTERFACE include)

add_executable(test test/test.cpp)
add_executable(hold benchmarks/hold/hold.cpp)
target_link_libraries(test PRIVATE priority_queues::priority_queues)
target_link_libraries(hold PRIVATE priority_queues::priority_queues)


