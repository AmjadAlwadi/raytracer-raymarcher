cmake_minimum_required(VERSION 3.5)
project(CG1_Tracer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT WIN32)
  find_package(Threads REQUIRED)
  find_package(X11 REQUIRED)
endif()

# This directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
if(APPLE)
   include_directories(AFTER "/opt/X11/include")
endif()


# which source files to use
file(GLOB common_src "common/*.cpp")
file(GLOB camera_src "camera/*.cpp")
file(GLOB light_src "light/*.cpp")
file(GLOB primitive_src "primitive/*.cpp")
file(GLOB renderer_src "renderer/*.cpp")
file(GLOB scene_src "scene/*.cpp")
file(GLOB shader_src "shader/*.cpp")


# The tracey library
add_library(tracey STATIC ${common_src} ${camera_src} ${light_src}
        ${primitive_src} ${renderer_src} ${scene_src} ${shader_src})
if(NOT WIN32)
    target_link_libraries(tracey ${CMAKE_THREAD_LIBS_INIT} ${X11_LIBRARIES})
endif()


# Executables
add_executable(tracey_main main.cpp)
target_link_libraries(tracey_main tracey)



if("${CMAKE_CURRENT_LIST_DIR}/light/ambientlight.cpp" IN_LIST light_src)
    add_definitions(-DAMBIENTLIGHT_FOUND)
endif()
if("${CMAKE_CURRENT_LIST_DIR}/light/spotlight.cpp" IN_LIST light_src)
    add_definitions(-DSPOTLIGHT_FOUND)
endif()
if("${CMAKE_CURRENT_LIST_DIR}/primitive/objmodel.cpp" IN_LIST primitive_src)
    add_definitions(-DOBJMODEL_FOUND)
endif()




if("${CMAKE_CURRENT_LIST_DIR}/renderer/superrenderer.cpp" IN_LIST renderer_src)
    add_definitions(-DSUPERRENDERER_FOUND)
endif()




