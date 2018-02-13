cmake_minimum_required(VERSION 3.9)
project(GL1)

set(CMAKE_CXX_STANDARD 11)

add_executable(GL1 main.cpp)

IF(APPLE)
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
    FIND_LIBRARY(GLUT_LIBRARY GLUT )
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    SET(EXTRA_LIBS ${GLUT_LIBRARY} ${OpenGL_LIBRARY})
    target_link_libraries(GL1 ${EXTRA_LIBS})
ENDIF (APPLE)

