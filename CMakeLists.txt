# Minimum required version of cmake
cmake_minimum_required(VERSION 3.26.3)

# Project name
project(ctw CXX)

# Set compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(headers)
include_directories(libs/SFML/include)

# dependancies
add_subdirectory(libs/SFML) # sfml
add_subdirectory(libs/flac) # flac
add_subdirectory(libs/freetype) # freetype

# Target
add_executable(ctw ctw.cpp src/mainMenu.cpp src/textBoard.cpp src/window.cpp)
target_link_libraries(ctw sfml-graphics sfml-main sfml-window sfml-system sfml-audio FLAC freetype)
set_target_properties(ctw PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin)

# Extra folders
#   bin/ , build/ , libs/
