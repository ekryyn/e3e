cmake_minimum_required(VERSION 2.6)
project(e3e-graphics)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(PkgConfig REQUIRED)
find_package(SFML 1.6 REQUIRED system window graphics)

pkg_check_modules(SDL sdl REQUIRED)
pkg_check_modules(SDL_IMAGE SDL_image REQUIRED)


include_directories(${SFML_INCLUDE_DIR})
include_directories(${SDL_INCLUDE_DIRS})
include_directories(${SDL_IMAGE_INCLUDE_DIRS})

set(mainLibs ${SFML_LIBRARIES} ${SDL_LIBRARIES} ${SDL_IMAGE_LIBRARIES})

file(
	GLOB
	MAIN_SOURCES
	src/*.cpp
)

add_subdirectory(src/e3e/)

add_executable(e3e-graphics ${MAIN_SOURCES})

target_link_libraries(e3e-graphics e3e ${mainLibs})



configure_file(src/e3e/shaders/e3e.vert shaders/e3e.vert COPYONLY)
configure_file(src/e3e/shaders/e3e.frag shaders/e3e.frag COPYONLY)
