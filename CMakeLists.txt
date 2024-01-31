cmake_minimum_required(VERSION 3.19)
project(client)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES src/server.cpp src/connection_handler.cpp)
set(HEADERS include/server.h include/connection_handler.h)

set(Boost_INCLUDE_DIR "../vcpkg_installed/x64-linux/include/")
list(APPEND CMAKE_PREFIX_PATH "../vcpkg_installed/x64-linux/share/")
include_directories("../vcpkg_installed/x64-linux/include/")

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_library(server-lib STATIC ${SOURCES} ${HEADERS})

target_include_directories(server-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_precompile_headers(server-lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h)

add_executable(server src/main.cpp)

target_link_libraries(server PRIVATE server-lib ${Boost_LIBRARIES})