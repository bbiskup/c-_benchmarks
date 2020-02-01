set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
project(cpp_benchmarks)
cmake_minimum_required(VERSION 3.13.1)
aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# clang settings
set(CMAKE_CXX_FLAGS "-g -Wall -Werror -O3")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include(cmake/google.cmake)

find_package (Boost COMPONENTS 
    system
    chrono
 REQUIRED)



 target_link_libraries(${PROJECT_NAME}
                      ${Boost_LIBRARIES}
                      )
