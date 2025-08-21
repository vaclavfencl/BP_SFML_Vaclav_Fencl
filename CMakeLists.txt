cmake_minimum_required(VERSION 3.20)
project(BP_SFML_Vaclav_Fencl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-3.0.0/lib/cmake/SFML")
list(PREPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/SFML-3.0.0")

find_package(SFML 3.0.0 REQUIRED COMPONENTS Graphics Window System Audio)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
  add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "${CMAKE_BINARY_DIR}/bin/assets"
    BYPRODUCTS "${CMAKE_BINARY_DIR}/bin/assets"
    COMMENT "Copying assets -> build/bin/assets")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(APP1)
add_subdirectory(APP2)

if(TARGET copy_assets)
  add_dependencies(APP1 copy_assets)
  add_dependencies(APP2 copy_assets)
endif()