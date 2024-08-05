cmake_minimum_required(VERSION 3.10)

# set the project name
project(The_spaceship)

file(COPY planet.txt
     DESTINATION ./build)

set(CMAKE_CXX_STANDARD 23)

# add the executable
add_executable(The_spaceship main.cpp planet.txt GameSpaceship.cpp GameSpaceship.h Enemy.cpp Enemy.h Planet.cpp Planet.h Shop.cpp Shop.h SpaceItem.cpp SpaceItem.h Spaceship.cpp Spaceship.h)

add_custom_target(copy_file ALL
DEPENDS The_spaceship
COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/planet.txt $<TARGET_FILE_DIR:The_spaceship>/planet.txt)

