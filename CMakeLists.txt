# CMake minimum version requirement
cmake_minimum_required(VERSION 3.10)

# Project name
project(DungeonAdventure C)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Add source files
set(SOURCES
    main.c
    game.c
    player.c
    creature.c
    room.c
)

# Add header files (optional for IDEs)
set(HEADERS
    game.h
    player.h
    creature.h
    room.h
)

# Add executable target
add_executable(DungeonAdventure ${SOURCES} ${HEADERS})

# Link cJSON library
add_subdirectory(cJSON)
target_link_libraries(DungeonAdventure cjson)

