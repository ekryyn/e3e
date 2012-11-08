find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL sdl REQUIRED)
pkg_check_modules(SDL_IMAGE SDL_image REQUIRED)

include_directories(${GLEW_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${SDL_INCLUDE_DIRS})
include_directories(${SDL_IMAGE_INCLUDE_DIRS})

set(extlibs ${GLEW_LIBRARY} ${OPENGL_LIBRARIES} ${SDL_LIBRARIES} ${SDL_IMAGE_LIBRARIES})


file(
	GLOB
	e3e_src
	*pp
)

add_library(e3e SHARED ${e3e_src})
target_link_libraries(e3e ${extlibs})
