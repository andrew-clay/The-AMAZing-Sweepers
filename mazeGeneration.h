#ifndef MAZEGENERATION_H
#define MAZEGENERATION_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

const char WALL_CHAR = 'X';
const char PATH_CHAR = ' ';

// Some things of note for group:
// I think we should have had a 2d array of cell objects, instead of having a 2d array of chars.
// I believe this would have made it easier to implement the maze generation algorithm, as well as made the logic easier for maze navigation.

// --------------------------------------------
// Andrew Clay
// June 13, 2024
// 
// Functions and classes to generate a maze.
// The generateMaze(width, height) function will return a 2D array of chars, where X is a wall and o is an open space.
// 
// Comments to be deleted on final version:
// The maze generation algorithm is an attempt at eller's algorithm, but is not a perfect implementation, i dont think. I need to work on it way more.
// The maze in its current state, isnt very..maze-y, and I need to work on it way more, however I have a footholding and a basic start.
// Also there may be mistakes in the code, and the algorithm may not be perfect, but I am working on it.
// Also because there could be mistakes in the code, its possible that the maze may accidentally generate a maze that is impossible to solve.
// important resources:
// https://weblog.jamisbuck.org/2010/12/29/maze-generation-eller-s-algorithm
// http://www.neocomputer.org/projects/eller.html
// --------------------------------------------

// Example usage:
// #include "mazeGeneration.h"

// int main()
// {
//     int width, height;
//     std::cout << "Enter the width and height of the maze: ";
//     std::cin >> width >> height;
//     Maze maze(width, height);
//     // Generated maze is a 2D array of chars, X's and ' ''s right now. (can be changed)
//     // To use it just generatedMaze[x][y]
//     auto generatedMaze = maze.generateMaze(); 
//     maze.printMaze() 
// }



class Maze {
public:
    Maze(int width, int height) : width(width), height(height) {
        srand(time(NULL)); // Seed random number generator
        // Create a maze with all walls
        maze.resize(height, std::vector<char>(width, WALL_CHAR));
    }


    std::vector<std::vector<char>> generateMaze(int startX = 0, int startY = 0, int endX = -1, int endY = -1) {
        // Make it so by default, the start is at the top left and the end is at the bottom right
        if (endX == -1) endX = width - 1;
        if (endY == -1) endY = height - 1;

        // make sure start and end are within bounds and not on the border, by clamping them
        // Also an option would be to error out.

        // this can also be changed if we want to put holes into the border, instead of always being started inside the maze.
        startX = std::max(1, std::min(width - 2, startX));
        startY = std::max(1, std::min(height - 2, startY));
        endX = std::max(1, std::min(width - 2, endX));
        endY = std::max(1, std::min(height - 2, endY));

        // create a vector to keep track of the current set of each cell
        std::vector<int> current_set(width);

        // create a map to keep track of the size of each set
        std::unordered_map<int, int> set_count;

        // Initialize first row sets
        for (int i = 0; i < width; ++i) {
            current_set[i] = i;
            set_count[i] = 1;
        }

        // Loop through each row
        for (int y = 1; y < height - 1; ++y) { // Start from 1 to keep top border intact
            // loop through each cell in the row
            // these are the horizontal connections
            for (int x = 1; x < width - 2; ++x) { 
                if ((rand() % 2 == 0 || y == height - 2) && current_set[x] != current_set[x + 1]) { // 50% chance of merging sets
                    // Merge sets
                    int old_set = current_set[x + 1];

                    // Update set count
                    for (int k = 1; k < width - 1; ++k) {
                        if (current_set[k] == old_set) {
                            current_set[k] = current_set[x];
                        }
                    }
                    maze[y][x + 1] = PATH_CHAR; // Connect right
                }
            }

            // these are the horizontal connectionsns
            // create a map to keep track of which sets are connected
            std::unordered_map<int, bool> connected;
            // connect downwards
            for (int x = 1; x < width - 1; ++x) {
                if (y < height - 2 && (rand() % 2 == 0 || !connected[current_set[x]])) { // 50% chance of connecting down
                    connected[current_set[x]] = true; // mark set as connected
                    maze[y + 1][x] = PATH_CHAR; // connect downwards
                }
            }

            // prepare the next row 
            if (y < height - 2) {
                for (int x = 1; x < width - 1; ++x) {
                    if (maze[y + 1][x] == PATH_CHAR) {
                        current_set[x] = current_set[x]; // Continue set vertically
                    } else {
                        current_set[x] = x + y * width; // New set for each unconnected cell
                    }
                }
            }
        }

        // Place the entrance and exit
        // These character representations of these can be changed.
        maze[startY][startX] = '>';
        maze[endY][endX] = '^';

        return maze;
    }

    void printMaze() {
        for (const auto& row : maze) {
            for (char cell : row) {
                std::cout << cell;
            }
            std::cout << std::endl;
        }
    }

private:
    int width, height;
    std::vector<std::vector<char>> maze;
};

#endif
