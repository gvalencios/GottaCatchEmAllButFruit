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

