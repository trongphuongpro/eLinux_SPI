cmake_minimum_required(VERSION 3.4)

#-----------------------------------------------------------------------------#
find_package(Threads REQUIRED)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CXX_COMPILER arm-linux-g++)
set(CMAKE_C_COMPILER arm-linux-gcc)
#-----------------------------------------------------------------------------#

set(TARGET testbench)
set(SOURCE ../src/spi.cpp test.cpp)

add_executable(${TARGET} ${SOURCE})
target_include_directories(${TARGET} PUBLIC ../include
							/home/trongphuong/Work/BBB/libraries/crc32/include)

#-----------------------------------------------------------------------------#
target_compile_options(${TARGET} PUBLIC -std=gnu++11
										-O2
										-Werror
										-Wall
)
#-----------------------------------------------------------------------------#
install(TARGETS ${TARGET} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)