cmake_minimum_required(VERSION 3.24)
project(FreixasDefense)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(FreixasDefense main.cpp
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
target_link_libraries(FreixasDefense
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

