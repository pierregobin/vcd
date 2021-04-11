cmake_minimum_required(VERSION 3.10)

if (MINGW32)
	set(CMAKE_SYSTEM_NAME Windows)
	SET(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
	SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
	SET(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
	set(CMAKE_RANLIB x86_64-w64-mingw32-ranlib)
	set(SDL2_INCLUDE_DIR /usr/x86_64-w64-mingw32/include)
	set(SDL2_LIBRARY /usr/x86_64-w64-mingw32/lib)
endif()

set(CMAKE_CXX_FLAGS "-O3")
SET(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-Xlinker -Map=output.map" )
set(CMAKE_BUILD_TYPE RelWithDebInfo)

project(vcd)

include_directories(/usr/include/glib-2.0/)


add_library(${CMAKE_PROJECT_NAME} SHARED
	./src/vcd.c
)
