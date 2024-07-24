cmake_minimum_required(VERSION 3.10)

# set the project name
project(The_spaceship)

file(COPY planet.txt
     DESTINATION ./build)

# add the executable
add_executable(The_spaceship main.cpp planet.txt)

add_custom_target(copy_file ALL
DEPENDS The_spaceship
COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/planet.txt $<TARGET_FILE_DIR:The_spaceship>/planet.txt)