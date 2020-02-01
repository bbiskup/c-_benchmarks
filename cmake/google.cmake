# Google test and benchmark

message("IN GOOGLE ${CMAKE_CXX_COMPILER}")

# Disable warnings for google test & benchmark
set(MASTER_CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "-stdlib=libc++")
# Google benchmark
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
set(BENCHMARK_ENABLE_LTO ON CACHE BOOL "Enable link time optimization" FORCE)
add_subdirectory(vendor/google/benchmark)

# Google test (dependency of benchmark)
set(GOOGLETEST_VERSION 0)
add_subdirectory(vendor/google/googletest/googletest)
set(CMAKE_CXX_FLAGS "${MASTER_CMAKE_CXX_FLAGS}")
