###############################################################################
# Copyright (c) 2012 Evgeny Proydakov <lord.tiran@gmail.com>
###############################################################################

MACRO(I_ADD_EXECUTABLE args)

MESSAGE(STATUS "create ${ARGV0}")
SET(EXECUTABLE_NAME ${ARGV0})
ADD_EXECUTABLE(${EXECUTABLE_NAME} ${ARGN})
SOURCE_GROUP(source FILES ${ARGN})
SET_PROPERTY(TARGET ${EXECUTABLE_NAME} PROPERTY FOLDER ${GLOBAL_PROJECT_FOLDER})

ENDMACRO(I_ADD_EXECUTABLE)

###############################################################################

MACRO(I_ADD_DIRECTX_EXECUTABLE args)

MESSAGE(STATUS "create ${ARGV0}")
SET(EXECUTABLE_NAME ${ARGV0})
ADD_EXECUTABLE(${EXECUTABLE_NAME} WIN32 ${ARGN})
SOURCE_GROUP(source FILES ${ARGN})
SET_PROPERTY(TARGET ${EXECUTABLE_NAME} PROPERTY FOLDER ${GLOBAL_PROJECT_FOLDER})

ENDMACRO(I_ADD_DIRECTX_EXECUTABLE)

###############################################################################

MACRO(I_ADD_LIBRARY args)

SET(LIBRARY_NAME ${ARGV0})
ADD_LIBRARY(${LIBRARY_NAME} STATIC ${ARGN})
SOURCE_GROUP(source FILES ${ARGN})
SET_PROPERTY(TARGET ${LIBRARY_NAME} PROPERTY FOLDER ${GLOBAL_PROJECT_FOLDER})

ENDMACRO(I_ADD_LIBRARY)

###############################################################################

MACRO(I_ADD_SHARED_LIBRARY args)

SET(LIBRARY_NAME ${ARGV0})
ADD_LIBRARY(${LIBRARY_NAME} SHARED ${ARGN})
SOURCE_GROUP(source FILES ${ARGN})
SET_PROPERTY(TARGET ${LIBRARY_NAME} PROPERTY FOLDER ${GLOBAL_PROJECT_FOLDER})

ENDMACRO(I_ADD_SHARED_LIBRARY)

###############################################################################

MACRO(I_ADD_LUA_LIBRARY args)

SET(LIBRARY_NAME ${ARGV0})
ADD_LIBRARY(${LIBRARY_NAME} SHARED ${ARGN})
SOURCE_GROUP(source FILES ${ARGN})
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES DEFINE_SYMBOL LUA_EXPORT)
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES FOLDER ${GLOBAL_PROJECT_FOLDER})

ENDMACRO(I_ADD_LUA_LIBRARY)
