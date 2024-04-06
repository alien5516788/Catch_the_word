#include "textBoard.hpp"

float selectionMenuHeight = 40.0;
float selectionMenuWidth = 1024.0;

sf::Texture selectionMenuTexture;
// sf::Sprite selectionMenu;

// sf::Text wordCountText;

sf::Texture decWordsTexture;
// sf::Sprite decWordsButton;

sf::Texture incWordsTexture;
// sf::Sprite incWordsButton;

sf::Texture runButtonTexture;
sf::Texture pauseButtonTexture;
// sf::Sprite runPauseButton;

sf::Texture restartButtonTexture;
// sf::Sprite restartButton;

bool paused = true;
bool finished = true;

void decWords(){

    if (wordCount <= 25) return;
    else if (wordCount > 100) wordCount -= 100;
    else  wordCount -= 25;
    
    restart();

}

void incWords(){

    if (wordCount >= 1000) return;
    else if (wordCount < 100) wordCount += 25;
    else wordCount += 100;
   
    restart();

}

void runPause(){
    
    // set paused state
    if (paused == true) {

        paused = false;
        runPauseButton.setTexture(pauseButtonTexture);

    }else{

        paused = true;
        runPauseButton.setTexture(runButtonTexture);

    }

}

void restart(){
    
    // pause if not paused
    if (paused == false) runPause();

    finished = true;

    // reset parameters
    loadWordList();
    trainingList.clear();
    nextWord = 0;
    speed = 0.7;

    inputText.setString("");

    gameMusic.play();

}

bool isButtonClicked(sf::Sprite& button, int posX, int posY){

    short buttonX = button.getGlobalBounds().width;
    short buttonX2 = button.getPosition().x - buttonX / 2;

    short buttonY = button.getGlobalBounds().height;
    short buttonY2 = button.getPosition().y - buttonY / 2;
    
    if ((posX <= buttonX2 + buttonX && posX >= buttonX2) 
    && (posY <= buttonY2 + buttonY && posY >= buttonY2)) return true;

    else return false;

}

void animateButton(sf::Sprite& button, bool reset){

    sf::Vector2f buttonPosition(button.getPosition());

    if (reset == true) {

        button.setScale(sf::Vector2f(1, 1));
        button.setPosition(buttonPosition);

    } else {

        button.setScale(sf::Vector2f(0.95, 0.95));
        button.setPosition(buttonPosition);
        
    }

}

// textboard
double textBoardHeight = 540;
double textBoardWidth = 1024;
double charactorSize = 20;

sf::Texture textBoardTexture;
// sf::Sprite textBoard;

sf::Font font;
std::vector<std::string> wordList;
int wordCount = 25;
int nextWord = 0;

std::vector<sf::Text> trainingList;
double speed = 0.7;

void loadWordList(){
    
    // read file
    std::ifstream tempWordList("assets/wordlist/wordlist_common.txt");
    
    // load all the words
    std::vector<std::string> wordL;
    std::string tempW;

    while (tempWordList >> tempW) wordL.push_back(tempW);

    tempWordList.close();

    // shuffle and select words
    wordList.clear();
    
    int wordC = wordL.size();
    int tempWordC = 0;
    
    while (tempWordC < wordCount){

        int randW = rand() % wordC;
        wordList.push_back(wordL[randW]);
        tempWordC++;
        
    }

}

void addWord(sf::RenderWindow& window){

    // draw words
    for (sf::Text& word : trainingList){
        window.draw(word);
    }

    // move words to next line
    if (paused == false) {

        // reset score if game begins
        if (finished == true) {

            resetScore();
            finished = false;

        }
        
        // move words
        for (sf::Text& word : trainingList){
            word.move(sf::Vector2f(0, speed));
        }
   
    }
    
    // return if word list ends
    if (nextWord == wordCount){
        
        if (trainingList.size() == 0) restart();
        return;

    }

    // add a new word
    short trainingListSize = trainingList.size();
    
    if ((trainingListSize == 0 || trainingList[trainingListSize - 1].getPosition().y >= 80)){

        // sf::Text word;
        // word.setFont(font);
        sf::Text word(font);
        word.setString(wordList[nextWord]);
        word.setCharacterSize(charactorSize);

        int randPosX = std::rand() % (1024 - (word.getString().getSize() * 20));
        word.setPosition(sf::Vector2f(randPosX, 0));

        trainingList.push_back(word);
        nextWord++;
    
    }

}

