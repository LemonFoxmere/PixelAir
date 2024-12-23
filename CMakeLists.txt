cmake_minimum_required(VERSION 3.16)

project(PixelAir VERSION 0.1 LANGUAGES CXX OBJCXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)

qt_add_executable(appPixelAir
    src/main.cpp
    macos/windowHelper/MacOSWindowHelper.h
    macos/windowHelper/MacOSWindowHelper.mm
)

qt_add_qml_module(appPixelAir
    URI PixelAir
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appPixelAir PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPixelAir
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPixelAir
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appPixelAir
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# macos native support with cocoa
find_library(COCOA_LIBRARY Cocoa)
if(COCOA_LIBRARY)
    target_link_libraries(appPixelAir PRIVATE ${COCOA_LIBRARY}) # link if exists
endif()
