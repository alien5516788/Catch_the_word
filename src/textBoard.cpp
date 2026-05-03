#include "textBoard.hpp"

unsigned int selectionMenuHeight = 40;
unsigned int selectionMenuWidth = 1024;

sf::Texture selectionMenuTexture;

sf::Texture decWordsTexture;

sf::Texture incWordsTexture;

sf::Texture runButtonTexture;
sf::Texture pauseButtonTexture;

sf::Texture restartButtonTexture;

bool paused = true;
bool finished = true;

void decWords(sf::Text& inputText, sf::Sprite& runPauseButton){
    
    // if word count is less than 25, do nothing
    if (wordCount <= 25) return;
    // if word count is greater than 100, decrease by 100
    else if (wordCount > 100) wordCount -= 100;
    // if word count is between 25 and 100, decrease by 25
    else  wordCount -= 25;
    
    restart(inputText, runPauseButton);

}

void incWords(sf::Text& inputText, sf::Sprite& runPauseButton){
    
    // if word count is greater than 1000, do nothing
    if (wordCount >= 1000) return;
    // if word count is less than 100, increase by 25
    else if (wordCount < 100) wordCount += 25;
    // if word count is between 100 and 1000, increase by 100
    else wordCount += 100;
   
    restart(inputText, runPauseButton);

}

void runPause(sf::Sprite& runPauseButton){
    
    // run or pause
    // Button texture is changed
    if (paused == true) {

        paused = false;
        runPauseButton.setTexture(pauseButtonTexture);

    }else{

        paused = true;
        runPauseButton.setTexture(runButtonTexture);

    }

}

void restart(sf::Text& inputText, sf::Sprite& runPauseButton){
    
    // pause if not paused
    if (paused == false) runPause(runPauseButton);
    
    // set finished status
    finished = true;

    // reset data
    loadWordList();
    trainingList.clear();
    nextWord = 0;
    speed = 0.7;
    
    // clear input
    inputText.setString("");
    
    // restart game music
    gameMusic.play();

}

bool isButtonClicked(sf::Sprite& button, int posX, int posY){
    
    // get click positions
    short buttonX = button.getGlobalBounds().width;
    short buttonX2 = button.getPosition().x - buttonX / 2;

    short buttonY = button.getGlobalBounds().height;
    short buttonY2 = button.getPosition().y - buttonY / 2;
    
    // check if clck position is a button
    if ((posX <= buttonX2 + buttonX && posX >= buttonX2) 
    && (posY <= buttonY2 + buttonY && posY >= buttonY2)) return true;

    else return false;

}

void animateButton(sf::Sprite& button, bool reset){
    
    // check for button clicks
    sf::Vector2f buttonPosition(button.getPosition());
    
    // animate buttons
    if (reset == true) {

        button.setScale(sf::Vector2f(1, 1));
        button.setPosition(buttonPosition);

    } else {

        button.setScale(sf::Vector2f(0.95, 0.95));
        button.setPosition(buttonPosition);
        
    }

}

double textBoardHeight = 540;
double textBoardWidth = 1024;
double charactorSize = 20;

sf::Texture textBoardTexture;

sf::Font font;
std::vector<std::string> wordList;
int wordCount = 25;
int nextWord = 0;

std::vector<sf::Text> trainingList;
double speed = 0.7;

void loadWordList(){
    
    // read word file
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

void addWord(sf::RenderWindow& window, sf::Text& inputText, sf::Sprite& runPauseButton){

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
        
        if (trainingList.size() == 0) restart(inputText, runPauseButton);
        return;

    }

    // add a new word
    short trainingListSize = trainingList.size();
    
    // check position before adding word
    // last word must be in a reasonable distance from the top
    if ((trainingListSize == 0 || trainingList[trainingListSize - 1].getPosition().y >= 80)){

        // sf::Text word;
        // word.setFont(font);
        sf::Text word;
        word.setFont(font);
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
    
    // adjust word flow speed according to the typing speed
    // I don't know a sh*t about this
    speed = (2 / (1 + log10(trainingList.size()))) - 0.3;

}

sf::Texture scoreBoardTexture;

std::vector<char> inputWord;

int catchedWordCount = 0;

void catchWord(sf::Text& inputText){
    
    // return if training list is empty
    if (trainingList.size() == 0 || paused == true) return;
 
    // update score
    if (inputText.getString() == trainingList[0].getString()) {

        catchedWordCount++;
        
        // play catching sound
        if (!catchMusic.openFromFile("assets/musics/catch.wav")){
            std::cout << "Failed to load catch sound" << std::endl;
        }
        catchMusic.play();

    }else{

        missedWordCount++;
        
        // play missing sound
        if (!missMusic.openFromFile("assets/musics/miss.wav")){
            std::cout << "Failed to load miss sound" << std::endl;
        }
        missMusic.play();

    } 
    
    // remove catched or incorrect word
    trainingList.erase(trainingList.begin());
    inputWord.clear();
    inputText.setString("");

}

void getInput(int unicode, sf::Text& inputText){

    // prevent input while paused
    if (paused == true) return;
    
    // get character
    char inputChar;
    inputChar = static_cast<char> (unicode);

    std::string text;

    // type space to catch
    // catch the word if space is entered
    // empty words are ignored
    if (inputChar == ' ' && inputWord.size() > 0) {

        for (char chr: inputWord){
            text += chr;
        }

        inputText.setString(text);
        catchWord(inputText);
        return;
    
    // regular and special characters
    }else if (32 < unicode && unicode < 127) inputWord.push_back(inputChar);
    
    // backspace remove last character
    else if (inputChar == '\b' && inputWord.size() > 0) inputWord.pop_back();
    
    // update word
    for (char chr: inputWord){
        text += chr;
    }

    // return if character length exceeds
    // prevent user from inputing unnecessary amount of characters
    if (text.size() > 16) return;
    
    // set text and warn
    // warn about mistakes
    inputText.setString(text);
    if (text != trainingList[0].getString().substring(0, text.size())) inputText.setFillColor(sf::Color::Red);
    else inputText.setFillColor(sf::Color::Black);

}

int missedWordCount = 0;

void kickWord(){
       
    // return if training list is empty
    if (trainingList.size() == 0) return;
    
    // remove missed word
    sf::Text word = trainingList[0];
    
    // check for missed words
    if (word.getPosition().y >= 570){

        trainingList.erase(trainingList.begin());
        missedWordCount++;
        
        // play missed music
        if (!missMusic.openFromFile("assets/musics/miss.wav")){
            std::cout << "Failed to load miss sound" << std::endl;
        }
        missMusic.play();

    }

}

int WPM = 0;

sf::Clock wpmClock;
double wpmTime = 0;

void wordsPerMinute(){
    
    // wpm clock is not running if the game is paused or finished
    if (finished == false && paused == false) wpmTime += wpmClock.getElapsedTime().asSeconds();
    else if (finished == true) wpmTime = 0;

    // calculate wpm
    if (wpmTime > 0) WPM = ceil(catchedWordCount * 60 / wpmTime);

    wpmClock.restart();

}

void updateScore(sf::RenderWindow& window, sf::Text& catchedWordText, 
sf::Text& missedWordText, sf::Text& wpmText){
    
    // draw scores
    // catched, missed, wpm
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
    
    // reset scores to original
    // catched, missed, wpm
    catchedWordCount = 0;
    missedWordCount = 0;
    WPM = 0;

}

sf::Music gameMusic;
sf::Music catchMusic;
sf::Music missMusic;
