#==============================================================================
# Copyright (c) 2012 Evgeny Proydakov <lord.tiran@gmail.com>
#==============================================================================

IF(MSVC)
    COMPILER_MSVC_SET_STATIC_RUNTIME()
ENDIF(MSVC)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FIND_PACKAGE(OpenGL)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})

FIND_PACKAGE(GLUT)
INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR})

SET(SOURCE_FILES
    main.cpp
    )

I_ADD_EXECUTABLE(opengl_get_system_info ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(opengl_get_system_info ${OPENGL_LIBRARIES})
TARGET_LINK_LIBRARIES(opengl_get_system_info ${GLUT_LIBRARIES})
