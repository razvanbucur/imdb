cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

####################### Project ######################
project(Server)
set(ROOT_NAMESPACE ${PROJECT_NAME})

#################### Source files ####################
set(Headers
    Server.hpp    
    )
source_group("Headers" FILES ${Headers})

set(Sources
    Server.cpp
    MainServer.cpp   
    )
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

####################### Target #######################

add_executable(${PROJECT_NAME} ${ALL_FILES})


#################### Dependencies ####################