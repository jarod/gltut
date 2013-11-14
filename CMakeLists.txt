cmake_minimum_required(VERSION 2.6)

project(gltut C CXX)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)


find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

if(WIN32)
add_definitions(-DWIN32)
else()
add_definitions(-DLOAD_X11)
endif()

add_subdirectory(glsdk)

include_directories(
${glload_SOURCE_DIR}/include
${glutil_SOURCE_DIR}/include
${glimg_SOURCE_DIR}/include
${OPENGL_INCLUDE_DIRS}
${GLFW_INCLUDE_DIRS}
)

set(LIBS
${OPENGL_LIBRARIES}
glload
glutil
glimg
${GLFW_STATIC_LIBRARIES}
)

add_subdirectory(framework)

set(LIBS ${LIBS} framework)

add_subdirectory(Tut01HelloTriangle)

add_subdirectory(Tut02PlayingWithColors)

add_subdirectory(Tut03OpenGLsMovingTriangle)
