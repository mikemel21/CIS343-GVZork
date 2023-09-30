cmake_minimum_required(VERSION 3.26)
project(GVZork)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(GVZork
        Game.cpp
        Game.hpp
        Item.cpp
        Item.hpp
        Location.cpp
        Location.hpp
        NPC.cpp
        NPC.hpp)
