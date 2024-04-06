#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

// window
extern unsigned int windowHeight;
extern unsigned int windowWidth;

extern short changeWindow;
extern short currentWindow; // 0 - mainmenu, 1 - text board

// change window
void windowTransition();

// game icon
extern sf::Image icon;

// intro music
extern sf::Music introMusic;

#endif
