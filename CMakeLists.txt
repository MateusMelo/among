cmake_minimum_required(VERSION 3.17)
project(among)

set(CMAKE_CXX_STANDARD 11)
set(SOURCES
    main.cpp
    src/gui/MainWindow.cpp
    src/gui/MainWindow.h
    src/gui/resources/ui.glade
    src/gui/UiRegistry.cpp src/gui/UiRegistry.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
#find_package(mongocxx REQUIRED)
#find_package(bsoncxx REQUIRED)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(include ${GTKMM_INCLUDE_DIRS})
#include_directories(${LIBMONGOCXX_INCLUDE_DIR})
#include_directories(${LIBBSONCXX_INCLUDE_DIR})

add_executable(among ${SOURCES})

#target_link_libraries(${PROJECT_NAME} PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(${PROJECT_NAME} PRIVATE mongo::mongocxx_shared)
target_link_libraries(among ${GTKMM_LIBRARIES})