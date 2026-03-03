cmake_minimum_required(VERSION 3.14)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
project(Lab2_Threads LANGUAGES CXX)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_COMPILER "/usr/bin/x86_64-w64-mingw32-g++")
endif()

include(FetchContent)
FetchContent_Declare(
    doctest
    URL https://github.com/doctest/doctest/archive/refs/tags/v2.4.11.zip
)
FetchContent_MakeAvailable(doctest)

add_library(thread_lib STATIC
    src/thread_functions.cpp
    include/thread_functions.h
)

add_executable(lab2_threads src/main.cpp)
target_link_libraries(lab2_threads PRIVATE thread_lib)

add_executable(tests tests/test_threads.cpp)
target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${doctest_SOURCE_DIR}
)
target_link_libraries(tests PRIVATE thread_lib)

enable_testing()
add_test(NAME ThreadTests COMMAND tests)