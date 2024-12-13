cmake_minimum_required(VERSION 3.5)

project(versionmap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(versionmap main.cpp
    interval_map.h
)

include(GNUInstallDirs)
install(TARGETS versionmap
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
