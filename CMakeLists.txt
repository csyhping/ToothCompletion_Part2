cmake_minimum_required(VERSION 3.1)
project(ToothCompletionPart2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# libigl
option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)
option(LIBIGL_WITH_OPENGL_GLFW_IMGUI "Use ImGui"          ON)

find_package(LIBIGL REQUIRED QUIET)

# Add your project files
FILE(GLOB SRCFILES *.cpp)
FILE(GLOB HEADFILES *.h)
add_executable(${PROJECT_NAME}_bin ${SRCFILES} ${HEADFILES} ${LIBIGL_EXTRA_SOURCES})
target_link_libraries(${PROJECT_NAME}_bin igl::core igl::opengl_glfw igl::opengl_glfw_imgui)
