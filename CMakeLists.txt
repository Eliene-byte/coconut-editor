cmake_minimum_required(VERSION 3.21)
project(CoConutEditor VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(CoConutEditor
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/timelinewidget.h
    src/timelinewidget.cpp
    src/clipitem.h
    src/clipitem.cpp
)

target_link_libraries(CoConutEditor PRIVATE
    Qt6::Widgets
)

if(WIN32)
    set_target_properties(CoConutEditor PROPERTIES WIN32_EXECUTABLE ON)
    add_custom_command(TARGET CoConutEditor POST_BUILD
        COMMAND ${Qt6_DIR}/../../../bin/windeployqt.exe $<TARGET_FILE:CoConutEditor>
    )
endif()
