# cmake ..

cmake_minimum_required(VERSION 3.4)
project(bfelf_loader C CXX)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/bfprefix" CACHE PATH "default bareflank prefix" FORCE)
endif()

include("${CMAKE_INSTALL_PREFIX}/cmake/CMakeGlobal_Project.txt")

# ------------------------------------------------------------------------------
# Subdirectories
# ------------------------------------------------------------------------------

add_subdirectory(tests)

# ------------------------------------------------------------------------------
# Install
# ------------------------------------------------------------------------------

install(FILES include/bfelf_loader.h DESTINATION include)
