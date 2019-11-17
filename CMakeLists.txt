cmake_minimum_required(VERSION 3.0)

find_package(Threads REQUIRED)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CXX_COMPILER arm-g++)
set(CMAKE_C_COMPILER arm-gcc)

add_compile_options(
	-std=gnu++11
	-Wall
	-Werror
	-O2
)


set(LIB_NAME spi)
add_library(${LIB_NAME} STATIC src/spi.cpp)
target_include_directories(${LIB_NAME} PUBLIC include)
install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)