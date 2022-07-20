#                    _       _         
#   /\/\   ___  _ __(_) ___ | | ____ _ 
#  /    \ / _ \| '__| |/ _ \| |/ / _` |
# / /\/\ \ (_) | |  | | (_) |   < (_| |
# \/    \/\___/|_|  |_|\___/|_|\_\__,_|
#                                      

cmake_minimum_required(VERSION 2.22)
project(Sample CXX)


# find_package(imgui CONFIG REQUIRED)
if(UNIX) # Configuration for Linux/Unix System
find_package(glfw3 CONFIG REQUIRED)
find_package(PkgConfig)
pkg_check_modules(LIBIMGUI REQUIRED imgui)
include_directories(${LIBIMGUI_INCLUDE_DIRS})
pkg_check_modules(LIBVLC REQUIRED libvlc)
include_directories(${LIBVLC_INCLUDE_DIRS})
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
elseif(WIN32 AND CMAKE_CL_64)
# Configuration for x64-windows
find_package(glfw3 CONFIG REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR}/external/x64-windows/share/)
find_package(imgui CONFIG REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR}/external/x64-windows/share)
find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR}/external/x64-windows/share)
find_package(vlc REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR}/external/x64-windows/share)
else()
message(FATAL_ERROR "This app is only for x64-windows or linux")
endif()

message(${PROJECT_NAME})
file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
add_executable(sample ${SRC})
if(UNIX)
target_link_libraries(sample ${LIBIMGUI_LIBRARIES} glfw OpenGL::GL ${LIBVLC_LIBRARIES})
target_include_directories(sample PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/)
else()
# Configuration for x64-windows
target_link_libraries(sample imgui::imgui glfw OpenGL::GL vlc::vlc vlc::vlccore glad::glad)
target_include_directories(sample PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/)
endif()