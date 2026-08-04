cmake_minimum_required(VERSION 3.19)
project(InifynityMacro LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)

pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11 xtst)

add_executable(InifynityMacro
    gui/main.c
    gui/mainwindow.c
    gui/mainwindow.h
    engine/macroengine.h
    engine/macroengine.c
)
target_include_directories(InifynityMacro PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/gui
)
target_link_libraries(InifynityMacro PRIVATE
    PkgConfig::GTK4
    PkgConfig::X11
    Threads::Threads
)

install(TARGETS InifynityMacro
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
