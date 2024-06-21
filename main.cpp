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

    Player player; // Create the player x, y.

    // Maze creation and handling.
    int width = 5;
    int height = 5;
    Maze mazeGenerator(width, height);
    MapManager mapManager(width, height);

    // Set maze.
    mapManager.DEBUG_SetMaze(mazeGenerator);

    // For player movement and game loop.
    string userInput;
    bool validInput;
    string playerFacing = "South"; // Default South.
    vector<string> adjustedOptions;
    vector<string> movementOptions = mapManager.validMovementOptions(player.x,player.y);

    // Opening.
    cout << "You have just entered a dark hedge maze. There is no going back." << endl;

    // Print begining options.
    adjustDirection(movementOptions, adjustedOptions, playerFacing);
    printOptions(adjustedOptions);

    // Priming.
    cout << "Enter a direction: (forward/left/right/back/quit): ";
    cin >> userInput;

    // Game loop.
    while (userInput != "quit"){

        validInput = false; // Assume false.

        // Validate user input.
        for (int i = 0; i < adjustedOptions.size(); i++){
            if (userInput == adjustedOptions.at(i)){

                validInput = true; // Flag.

                if (movementOptions.at(i) == "North"){
                        player.y -= 1;
                        playerFacing = "North";
                        cout << "You go " << adjustedOptions.at(i) << "." << endl;
               }

                else if (movementOptions.at(i) == "East"){
                        player.x = player.x + 1;
                        playerFacing = "East";
                        cout << "You go " << adjustedOptions.at(i) << "." << endl;

                }

                else if (movementOptions.at(i) == "South"){
                    player.y += 1;
                    playerFacing = "South";
                    cout << "You go " << adjustedOptions.at(i) << "." << endl;
                    break;
                }

                else if (movementOptions.at(i) == "West"){
                    player.x -= 1;
                    playerFacing = "West";
                    cout << "You go " << adjustedOptions.at(i) << "." << endl;
                    break;
                }

            }
        }

        // Handle invalid input.
        if (!validInput){
            cout << "Invalid input. ";
        }

        // Next move.
        else {

            // Check for the end of maze.
            if (mapManager.isEnd(player.x, player.y)){
                // End text.
                cout << "You step out of the maze into sunlight. You made it out." << endl;
                break;
            }

            // Reset vectors.
            adjustedOptions.clear();
            movementOptions = mapManager.validMovementOptions(player.x,player.y);

            // Print updated options.
            adjustDirection(movementOptions, adjustedOptions, playerFacing);
            printOptions(adjustedOptions);
        }

        // Prompt for next direction.
        cout << "Enter a direction (left/right/forward/back/quit): ";
        cin >> userInput;
    }

    cout << "Thanks for playing." << endl;
    return 0;
}
