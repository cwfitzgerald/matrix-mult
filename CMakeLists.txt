cmake_minimum_required(VERSION 3.12)
project(matrix-mult LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(benchmark CONFIG REQUIRED)

file(GLOB_RECURSE SSE_FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS "*-sse.cpp")
file(GLOB_RECURSE AVX_FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS "*-avx.cpp")
file(GLOB_RECURSE CPP_FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.hpp")

set_property(SOURCE ${SSE_FILES} benchmark.cpp APPEND PROPERTY COMPILE_FLAGS "-msse4.2")
set_property(SOURCE ${AVX_FILES} APPEND PROPERTY COMPILE_FLAGS "-mavx2 -mfma")

add_executable(matrix-mult ${SSE_FILES} ${AVX_FILES} ${CPP_FILES} benchmark.cpp)
target_compile_options(matrix-mult PRIVATE -fdiagnostics-color=always)
target_link_libraries(matrix-mult PRIVATE benchmark::benchmark benchmark::benchmark_main)
