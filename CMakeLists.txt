# Minimum required version of cmake
cmake_minimum_required(VERSION 3.26.3)

# Project name
project(ctw CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(headers)
include_directories(libs/SFML/include)

# SFML path
add_subdirectory(libs/SFML)

# Target
add_executable(ctw ctw.cpp src/mainMenu.cpp src/textBoard.cpp src/window.cpp)
target_link_libraries(ctw sfml-graphics sfml-window sfml-system)
set_target_properties(ctw PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin)

# SFML root folder path: libs/SFML
# build path: build , bin path: bin