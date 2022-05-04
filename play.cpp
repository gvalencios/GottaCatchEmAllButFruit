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
