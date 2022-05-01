# Gotta Catch’em All! But Fruit..!
## Team Members
:panda_face: Georgy Valencio Siswanta UID: 3035898896

:tiger: Dave Matthew UID: 3035898901

## Description
Gotta Catch’em All…But Fruit! is a game where players will catch fruits falling from the legendary sky with their basket. Fruits will drop randomly with a certain velocity. However, as the score increases, the speed of the falling fruit will be increased. The player gets 3 lives at first and losing one fruit means losing 1 life. Beat the current highscore to show who's the best in this game!

## Game Rules
1. Players will move the basket using their keyboard’s arrow key or 'A' and 'D' key.
2. Players must try to fit the fruits into their basket.
3. Losing 1 fruit means losing 1 life out of 3 lives given at the beginning of the game.
4. Catching 1 fruit means earning 1 points which then will be uploaded into the scoreboard.
5. The longer you play, the faster the fruit gets, making it more challenging to catch the fruits.

## Features
1. The random element of this game will be the frequency, speed, and location where the fruits will be generated.
2. In this game, several data structures (struct, vector, array) will be used. There are 3 main structs in this game which are the Fruit, Basket, and Event. On the other hand, one of the examples of the usage of the vector in the game is to store and sort the high score of players.
3. The process of catching the fruits will involve dynamic memory management, as after the fruit is caught or after it is out of the map, it will be removed from the vector.
4. File input/output will also be used to store the score of players and display the top 3 high scores. There is also a reset score feature where players need to press the ‘R’ key to reset the whole scoreboard hence erasing all the high score history.
5. The source of the game will be separated into 3 different files(“main.cpp”, “play.cpp”, and “play.h”) which will then be imported into the makefile, which will be executed.
6. In all of the game source files, all functions and data structure has been properly written with correct indentation and naming style.
7. In-code documentation will also be provided in the game file in a form of descriptive comments explaining the “what it does”, “what the inputs are”, and “what the outputs are” questions. 

## Non-standard C/C++ Libraries Used
In the game, there are #include "play.h" which is the library/ header file that we created. Inside the "play.h" there are structs and functions declarations that are used to operate the game. 

## Quick Start
Run the makefile

