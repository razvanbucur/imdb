cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

####################### Project ######################

project(Server)
set(ROOT_NAMESPACE ${PROJECT_NAME})


######################## Flags #######################

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

#################### Source files ####################

set(Headers
    Server.hpp
    UUIDGenerator.hpp
    MessageInterpreter.hpp
    DataManager.hpp
    )
source_group("Headers" FILES ${Headers})

set(Sources
    Server.cpp
    MainServer.cpp 
    UUIDGenerator.cpp
    MessageInterpreter.cpp
    DataManager.cpp
    )
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

####################### Target #######################

add_executable(${PROJECT_NAME} ${ALL_FILES})

#################### Dependencies ####################

target_link_libraries(${PROJECT_NAME}
    sqlite3
)
