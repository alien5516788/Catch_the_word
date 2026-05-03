#include <iostream>

#include "window.hpp"
#include "mainMenu.hpp"
#include "textBoard.hpp"

int main(){

    // window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Catch the word", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    if (!icon.loadFromFile("assets/images/icon.ico")) {
        std::cout << "Failed to load icon" << std::endl;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // main menu

    // main menu backgound
    if (!mainMenuBackground.loadFromFile("assets/images/main_menu.jpg")) {
        std::cout << "Failed to load main menu background" << std::endl; 
    }
    mainMenu.setTexture(&mainMenuBackground);
    mainMenu.setSize(sf::Vector2f(mainMenuWidth, mainMenuHeight));

    // title
    if (!titleTexture.loadFromFile("assets/images/title.png")){
        std::cout << "Failed to load title" << std::endl; 
    } 
    sf::Sprite title(titleTexture);
    title.setOrigin(sf::Vector2f(500, 150));
    title.setPosition(sf::Vector2f(512, 250));
    
    // play button
    if (!playButtonTexture.loadFromFile("assets/images/play_button.png")){
        std::cout << "Failed to load play button" << std::endl;
    }
    sf::Sprite playButton(playButtonTexture);
    playButton.setPosition(sf::Vector2f(512, 450));
    playButton.setOrigin(sf::Vector2f(200, 50));
    
    // text board

    // textboard menu
    if (!selectionMenuTexture.loadFromFile("assets/images/selection_menu.png")){
        std::cout << "Failed to load selection menu" << std::endl;
    }
    sf::Sprite selectionMenu(selectionMenuTexture);
    
    // word count
    sf::Text wordCountText;
    wordCountText.setFont(font);
    wordCountText.setCharacterSize(25);
    wordCountText.setFillColor(sf::Color::White);
    wordCountText.setPosition(sf::Vector2f(140, 6));
    
    // decrease words button
    if (!decWordsTexture.loadFromFile("assets/images/dec_words.png")){
        std::cout << "Failed to load dec words button" << std::endl;
    }
    sf::Sprite decWordsButton(decWordsTexture);
    decWordsButton.setOrigin(sf::Vector2f(25, 18));
    decWordsButton.setPosition(sf::Vector2f(260, 20));
    
    // increase word count button
    if (!incWordsTexture.loadFromFile("assets/images/inc_words.png")){
        std::cout << "Failed to load inc words button" << std::endl;
    }
    sf::Sprite incWordsButton(incWordsTexture);
    incWordsButton.setOrigin(sf::Vector2f(25, 18));
    incWordsButton.setPosition(sf::Vector2f(320, 20));
    
    // run pause button
    if (!runButtonTexture.loadFromFile("assets/images/run_button.png") || 
        !pauseButtonTexture.loadFromFile("assets/images/pause_button.png")){
        std::cout << "Failed to load run-pause button" << std::endl;
    }
    sf::Sprite runPauseButton(runButtonTexture);
    runPauseButton.setOrigin(sf::Vector2f(25, 18));
    runPauseButton.setPosition(sf::Vector2f(904, 20));
    
    // restart button
    if (!restartButtonTexture.loadFromFile("assets/images/restart_button.png")){
        std::cout << "Failed to load restart button" << std::endl;
    }
    sf::Sprite restartButton(restartButtonTexture);
    restartButton.setOrigin(sf::Vector2f(25, 18));
    restartButton.setPosition(sf::Vector2f(964, 20));
    
    // textboard // this is where the words are shown
    if (!textBoardTexture.loadFromFile("assets/images/text_board.jpg")){
        std::cout << "Failed to load text board" << std::endl;
    }
    sf::Sprite textBoard(textBoardTexture);
    
    // load font and word list
    if (!font.loadFromFile("assets/fonts/OpenSans-Regular.ttf")){
        std::cout << "Failed to load font" << std::endl;
    }
    srand(time(0));
    loadWordList();
    
    // score board
    
    // score baord menu
    if (!scoreBoardTexture.loadFromFile("assets/images/score_board.png")){
        std::cout << "Failed to load score board" << std::endl;
    }
    sf::Sprite scoreBoard(scoreBoardTexture);
    scoreBoard.setPosition(sf::Vector2f(0, selectionMenuHeight + textBoardHeight));
    
    // input text from the player
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(sf::Vector2f(30, 590));
    
    // catched words count
    sf::Text catchedWordText;
    catchedWordText.setFont(font);
    catchedWordText.setCharacterSize(20);
    catchedWordText.setFillColor(sf::Color::White);
    catchedWordText.setPosition(sf::Vector2f(560, 600));

    // missed words count
    sf::Text missedWordText;
    missedWordText.setFont(font);
    missedWordText.setCharacterSize(20);
    missedWordText.setFillColor(sf::Color::White);
    missedWordText.setPosition(sf::Vector2f(760, 600));
    
    // words per minute
    sf::Text wpmText;
    wpmText.setFont(font);
    wpmText.setCharacterSize(20);
    wpmText.setFillColor(sf::Color::White);
    wpmText.setPosition(sf::Vector2f(935, 600));
    
    // game loop
    while (window.isOpen()){

        // event loop
        sf::Event event;

        while(window.pollEvent(event)){
            
            // main menu
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
            
            // text baord
            }else if(currentWindow == 1){

                if (event.type == sf::Event::TextEntered) getInput(event.text.unicode, inputText);

                if (event.type == sf::Event::KeyPressed){

                    if (event.key.code == sf::Keyboard::Escape){

                        restart(inputText, runPauseButton);
                        resetScore();
                        currentWindow = 0;

                    } else if (event.key.code == sf::Keyboard::Enter) animateButton(runPauseButton, false);
                       
                }else if(event.type == sf::Event::KeyReleased){

                    if (event.key.code == sf::Keyboard::Enter) {

                        animateButton(runPauseButton, true);
                        runPause(runPauseButton);

                    }
                      
                }else if (event.type == sf::Event::MouseButtonPressed){

                    int posX =  event.mouseButton.x;
                    int posY =  event.mouseButton.y;

                    if (isButtonClicked(decWordsButton, posX, posY)) animateButton(decWordsButton, false);
                    else if (isButtonClicked(incWordsButton, posX, posY)) animateButton(incWordsButton, false);
                    else if (isButtonClicked(runPauseButton, posX, posY)) animateButton(runPauseButton, false);
                    else if (isButtonClicked(restartButton, posX, posY)) animateButton(restartButton, false);

                }else if (event.type == sf::Event::MouseButtonReleased){

                    int posX =  event.mouseButton.x;
                    int posY =  event.mouseButton.y;

                    if (isButtonClicked(decWordsButton, posX, posY)) {
                        animateButton(decWordsButton, true);
                        decWords(inputText, runPauseButton);
                    }else if (isButtonClicked(incWordsButton, posX, posY)){
                        animateButton(incWordsButton, true);
                        incWords(inputText, runPauseButton);
                    }else if (isButtonClicked(runPauseButton, posX, posY)){
                        animateButton(runPauseButton, true);
                        runPause(runPauseButton);
                    }else if (isButtonClicked(restartButton, posX, posY)){
                        animateButton(restartButton, true);
                        restart(inputText, runPauseButton);
                    }

                }

            }

            if (event.type == sf::Event::Closed) window.close();
            
        }

        // draw entites
        window.clear();
        
        if (currentWindow == 0){
            
            // play mainmenu music
            if (introMusic.getStatus() != sf::Music::Playing) {
                if (!introMusic.openFromFile("assets/musics/intro.wav")){
                    std::cout<< "Failed to load intro music" << std::endl;
                }
                introMusic.play();
            }
            if (gameMusic.getStatus() == sf::Music::Playing) gameMusic.stop();
            
            window.draw(mainMenu);
            window.draw(title);
            window.draw(playButton);
           
        }else if (currentWindow == 1){
            
            // play game music
            if (gameMusic.getStatus() != sf::Music::Playing) {
                if (!gameMusic.openFromFile("assets/musics/game.wav")){
                    std::cout<< "Failed to load game music" << std::endl;
                }
                gameMusic.play();
            }
            if (introMusic.getStatus() == sf::Music::Playing) introMusic.stop();

            window.draw(textBoard);
            
            // take textboard actions
            addWord(window, inputText, runPauseButton);
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
            updateScore(window, catchedWordText, missedWordText, wpmText);
            
        }
        
        window.display();
        
        // check is window change is set
        windowTransition();

    }
    
    return 0;
    
}
