set(CMAKE_CXX_COMPILER "/usr/bin/g++")
cmake_minimum_required(VERSION 3.13.1)
project(cpp_benchmarks
  VERSION 0.1
  LANGUAGES CXX
)

# Hard-coding build type since running benchmarks
# in debug mode does not make sense
set(CMAKE_BUILD_TYPE Release)

aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# clang settings
set(CMAKE_CXX_FLAGS "-Wall -Werror -O3 -DFMT_HEADER_ONLY")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include(cmake/google.cmake)

find_package (Boost COMPONENTS 
    system
 REQUIRED)


 target_include_directories(${PROJECT_NAME}
    PRIVATE vendor
 )

 target_link_libraries(${PROJECT_NAME}
                      ${Boost_LIBRARIES}
                      benchmark
                      )
