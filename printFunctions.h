#ifndef PRINTFUNCTIONS_H
#define PRINTFUNCTIONS_H

/* Zaina Williams - zjwilliams1@dmacc.edu
 * June 11, 2024
 * June 20, 2024 (minor fix)
 *
 * Functions for orientating and printing movement options for maze navigation.
*/

#include <iostream>
#include <map>
#include <vector>
using namespace std;

// Takes a vector of compass movements ("North", ...) and changes refrence vector with facing-direction accounted ("left", ...).
void adjustDirection(vector<string> movementOptions, vector<string>& adjustedOptions, string playerFacing){
    // compass and rotation are a pair.
    array<string, 4> compass = {"North", "East", "South", "West"};
    array<int, 4> rotation = {0, 90, 180, 270};

    map<int, string> rotationMap;
    rotationMap[0] = "forward";
    rotationMap[90] = "right";
    rotationMap[180] = "back";
    rotationMap[270] = "left";

    // Update rotation for playerFacing, North is default.
    int correction = 0;

    if (playerFacing == "East"){
        correction = -90;
    } else if (playerFacing == "South"){
        correction = 180;
    } else if (playerFacing == "West"){
        correction = 90;
    }

    for(int i = 0; i < rotation.size(); i++){
        rotation[i] += correction;

        // Correction for overspilling rotations.
        if (rotation[i] > 270){
            rotation[i] = 0;
        } else if (rotation[i] < 0){
            rotation[i] = 270;
        }
    }

    // Look through movementOptions and compare to compass, adding the relating rotation direction (using rotationMap) to adjustedOptions.
    for (int i = 0; i < compass.size(); i++){
        for (auto & item : movementOptions){
            if (item == compass.at(i)){
                adjustedOptions.push_back(rotationMap[rotation[i]]);
                continue;
            }
        }
    }
}

// Returns random flavor text from cache.
string flavorText(){
    array<string, 7> flavorText = {"Something briefly shakes in the hedges to your left, then stills.",
        "The air is deathly still.",
        "The flashlight flickers, shadows seem to creep closer.",
        "There is a strange murmuring in your ears.",
        "You think you hear something moving behind you.",
        "The vibrant green hedges around you seem to lose color.",
        "The sky doesn't have stars."
    };
    int text = rand() % flavorText.size();
    return flavorText[text];
}

// Takes a vector of adjusted options and prints flavor text, dynamic options to player.
void printOptions(vector<string>& adjustedOptions){

    // Flavor text.
    cout << flavorText() << endl;

    // Dynamic print options for number of paths avaliable.
    if (adjustedOptions.size() == 4){
        cout << "You are at a crossroads. ";
    } else if (adjustedOptions.size() == 2){
        cout << "The path is limited. ";
    }

    if (adjustedOptions.size() == 1){
        cout << "There is only one path. You must go " << adjustedOptions.at(0) << "." << endl;
    }
    else {
        // Output path options for more than one path.
        cout << "You can ";
        for (int i = 0; i < adjustedOptions.size() - 1; i++){
            // Added depth.
            if (adjustedOptions.at(i) == "forward"){
                cout << "keep moving ";
            } else {
                cout << "turn ";
            }
            cout << adjustedOptions.at(i) << ", ";
        }
        cout << "or go " << adjustedOptions.at(adjustedOptions.size() -1) << "." << endl;
    }
}

#endif // PRINTFUNCTIONS_H
