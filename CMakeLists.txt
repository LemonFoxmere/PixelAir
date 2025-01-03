cmake_minimum_required(VERSION 3.16)

project(PixelAir VERSION 0.1 LANGUAGES CXX OBJCXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(Qt6 REQUIRED COMPONENTS Quick Test)
find_package(GTest REQUIRED)

qt_add_executable(PixelAir
    main.cpp
)

qt_add_qml_module(PixelAir
    URI PixelAir
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        macos/windowHelper/MacOSWindowHelper.h macos/windowHelper/MacOSWindowHelper.mm
        src/models/avltree.h src/models/avltree.cpp
        src/models/rasterlayer.h src/models/rasterlayer.cpp
        src/controllers/canvascontroller.h src/controllers/canvascontroller.cpp
        src/views/canvasrenderer.h src/views/canvasrenderer.cpp
        src/views/shaders/gradient/gradientshader.h src/views/shaders/gradient/gradientshader.cpp
        main.cpp
    RESOURCES
        resources.qrc
        src/views/shaders/gradient/gradientshader.frag
        src/views/shaders/gradient/gradientshader.vert
)

qt_add_resources(app_resources resources.qrc)
target_sources(PixelAir PRIVATE ${app_resources})

# test executables
qt_add_executable(TestAVLTree
    tests/tst_avltree.cpp
    src/models/avltree.h src/models/avltree.cpp
)
qt_add_executable(TestRasterLayer
    tests/tst_rasterlayer.cpp
    src/models/avltree.h src/models/avltree.cpp
    src/models/rasterlayer.h src/models/rasterlayer.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(PixelAir PROPERTIES
    # MACOSX_BUNDLE_GUI_IDENTIFIER com.lemonfoxmere.PixelAir
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Info.plist"
    WIN32_EXECUTABLE TRUE
)

target_include_directories(PixelAir
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controllers
        ${CMAKE_CURRENT_SOURCE_DIR}/src/models
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/shaders/
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/shaders/gradient
)
target_include_directories(TestAVLTree PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/models)
target_include_directories(TestRasterLayer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/models)

target_link_libraries(PixelAir PRIVATE Qt6::Quick)
target_link_libraries(TestAVLTree PRIVATE Qt6::Quick GTest::GTest GTest::Main Qt6::Test)
target_link_libraries(TestRasterLayer PRIVATE Qt6::Quick GTest::GTest GTest::Main Qt6::Test)

include(GNUInstallDirs)
install(TARGETS PixelAir
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# adding tests
add_test(NAME AVLTreeTests COMMAND TestAVLTree)

# macos native support with cocoa
find_library(COCOA_LIBRARY Cocoa)
if(COCOA_LIBRARY)
    target_link_libraries(PixelAir PRIVATE ${COCOA_LIBRARY}) # link if exists
endif()
