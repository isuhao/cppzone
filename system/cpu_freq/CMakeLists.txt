#==============================================================================
# Copyright (c) 2018 Evgeny Proydakov <e.proydakov@gmail.com>
#==============================================================================

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(SOURCE_FILES
    main.cpp
    )

I_ADD_EXECUTABLE(system_cpu_freq ${SOURCE_FILES})
