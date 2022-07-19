cmake_minimum_required(VERSION 2.22)
project(Sample CXX)


# find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(PkgConfig)
pkg_check_modules(LIBIMGUI REQUIRED imgui)
include_directories(${LIBIMGUI_INCLUDE_DIRS})
pkg_check_modules(LIBVLC REQUIRED libvlc)
include_directories(${LIBVLC_INCLUDE_DIRS})
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

message(${PROJECT_NAME})
file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
add_executable(sample ${SRC})
target_link_libraries(sample ${LIBIMGUI_LIBRARIES} glfw OpenGL::GL ${LIBVLC_LIBRARIES})
target_include_directories(sample PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/)