cmake_minimum_required(VERSION 3.19)
project(InifynityMacro  LANGUAGES C CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(InifynityMacro
    WIN32 MACOSX_BUNDLE
    gui/main.cpp
    gui/mainwindow.cpp
    gui/mainwindow.h
    gui/mainwindow.ui
    engine/macroengine.h
    engine/macroengine.c
    resources/app.rc
)
target_include_directories(InifynityMacro PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/gui
)
target_link_libraries(InifynityMacro
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS InifynityMacro 
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET InifynityMacro 
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
