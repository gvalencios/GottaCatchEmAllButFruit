#ifndef PLAY_H
#define PLAY_H

#include <iostream>
#include <vector>
#include <string>
// for kbhit()
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


struct Fruit {
    int Xpos, Ypos, Size; //position and size of the fruit
    void Move();
    void init(int Mapsize_x, int Mapsize_y);
};

struct Basket {
    int Xpos, Ypos; //position of the player
    int HP;// the player's health
    int Score = -1; // the player's score
    void Move(int Mapsize_x, int Mapsize_y);//function that detect keypress and move the player
    void init(int Mapsize_x, int Mapsize_y);
};

struct Event {
    // member variables
    bool EndGame;
    int MapSize_x, MapSize_y;
    int tmp, count, intervalDrop; //to delay the drop and add difficulty
    char Map[105][105];
    std::string ch;
    Basket player;
    std::vector<Fruit> fruities;
    
    // member functions
    void initMap();
    void initVariables();
    void startingNewGame();
    bool isRunning();
    
    //updating Map and other variable functions
    void detectCatchedFruits();
    void detectDroppedFruits();
    void refreshMap(); 
    void refreshPlayerStatus();
    void refreshFruitStatus();
    // a combination of refresh map, player, and fruit status is further evoke with the "update" function below
    void update();  
    
    // printing UI and Map functions
    void printUI(); 
    void printMap(); 
    // a combination of print UI and Map is further evoke with the "print" function below
    void print();
    
    // printing and storing score to the scoreboard
    void printScoreboard();
    void storeScoreboard();
    void instructions();
    
};
int kbhit();

#endif
