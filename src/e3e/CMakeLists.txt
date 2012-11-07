find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${GLEW_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

set(extlibs ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})


file(
	GLOB
	e3e_src
	*pp
)

add_library(e3e SHARED ${e3e_src})
target_link_libraries(e3e ${extlibs})
