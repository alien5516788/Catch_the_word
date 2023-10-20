#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

extern float windowHeight;
extern float windowWidth;

extern short changeWindow;
extern short currentWindow; // 0 - mainmenu, 1 - text board

void windowTransition();

// game icon
extern sf::Image icon;

// intro music
extern sf::Music introMusic;

#endif