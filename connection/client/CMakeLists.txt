cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

####################### Project ######################
project(Client)
set(ROOT_NAMESPACE ${PROJECT_NAME})

#################### Source files ####################
set(Headers   
    Client.hpp
    application/Application.hpp
    )
source_group("Headers" FILES ${Headers})

set(Sources
    Client.cpp
    MainClient.cpp
    application/Application.cpp
    
    )
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

####################### Target #######################

add_executable(${PROJECT_NAME} ${ALL_FILES})


#################### Dependencies ####################