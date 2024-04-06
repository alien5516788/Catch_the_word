#include <iostream>

#include "window.hpp"
#include "mainMenu.hpp"
#include "textBoard.hpp"

int main(){

    // window
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Catch the word", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    icon.loadFromFile("assets/images/icon.ico");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // main menu
    mainMenuBackground.loadFromFile("assets/images/main_menu.jpg");
    mainMenu.setTexture(&mainMenuBackground);
    mainMenu.setSize(sf::Vector2f(mainMenuWidth, mainMenuHeight));

    titleTexture.loadFromFile("assets/images/title.png");
    title.setTexture(titleTexture);
    title.setOrigin(sf::Vector2f(500, 150));
    title.setPosition(sf::Vector2f(512, 250));
    
    playButtonTexture.loadFromFile("assets/images/play_button.png");
    playButton.setPosition(sf::Vector2f(512, 450));
    playButton.setOrigin(sf::Vector2f(200, 50));
    playButton.setTexture(playButtonTexture);

    // text board
    selectionMenuTexture.loadFromFile("assets/images/selection_menu.png");
    selectionMenu.setTexture(selectionMenuTexture);

    wordCountText.setCharacterSize(25);
    wordCountText.setFont(font);
    wordCountText.setFillColor(sf::Color::White);
    wordCountText.setPosition(sf::Vector2f(140, 6));

    decWordsTexture.loadFromFile("assets/images/dec_words.png");
    decWordsButton.setTexture(decWordsTexture);
    decWordsButton.setOrigin(sf::Vector2f(25, 18));
    decWordsButton.setPosition(sf::Vector2f(260, 20));
    
    incWordsTexture.loadFromFile("assets/images/inc_words.png");
    incWordsButton.setTexture(incWordsTexture);
    incWordsButton.setOrigin(sf::Vector2f(25, 18));
    incWordsButton.setPosition(sf::Vector2f(320, 20));
    
    runButtonTexture.loadFromFile("assets/images/run_button.png");
    pauseButtonTexture.loadFromFile("assets/images/pause_button.png");
    runPauseButton.setTexture(runButtonTexture);
    runPauseButton.setOrigin(sf::Vector2f(25, 18));
    runPauseButton.setPosition(sf::Vector2f(904, 20));

    restartButtonTexture.loadFromFile("assets/images/restart_button.png");
    restartButton.setTexture(restartButtonTexture);
    restartButton.setOrigin(sf::Vector2f(25, 18));
    restartButton.setPosition(sf::Vector2f(964, 20));
    
    textBoardTexture.loadFromFile("assets/images/text_board.jpg");
    textBoard.setTexture(textBoardTexture);
    font.loadFromFile("assets/fonts/OpenSans-Regular.ttf");

    srand(time(0));
    loadWordList();

    scoreBoardTexture.loadFromFile("assets/images/score_board.png");
    scoreBoard.setTexture(scoreBoardTexture);
    scoreBoard.setPosition(sf::Vector2f(0, selectionMenuHeight + textBoardHeight));

    inputText.setCharacterSize(30);
    inputText.setFont(font);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(sf::Vector2f(30, 590));

    catchedWordText.setCharacterSize(20);
    catchedWordText.setFont(font);
    catchedWordText.setFillColor(sf::Color::White);
    catchedWordText.setPosition(sf::Vector2f(560, 600));

    missedWordText.setCharacterSize(20);
    missedWordText.setFont(font);
    missedWordText.setFillColor(sf::Color::White);
    missedWordText.setPosition(sf::Vector2f(760, 600));

    wpmText.setCharacterSize(20);
    wpmText.setFont(font);
    wpmText.setFillColor(sf::Color::White);
    wpmText.setPosition(sf::Vector2f(935, 600));
    
    // game loop
    while (window.isOpen()){

        // event loop
        sf::Event event;

        while(window.pollEvent(event)){

            if (currentWindow == 0){

                if (event.type == sf::Event::KeyPressed){
                    
                        if (event.key.code == sf::Keyboard::Enter) animateButton(playButton, false);
                        else if (event.key.code == sf::Keyboard::Escape) window.close();
                      
                }else if (event.type == sf::Event::KeyReleased){

                    if (event.key.code == sf::Keyboard::Enter) {
                        animateButton(playButton, true);
                        changeWindow = 1;
                    }

                }else if (event.type == sf::Event::MouseButtonPressed){

                    int posX =  event.mouseButton.x;
                    int posY =  event.mouseButton.y;

                    if (isButtonClicked(playButton, posX, posY)) animateButton(playButton, false);
            
                }else if (event.type == sf::Event::MouseButtonReleased){

                    int posX =  event.mouseButton.x;
                    int posY =  event.mouseButton.y;

                    if (isButtonClicked(playButton, posX, posY)) {
                        animateButton(playButton, true);
                        changeWindow = 1;
                    }

                }
                
            }else if(currentWindow == 1){

                if (event.type == sf::Event::TextEntered) getInput(event.text.unicode);

                if (event.type == sf::Event::KeyPressed){

                    if (event.key.code == sf::Keyboard::Escape){

                        restart();
                        resetScore();
                        currentWindow = 0;

                    } else if (event.key.code == sf::Keyboard::Enter) animateButton(runPauseButton, false);
                       
                }else if(event.type == sf::Event::KeyReleased){

                    if (event.key.code == sf::Keyboard::Enter) {

                        animateButton(runPauseButton, true);
                        runPause();

                    }
                      
                }else if (event.type == sf::Event::MouseButtonPressed){

                    int posX =  event.mouseButton.x;
                    int posY =  event.mouseButton.y;

                    if (isButtonClicked(decWordsButton, posX, posY)) animateButton(decWordsButton, false);
                    else if (isButtonClicked(incWordsButton, posX, posY)) animateButton(incWordsButton, false);
                    else if (isButtonClicked(runPauseButton, posX, posY)) animateButton(runPauseButton, false);
                    else if (isButtonClicked(restartButton, posX, posY))animateButton(restartButton, false);

                }else if (event.type == sf::Event::MouseButtonReleased){

                    int posX =  event.mouseButton.x;
                    int posY =  event.mouseButton.y;

                    if (isButtonClicked(decWordsButton, posX, posY)) {
                        animateButton(decWordsButton, true);
                        decWords();
                    }else if (isButtonClicked(incWordsButton, posX, posY)){
                        animateButton(incWordsButton, true);
                        incWords();
                    }else if (isButtonClicked(runPauseButton, posX, posY)){
                        animateButton(runPauseButton, true);
                        runPause();
                    }else if (isButtonClicked(restartButton, posX, posY)){
                        animateButton(restartButton, true);
                        restart();
                    }

                }

            }

            if (event.type == sf::Event::Closed) window.close();
            
        };

        // draw entites
        window.clear();
        
        if (currentWindow == 0){
        
            if (introMusic.getStatus() != sf::Music::Playing) {
                introMusic.openFromFile("assets/music/intro.wav");
                introMusic.play();
            }
            if (gameMusic.getStatus() == sf::Music::Playing) gameMusic.stop();

            window.draw(mainMenu);
            window.draw(title);
            window.draw(playButton);
           
        }else if (currentWindow == 1){

            if (gameMusic.getStatus() != sf::Music::Playing) {
                gameMusic.openFromFile("assets/music/game.wav");
                gameMusic.play();
            }
            if (introMusic.getStatus() == sf::Music::Playing) introMusic.stop();

            window.draw(textBoard);
            
            addWord(window);
            kickWord();
            highlightWord();
            wordsPerMinute();
            adjustSpeed();

            window.draw(selectionMenu);
            wordCountText.setString(std::to_string(wordCount));
            window.draw(wordCountText);
            window.draw(decWordsButton);
            window.draw(incWordsButton);
            window.draw(runPauseButton);
            window.draw(restartButton);

            window.draw(scoreBoard);
            window.draw(inputText);
            updateScore(window);
            
        };
        
        window.display();

        windowTransition();

    }
    
    return 0;
    
}