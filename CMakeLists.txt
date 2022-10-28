cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

####################### Project ######################
project(imdb)
set(ROOT_NAMESPACE ${PROJECT_NAME})

#################### Source files ####################
set(Headers
     src/Entities/Movie.hpp
     src/Entities/Actor.hpp
     src/Entities/Director.hpp
     src/Entities/User.hpp
    )
source_group("Headers" FILES ${Headers})

set(Sources
    src/main.cpp
    )
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

####################### Target #######################

add_executable(${PROJECT_NAME} ${ALL_FILES})


#################### Dependencies ####################