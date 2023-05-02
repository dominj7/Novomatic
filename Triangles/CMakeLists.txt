cmake_minimum_required (VERSION 3.6)

include_directories(./inc ./src)
file(GLOB SRC "./inc/*.h" "./src/*.cpp")

set(TARGET_NAME triangles)


add_executable(${TARGET_NAME} ${SRC})

find_library(SDL2 NAMES "SDL2")
target_link_libraries(${TARGET_NAME} ${SDL2})
