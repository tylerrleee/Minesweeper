cmake_minimum_required(VERSION 3.27)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(Minesweeper
        Button.h
        GameState.h
        Tile.h
        Toolbox.h
        minesweeper.h
        GameState.cpp
        minesweeper.cpp
        Tile.cpp
        Toolbox.cpp
        Button.cpp
)
target_link_libraries(Minesweeper sfml-system sfml-window sfml-graphics sfml-audio sfml-network)




