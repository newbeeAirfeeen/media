cmake_minimum_required(VERSION 3.20)
project(media)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src/flv)
add_subdirectory(src/mpeg)

#add_executable(main main.cpp)
#target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)
#target_link_libraries(main PUBLIC mpeg flv)

