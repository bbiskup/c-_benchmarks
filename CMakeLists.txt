project(cpp_benchmarks)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# set(CMAKE_CXX_FLAGS "--std=c++11 -O0")

# set(CMAKE_CXX_COMPILER g++)
# set(CMAKE_CXX_FLAGS "--std=c++11 -g -Wall -O3")

# clang settings
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -O2")


find_package (Boost COMPONENTS 
    system
    chrono
 REQUIRED)

 target_link_libraries(${PROJECT_NAME}
                      ${Boost_LIBRARIES}
                      )
