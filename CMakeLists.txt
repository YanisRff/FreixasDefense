cmake_minimum_required(VERSION 3.24)
project(ProjetTowerDefense)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(ProjetTowerDefense main.cpp
        src/MainWindow.cpp
        src/MyScene.cpp
        src/MyView.cpp
        src/MyView.h
        src/Enemy.cpp
        src/Enemy.h
        src/Tower.cpp
        src/Tower.h
        src/Castle.cpp src/Castle.h
        src/GameWidgets.cpp
        src/GameWidgets.h)
target_link_libraries(ProjetTowerDefense
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

