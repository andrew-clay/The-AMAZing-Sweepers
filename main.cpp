#include <cstdlib>  // Needed for random in flavorText function.
#include <time.h>   // Needed for a more random random.
#include "printFunctions.h"
#include "mazeGeneration.h"
#include "mapFunctions.h"

struct Player{
    int x = 1;
    int y = 1;
};

int main(){
    srand(time(0)); // Needed for random in flavorText function.
    Player player;
    int width = 30;
    int height = 15;
    Maze mazeGenerator(width, height);
    MapManager mapManager(width, height);
    mapManager.DEBUG_SetMaze(mazeGenerator);

    mazeGenerator.printMaze();

    mapManager.DEBUG_PrintValidMovementOptions(player.x, player.y);

    string playerFacing = "East";
    vector<string> adjustedOptions;

    adjustDirection(mapManager.validMovementOptions(player.x,player.y), adjustedOptions, playerFacing);

    printOptions(adjustedOptions);
    return 0;
}

