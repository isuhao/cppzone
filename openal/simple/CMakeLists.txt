#==============================================================================
# Copyright (c) 2012 Evgeny Proydakov <lord.tiran@gmail.com>
#==============================================================================

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${OPENAL_SOUND_PATH})

CONFIGURE_FILE(config.simple.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/config_simple.h)

SET(SOUND_FILE
    grid.wav
    )

SET(CONFIG_FILES
    config_simple.h
    )

SET(SOURCE_FILES
    main.cpp
    )

I_ADD_EXECUTABLE(openal_simple ${SOURCE_FILES} ${CONFIG_FILES} ${SOUND_FILE})
ADD_DEPENDENCIES(openal_simple openal_sound)
TARGET_LINK_LIBRARIES(openal_simple ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(openal_simple openal_sound)
