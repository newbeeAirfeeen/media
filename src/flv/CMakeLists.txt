file(GLOB MPEG_SRC ./*.c)
add_library(flv ${MPEG_SRC})
target_include_directories(flv PUBLIC ${PROJECT_SOURCE_DIR}/include)