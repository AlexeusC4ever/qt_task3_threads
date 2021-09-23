cmake_minimum_required(VERSION 3.5)

project(qt_task3_threads)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV 3.4.3 REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        convert.h
        convert.cpp
        thread.h
        thread.cpp
)

add_executable(qt_task3_threads ${PROJECT_SOURCES})

target_link_libraries(qt_task3_threads PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS})

