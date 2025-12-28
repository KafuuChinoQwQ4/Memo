cmake_minimum_required(VERSION 3.16)

project(memo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where to find header files
include_directories("header files")

set(CMAKE_INCLUDE_CURRENT_DIR ON)



# Find Qt to determine the version, then find the specific version to load its macros
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_CPP_SOURCES
    "source files/main.cpp"
    "source files/loginwigets.cpp"
    "source files/backgroundanimator.cpp"
    "source files/loginheaderwidget.cpp"
    "source files/topbarwidget.cpp"
    "source files/loginformwidget.cpp"
    "source files/logincontrolwidget.cpp"
)

set(PROJECT_HEADER_SOURCES
    "header files/loginwigets.h"
    "header files/backgroundanimator.h"
    "header files/loginheaderwidget.h"
    "header files/topbarwidget.h"
    "header files/loginformwidget.h"
    "header files/logincontrolwidget.h"
)

set(PROJECT_RESOURCES
    "resources.qrc"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(memo
        MANUAL_FINALIZATION
        ${PROJECT_CPP_SOURCES}
        ${PROJECT_RESOURCES}
    )
else()
    add_executable(memo
        ${PROJECT_CPP_SOURCES}
        ${PROJECT_RESOURCES}
    )
endif()

target_sources(memo PRIVATE ${PROJECT_HEADER_SOURCES})

target_link_libraries(memo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(memo PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS memo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(memo)
endif()
