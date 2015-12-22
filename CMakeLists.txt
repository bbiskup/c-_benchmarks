project(cpp_benchmarks)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
set(CMAKE_CXX_FLAGS "--std=c++11 -O0")


find_package (Boost COMPONENTS 
    system
    chrono
 REQUIRED)

 target_link_libraries(${PROJECT_NAME}
                      ${Boost_LIBRARIES}
                      )
