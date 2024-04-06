#ifndef TEXTBOARD_HPP
#define TEXTBOARD_HPP

#include <cmath>
#include <vector>
#include <fstream>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

// selection menu
extern float selectionMenuHeight;
extern float selectionMenuWidth;

extern sf::Texture selectionMenuTexture;
extern sf::Sprite selectionMenu;

extern sf::Texture selectionMenuTexture;
extern sf::Sprite selectionMenu;

extern sf::Text wordCountText;

extern sf::Texture decWordsTexture;
extern sf::Sprite decWordsButton;

extern sf::Texture incWordsTexture;
extern sf::Sprite incWordsButton;

extern sf::Texture runButtonTexture;
extern sf::Texture pauseButtonTexture;
extern sf::Sprite runPauseButton;

extern sf::Texture restartButtonTexture;
extern sf::Sprite restartButton;

extern bool paused;
extern bool finished;

void decWords();

void incWords();

void runPause();

void restart();

bool isButtonClicked(sf::Sprite& button, int posX, int posY);

void animateButton(sf::Sprite& button, bool reset);

// text board
extern double textBoardHeight;
extern double textBoardWidth;
extern double charactorSize;

extern sf::Texture textBoardTexture;
extern sf::Sprite textBoard;

extern sf::Font font;
extern std::vector<std::string> wordList;
extern int wordCount;
extern int nextWord;

extern std::vector<sf::Text> trainingList;
extern double speed;

void loadWordList();

void addWord(sf::RenderWindow& window);

void highlightWord();

void adjustSpeed();

// scoreboard
extern sf::Texture scoreBoardTexture;
extern sf::Sprite scoreBoard;

extern sf::Text inputText;
extern std::vector<char> inputWord;

extern int catchedWordCount;
extern sf::Text catchedWordText;

void catchWord();

void getInput(int unicode);

extern int missedWordCount;
extern sf::Text missedWordText;

void kickWord();

extern int WPM;
extern sf::Text wpmText;

extern sf::Clock wpmClock;
extern double wpmTime;

void wordsPerMinute();

void updateScore(sf::RenderWindow& window);

void resetScore();

extern sf::Music gameMusic;
extern sf::Music catchMusic;
extern sf::Music missMusic;

#endif