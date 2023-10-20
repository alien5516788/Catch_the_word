#include "window.hpp"

float windowHeight = 640;
float windowWidth = 1024;

short changeWindow = false;
short currentWindow = 0;

void windowTransition(){

    if (changeWindow != false){
    
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