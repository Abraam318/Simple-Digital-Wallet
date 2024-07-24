cmake_minimum_required(VERSION 3.5)

project(finalds VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Files.cpp
    Files.h
    DigitalWallet.cpp
    DigitalWallet.h
    image.qrc
    # Remove finalds_en_GB.ts if not needed
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(finalds
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    # Remove if not needed
    # qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} finalds_en_GB.ts)
else()
    if(ANDROID)
        add_library(finalds SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(finalds
            ${PROJECT_SOURCES}
        )
    endif()
    # Remove if not needed
    # qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} finalds_en_GB.ts)
endif()

target_link_libraries(finalds PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION_MAJOR} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.finalds)
endif()
set_target_properties(finalds PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS finalds
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(finalds)
endif()
