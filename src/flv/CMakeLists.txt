include_directories(${CMAKE_SOURCE_DIR}/include/impl/detail/flv)
file(GLOB MPEG_SRC ./*.c)
add_library(flv ${MPEG_SRC})