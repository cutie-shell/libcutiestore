cmake_minimum_required(VERSION 3.16)
project(cutiestore VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

set(lib_SOURCES
    src/cutiestore.cpp src/cutiestore.h)

qt6_add_library(cutiestore
    SHARED ${lib_SOURCES}
)

set_target_properties(cutiestore PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(cutiestore PROPERTIES SOVERSION 0)
set_target_properties(cutiestore PROPERTIES PUBLIC_HEADER src/cutiestore.h)

target_link_libraries(cutiestore PUBLIC
    Qt::Core
)

configure_file(src/cutiestore.pc.in cutiestore.pc @ONLY)

install(TARGETS cutiestore
    RUNTIME DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    BUNDLE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(FILES ${CMAKE_BINARY_DIR}/cutiestore.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
