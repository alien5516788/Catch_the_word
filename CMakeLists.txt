# cmake .. -G "MinGW Makefiles"

# configure this ..!
cmake_minimum_required(VERSION 3.26.3)
project("Catch-the-word" CXX)

# MinGW compiler command

# g++ CTW.cpp src/window.cpp src/mainMenu.cpp src/textBoard.cpp -o CTW.exe ^
# -Iheaders -IC:/Others/sfml/SFML-2.5.1/include ^
# -LC:/Others/sfml/SFML-2.5.1/lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio ^
# -std=c++17