#ifndef TEXTBOARD_HPP
#define TEXTBOARD_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

// selection menu
extern unsigned int selectionMenuHeight;
extern unsigned int selectionMenuWidth;

extern sf::Texture selectionMenuTexture;

extern sf::Texture decWordsTexture;

extern sf::Texture incWordsTexture;

extern sf::Texture runButtonTexture;
extern sf::Texture pauseButtonTexture;

extern sf::Texture restartButtonTexture;

// player status
// these are periodically checked
extern bool paused;
extern bool finished;

// decrease word count in play
void decWords(sf::Text& inputText, sf::Sprite& runPauseButton);

// increase word count in play
void incWords(sf::Text& inputText, sf::Sprite& runPauseButton);

// run or pause
void runPause(sf::Sprite& runPauseButton);

// restart game
void restart(sf::Text& inputText, sf::Sprite& runPauseButton);

// check if a menu button is clicked
bool isButtonClicked(sf::Sprite& button, int posX, int posY);

// animate the clcked button
void animateButton(sf::Sprite& button, bool reset);

// text board
extern double textBoardHeight;
extern double textBoardWidth;
extern double charactorSize;

extern sf::Texture textBoardTexture;

extern sf::Font font;
extern std::vector<std::string> wordList;
extern int wordCount;
extern int nextWord;

extern std::vector<sf::Text> trainingList;
extern double speed;

// load the words accordng to the preference
void loadWordList();

// add new words to play
void addWord(sf::RenderWindow& window, sf::Text& inputText, sf::Sprite& runPauseButton);

// show warning level
void highlightWord();

// adjust word flow speed according to the typing speed
void adjustSpeed();

// scoreboard
extern sf::Texture scoreBoardTexture;

extern std::vector<char> inputWord;

extern int catchedWordCount;

// catch correct word
void catchWord(sf::Text& inputText);

// get input from player
void getInput(int unicode, sf::Text& inputText);

// missed words
extern int missedWordCount;

// remove missed words
void kickWord();

// words per minute
extern int WPM;

// counter for wpm
extern sf::Clock wpmClock;
extern double wpmTime;

// calculate wpm
void wordsPerMinute();

// update scores
void updateScore(sf::RenderWindow& window, sf::Text& catchedWordText, 
sf::Text& missedWordText, sf::Text& wpmText);

// reset score back
void resetScore();

// in game msuics
extern sf::Music gameMusic;
extern sf::Music catchMusic;
extern sf::Music missMusic;

#endif
