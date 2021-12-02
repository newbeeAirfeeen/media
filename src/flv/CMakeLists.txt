file(GLOB MPEG_SRC ./*.c)
add_library(flv ${MPEG_SRC})
target_include_directories(flv PUBLIC ${CMAKE_SOURCE_DIR}/include)