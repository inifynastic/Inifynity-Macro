cmake_minimum_required(VERSION 3.19)
project(InifynityMacro  LANGUAGES C CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(InifynityMacro
    WIN32 MACOSX_BUNDLE
	
    gui/include/mainwindow.h
	gui/include/handledata.h

	
    gui/source/main.cpp
    gui/source/mainwindow.cpp
    gui/source/mainwindow.ui
	gui/source/handledata.cpp

    engine/include/enginelogs.h
    engine/include/handlehotkey.h
    engine/include/converter.hpp
	engine/include/enginebridge.hpp	
    engine/include/macroengine.h
	engine/include/inifynityengine.hpp

	engine/core/enginebridge.cpp
    engine/core/macroengine.c
	engine/core/inifynityengine.cpp
    
	engine/hotkey/converter.cpp
    engine/hotkey/handlehotkey.c
    
	engine/logs/enginelogs.cpp
    
    resources/app.rc

)
target_include_directories(InifynityMacro PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/guis
    ${CMAKE_SOURCE_DIR}/shared
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
