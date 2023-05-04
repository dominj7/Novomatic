cmake_minimum_required (VERSION 3.6)

include_directories(./inc ./src)
file(GLOB SRC "./inc/*.h" "./src/*.cpp")

set(TARGET_NAME strings)


add_executable(${TARGET_NAME} ${SRC})

find_library(cppunit NAMES "cppunit")
target_link_libraries(${TARGET_NAME} ${cppunit})