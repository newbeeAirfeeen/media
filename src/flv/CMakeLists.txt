file(GLOB MPEG_SRC ./*.c)
add_library(flv ${MPEG_SRC})
message("-----------------------------${CMAKE_SOURCE_DIR}")
target_include_directories(flv PUBLIC ${CMAKE_SOURCE_DIR}/include)