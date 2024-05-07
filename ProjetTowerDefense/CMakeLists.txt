cmake_minimum_required(VERSION 3.27)
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

add_executable(ProjetTowerDefense main.cpp)
target_link_libraries(ProjetTowerDefense
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

