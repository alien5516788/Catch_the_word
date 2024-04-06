#include "window.hpp"

unsigned int windowHeight = 640;
unsigned int windowWidth = 1024;

short changeWindow = false;
short currentWindow = 0;

void windowTransition(){
    
    // periodically check if window is set to change
    if (changeWindow != false){
        
        // keep a delay between transition
        // This gives time to see the button animation
        sf::Clock clock;
        short dt;

        do { dt = clock.getElapsedTime().asMilliseconds(); }
        while (dt < 50);

        currentWindow = changeWindow;
        changeWindow = false;

    }

}

sf::Image icon;

sf::Music introMusic;
