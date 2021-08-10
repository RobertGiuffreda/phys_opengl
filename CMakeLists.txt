cmake_minimum_required(VERSION 3.16.3)

project(BallPhys)

# BallPhys
file(GLOB_RECURSE SOURCE_FILE
    ${CMAKE_SOURCE_DIR}/BallPhys/src/*.c
    ${CMAKE_SOURCE_DIR}/BallPhys/src/*.cpp)

file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/BallPhys/src/*.h
    ${CMAKE_SOURCE_DIR}/BallPhys/src/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILE} ${HEADER_FILES})
# OpenGL
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

set(DEPENDENCIES "${CMAKE_SOURCE_DIR}/depend")

# GLFW
set(GLFW_DIR "${DEPENDENCIES}/GLFW")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory( depend/GLFW )
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# glad
set(GLAD_DIR "${DEPENDENCIES}/glad")
add_library("glad" STATIC "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# glm
add_library("glm" INTERFACE)
target_include_directories("glm" INTERFACE "${DEPENDENCIES}/glm")
target_link_libraries(${PROJECT_NAME} "glm")

# stb_image
set(STB_DIR "${DEPENDENCIES}/stb_image")
add_library("stb_image" STATIC "${STB_DIR}/stb_image.cpp")
target_include_directories("stb_image" PRIVATE "${STB_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${STB_DIR}")
target_link_libraries(${PROJECT_NAME} "stb_image")