void highlightWord(){
    
    // return if training list is empty
    if (trainingList.size() == 0) return;
    
    // hightlight words
    double offSet;

    for (sf::Text& word : trainingList){
        
        offSet = word.getPosition().y;
        
        // apply orrange to vulnerable words
        if (offSet >= (textBoardHeight * 2) / 3) word.setFillColor(sf::Color(255, 165, 0));
        // apply red to most vulnerable words
        if (offSet >= (textBoardHeight * 5) / 6) word.setFillColor(sf::Color::Red);

    }
    
    // apply yellow to the word to catch
    trainingList[0].setFillColor(sf::Color::Yellow);

}

void adjustSpeed(){
    
    speed = (2 / (1 + log10(trainingList.size()))) - 0.3;

}

// scoreboard
sf::Texture scoreBoardTexture;
// sf::Sprite scoreBoard;

std::vector<char> inputWord;
// sf::Text inputText;

int catchedWordCount = 0;
// sf::Text catchedWordText;

void catchWord(){
    
    // return if training list is empty
    if (trainingList.size() == 0 || paused == true) return;
    
    // update score
    if (inputText.getString() == trainingList[0].getString()) {

        catchedWordCount++;

        catchMusic.openFromFile("assets/music/catch.wav");
        catchMusic.play();

    }else{

        missedWordCount++;

        missMusic.openFromFile("assets/music/miss.wav");
        missMusic.play();

    } 
    
    // remove catched or incorrect word
    trainingList.erase(trainingList.begin());
    inputWord.clear();
    inputText.setString("");

}

void getInput(int unicode){
    
    // prevent input shile paused
    if (paused == true) return;
    
    // get character
    char inputChar;
    inputChar = static_cast<char>(unicode);

    std::string text;
    
    // type space to catch
    if (inputChar == ' ' && inputWord.size() > 0) {
        
        catchWord();
        return;
    
    // regular and special characters
    }else if (32 < unicode && unicode < 127) inputWord.push_back(inputChar);
    
    // backspace
    else if (inputChar == '\b' && inputWord.size() > 0) inputWord.pop_back();
    
    // update word
    for (char chr: inputWord){
        text += chr;
    }
    
    // return if character length exceeds
    if (text.size() > 16) return;
    
    // set text and warn
    inputText.setString(text);
    if (text != trainingList[0].getString().substring(0, text.size())) inputText.setFillColor(sf::Color::Red);
    else inputText.setFillColor(sf::Color::Black);

}

int missedWordCount = 0;
// sf::Text missedWordText;

void kickWord(){
       
    // return if training list is empty
    if (trainingList.size() == 0) return;
    
    // remove missed word
    sf::Text word = trainingList[0];

    if (word.getPosition().y >= 570){

        trainingList.erase(trainingList.begin());
        missedWordCount++;

        missMusic.openFromFile("assets/music/miss.wav");
        missMusic.play();

    }

}

int WPM = 0;
// sf::Text wpmText;

sf::Clock wpmClock;
double wpmTime = 0;

void wordsPerMinute(){

    if (finished == false && paused == false) wpmTime += wpmClock.getElapsedTime().asSeconds();
    else if (finished == true) wpmTime = 0;

    if (wpmTime > 0) WPM = ceil(catchedWordCount * 60 / wpmTime);

    wpmClock.restart();

}

void updateScore(sf::RenderWindow& window){

    std::string score;

    score = std::to_string(catchedWordCount);
    catchedWordText.setString(score);

    score = std::to_string(missedWordCount);
    missedWordText.setString(score);

    score = std::to_string(WPM);
    wpmText.setString(score);

    window.draw(catchedWordText);
    window.draw(missedWordText);
    window.draw(wpmText);

}

void resetScore(){

    catchedWordCount = 0;
    missedWordCount = 0;
    WPM = 0;

}

sf::Music gameMusic;
sf::Music catchMusic;
sf::Music missMusic;