#include "play.h"
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int kbhit()
{
	struct termios oldt, newt;
	int KeyPressed;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	KeyPressed = getchar();
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(KeyPressed != EOF)
	{
		ungetc(KeyPressed, stdin);
		return 1;
	}

	return 0;
}

void Fruit::Move()
{
 	// increment the Ypos in order to make the fruits "fall"
	Ypos += 1;
	// Xpos doesn't change as we don't alter the horizontal position of the furits
    Xpos += 0;
}

void Fruit::init(int MapY_length,int MapX_length)
{
	// always intialize fruits from Ypos = 0 which is the top most row
	Ypos = 0;
	// randomize the Xpos of the fruits
    Xpos = rand() % MapX_length;
	// the size of the fruits is always 1
    Size = 1;
}

// detect Keypressing and change the player's coordinate
void Basket::Move(int MapY_length, int MapX_length)
{
	if (kbhit())
	{
		char KeyPressed = getchar();
		if( (KeyPressed == 'a') || (KeyPressed == 'A') ) Xpos--; // decrement the Xpos of the basket if 'A' is pressed
		if( (KeyPressed == 'd') || (KeyPressed == 'D') ) Xpos++; // increment the Xpos of the basket if 'D' is pressed
			
		// power up
		if( (int(KeyPressed) == 110) ) { // the basket will go left by 2 pixel if 'N' is pressed
			Xpos -= 2;
		}
		if( (int(KeyPressed) == 109) ) { // the basket will go right by 2 pixel if 'M' is pressed
			Xpos += 2; 
		}
	}   
}

void Basket::init(int MapY_length, int MapX_length)
{
	// the Ypos of the basket is always in the bottom most row
    Ypos = MapY_length-1;
	// the Xpos of the basket is always in the middle of the map
    Xpos = MapX_length/2;
	// since the basket act as the player/ object that the player can move
    // we intialize the Health and the score of the player inside the basket initialization function
	HP = 3;
	Score = 0;
}

void Event::initMap()
{
	// initialize the map size
    MapSize_y = 15;
    MapSize_x = 22;
}

void Event::initVariables()
{
	// intialize variables that is needed
    EndGame = false;
    player.init(MapSize_y, MapSize_x);
    fruities.clear();
	intervalDrop = 12;
}

void Event::startingNewGame()
{
	// print the instructions of the game
	instructions();
	// store the last player score
	storeScoreboard();
	// print the score board
	printScoreboard();
	// initialize the map and other important variables
	initMap();
    initVariables();
}
