cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

####################### Project ######################
project(imdb)
set(ROOT_NAMESPACE ${PROJECT_NAME})

#################### Source files ####################
set(Headers
    
    )
source_group("Headers" FILES ${Headers})

set(Sources

    )
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

####################### Target #######################




#################### Dependencies ####################
# set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# message(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(connection/client)
add_subdirectory(connection/server)