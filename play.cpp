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

bool Event::isRunning()
{
	// this is a function to detect wether it is game over or not
   	return !EndGame;
}

void Event::detectCatchedFruits() {
	// detect fruit if catched by the basket
    	for (int i = 0; i < 5; i++) { // the reason why i < 5 is because the basket size is 5
		// if there is a '*' inside the basket then it means the fruits is catched successfully
    		if(Map[player.Ypos][ (player.Xpos + i) % MapSize_x ] == '*') {
			// hence the player's score is increased
    			player.Score++;
    			break;
    		}
	}
}

void Event::detectDroppedFruits()
{
	// detect fruit if failed to be caught
	for (int i = 0; i < (MapSize_x-5); i++) {
	// the reason i < (MapSize_x-5) is because the basket size is 5, we only check all the pixel in the map outside the basket
		// if there is a '*' in the last line outside the basket then it means the fruits has dropped to the ground
    		if( Map[player.Ypos][ (player.Xpos + 5 + i) % MapSize_x ] == '*') {
			// hence the player health is deducted
    			player.HP--;
			// if the health is smaller than 0 then it is game over
    			if(player.HP <= 0) {
				// therefore the endgame variable become true
				EndGame = true;
				break;
			}
    		}
	}
}

void Event::refreshMap()
{
    	//reseting the map  
    	for(int i = 0; i < MapSize_y; i++)
    	{
        	for(int j = 0; j < MapSize_x; j++)
        	{
            		Map[i][j]='.';
        	}
    	}

	// updating the positions of all fruities in the map
	for(unsigned int i = 0; i < fruities.size(); i++)
	{
		int sz = fruities[i].Size;

		for(int j = 0; fruities[i].Ypos + j < MapSize_y && j < sz; j++)
		    for(int k = 0; fruities[i].Xpos + k < MapSize_x && k < sz; k++)
			Map[fruities[i].Ypos + j][fruities[i].Xpos + k] = '*';
	}

	detectCatchedFruits();

	detectDroppedFruits();

    	// updating the position of the player
    	for (int i = 0; i < 5; i++) { // again i < 5 is because the basket size is 5
		// case 1: over the left & right boundaries
		// when the x position of the basket which named player is below 0
		// adding MapSize_x will bring the basket back to the right most part of the map
		if ( player.Xpos < 0 ) player.Xpos += MapSize_x;
		// when the x position of the basket + 5 of its size is larger than the MapSize_x
		// taking the modulus of player.Xpos with the MapSize_x will bring the basket back to the left most part of the map
		if ( (player.Xpos + 5) > MapSize_x ) {
			Map[player.Ypos][ (player.Xpos + i) % MapSize_x ] = '_';
		}
		// case 2: inside the boundaries
		else Map[player.Ypos][player.Xpos + i] = '_';
	}
}

void Event::refreshPlayerStatus()
{
	player.Move(MapSize_y, MapSize_x);
}

void Event::refreshFruitStatus()
{
	// moving all the current Fruit
	for(unsigned int i = 0; i < fruities.size();)
    	{
		fruities[i].Move();

		// check if the fruit is outside the map
		if(fruities[i].Ypos >= MapSize_y)
			// delete the fruit when the Ypos is larger than the MapSize_y which means already in the very bottom
			fruities.erase(fruities.begin() + i);
			else i++;
		}

		// summoning a fruit with some interval, and increase the probability of dropping by score 
		if ( (player.Score % 3 == 0) && (player.Score != 0) && (player.Score != tmp) && (intervalDrop > 5) ) {
			intervalDrop -= 1; // interval starting from 15 to 14 to 13 .. 5 (every score of 3)
			tmp = player.Score;
		}
		if( count % intervalDrop == 0 ) {	
			Fruit dropFruits;
			dropFruits.init(MapSize_y, MapSize_x);
			fruities.push_back(dropFruits);
	}
	count++;
}

void Event::update()
{
	refreshPlayerStatus();
	refreshFruitStatus();
	refreshMap();
}

void Event::printUI()
{
	cout << "Health: " << player.HP << " | " << "Score: " << player.Score << "\n";
}

void Event::printMap()
{
	for(int i = 0; i < MapSize_y; i++)
    	{
		for(int j = 0; j < MapSize_x; j++)
        	{
        		cout << Map[i][j];
        	}
        cout << "\n";
    	}
}

void Event::print()
{
 	printUI();
 	printMap();
}

void Event::printScoreboard()
{
	// output from the scoreboard txt file
	ifstream fin ("Scoreboard.txt");
	
	// error handling
	if ( fin.fail() ) {
      		cout << "Error in file opening!" << endl;
      		exit(1);
   	}
   
	int cur_score;
	int i=1;
	while ( fin >> cur_score ) {
		if (i == 1){
			cout << "| Highest score        : " << cur_score << endl;
		}
		if (i == 2){
			cout << "| Second highest score : " << cur_score << endl;
		}
		if (i == 3){
			cout << "| Third highest score  : " << cur_score << endl;
			break;
		}
		i++;
 	}
	
	fin.close();
	
}

void Event::storeScoreboard()	// input to scoreboard txt file
{
	//to reset scoreboard
	if ( (ch.back() == 'r') || (ch.back() == 'R') ) {
		ofstream fout("Scoreboard.txt");
		// error handling
		if ( fout.fail() ) {
			cout << "Error in file opening!" << endl;
			exit(1);
		}
		//fout << endl;
		for (int i = 0; i < 3; i++) {
			fout << 0 << endl;
		}
		fout.close();
	}

	// open the file to get the list of scores in the scoreboard
	ifstream fin ("Scoreboard.txt");
	
	// error handling
	if ( fin.fail() ) {
      		cout << "Error in file opening!" << endl;
      		exit(1);
   	}
   
	// copy them into a vector 
	int score;
	vector<int> scores;
	int cur_score = player.Score; // new score that want to be added in the scoreboard
	 
	if (fin.is_open())
	{
	    	//read lines and push into vector
		while (fin >> score)
	    	{
	        	scores.push_back(score);
	    	}
	}
	
	fin.close();
	
	// insert the new score
	scores.push_back(cur_score);
	
	// sort them decreasingly
	sort(scores.rbegin(), scores.rend());
	
	// open file for writing
	ofstream fout("Scoreboard.txt");
	
	// error handling
	if ( fout.fail() ) {
      		cout << "Error in file opening!" << endl;
      		exit(1);
   	}
   
	// iterate vector and add lines
	for (int i = 0; i < 4; i++) {
		fout << scores[i] << endl;
	}
		
	fout.close();
}

void Event::instructions() 
{
	cout << "WELCOME TO ~ GOTTA CATCH'EM ALL, BUT FRUITS!" << endl;
	cout << '+' << setw(43) << setfill('+') << '+' << endl;
	cout << setfill(' ') << "+ Instructions! " << setw(28) << '+' << endl
		<< "+ " << "To move LEFT   : Press 'A' " << setw(15) << '+' << endl
        	<< "+ " << "To move RIGHT  : Press 'D' " << setw(15) << '+' << endl
         	<< "+ " << "To move FASTER : Press 'N' (left) " << setw(8) << '+' << endl
		<< "+ " << "                 Press 'M' (right) " << setw(7) << '+' << endl
		<< "+ " << "To RESET score : Press 'R' key " << setw(11) << '+' << endl
		<< "+ " << "To EXIT game   : Press 'Q' key " << setw(11) << '+' << endl
		<< "+ " << "To PLAY game   : Press any key " << setw(11) << '+' << endl;
    	cout << '+' << setw(43) << setfill('+') << '+' << endl;
}
