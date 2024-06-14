//Thomas Hammond, June 13 2024

#ifndef MAPFUNCTIONS_H
#define MAPFUNCTIONS_H
#include "mazeGeneration.h"
#include <iostream>
using namespace std;

class MapManager{
    private:
        vector<vector<char>> maze;
        int width;
        int height;

    public:
        MapManager(int width,int height): width(width), height(height){ //Uses Maze Generation to create a maze vector
            Maze mazeGenerator(this->width,this->height);
            maze = mazeGenerator.generateMaze();
        }
        bool inBounds(int x, int y){ //Checks if is within vector
            return x >= 0 && x < width && y >= 0 && y < height;
        }
        bool validPos(int x , int y){//Checks if x and y Position are empty or end
            return (inBounds(x,y) ? (maze[y][x] == ' ' || maze[x][y] == '^') : false);
        }
        bool isEnd(int x, int y){//Checks if x and y Position is the end position
            return (inBounds(x,y) ? (maze[y][x] == '^') : false);
        }
        vector<string> validMovementOptions(int x, int y){//Returns a vector of compass directions depending on surrounding valid positions
            vector<string> movementOptions;
            //North
                if(validPos(x,y-1))
                    movementOptions.push_back("North");
            //East
                if(validPos(x+1,y))
                    movementOptions.push_back("East");
            //South
                if(validPos(x,y+1))
                    movementOptions.push_back("South");
            //West
                if(validPos(x-1,y))
                    movementOptions.push_back("West");

                return movementOptions;
        }

        void DEBUG_SetMaze(Maze& newMaze){ //Debug Sets Maze
            maze = newMaze.generateMaze();
        }
        void DEBUG_PrintValidMovementOptions(int x, int y){ //Debug Prints Compass directions from validMovementOptions function
            vector<string> options;
            options = validMovementOptions(x,y);

            for(string direction: options){
                cout << direction << endl;
            }
            cout << endl;
        }



};

#endif // MAPFUNCTIONS_H
