#include "play.h"
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
    srand( time(NULL) );
    Event play;
    while (1) {
        system("clear");
        play.startingNewGame();

        //system pause to ask player decision
        cout << "Play(any)/Reset(R)/Quit(Q): ";
        cin >> play.ch;
        if ( (play.ch.back() == 'q') || (play.ch.back() == 'Q') ) { break; } // to exit
        else if ( (play.ch.back() == 'r') || (play.ch.back() == 'R') ) { continue; } // to reset score
        else { play.ch = "#"; } //reset the variable, continue playing

        //game playing
        while(play.isRunning())
        {
            usleep(100000);
            system("clear");
            play.update();
            play.print();
        }
        cout << "Game over!" << endl;
        cout << "Please wait..." << endl;
        usleep(2000000); // to let players see the board for a few seconds after they lose, then return back to main menu 
    }
    return 0;
}
