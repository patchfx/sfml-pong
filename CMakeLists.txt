# General settings
cmake_minimum_required(VERSION 2.8.4)
set(PROJECT_NAME Pong)
project(${PROJECT_NAME})

# Enable debug symbols by default
if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Define sources and executable
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(SOURCE_FILES main.cpp game.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Detect and add SFML
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH "/Users/richard/SFML-2.2-osx-clang-universal/cmake/Modules" ${CMAKE_MODULE_PATH})
set(SFML_ROOT "/Users/richard/SFML-2.2-osx-clang-universal/" CACHE FILEPATH "Path to SFML library.")
set(SFML_STATIC_LIBRARIES OFF)
find_package(SFML 2 REQUIRED graphics window network audio system)
if (SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_DEPENDENCIES})
else()
    message(SEND_ERROR "SFML library not found. Please set SFML_ROOT.")
endif()
 