include_directories(${CMAKE_SOURCE_DIR}/include/impl/detail/mpeg)
file(GLOB MPEG_SRC ./*.c)
add_library(mpeg ${MPEG_SRC})
target_include_directories(mpeg PUBLIC ${CMAKE_SOURCE_DIR}/include)