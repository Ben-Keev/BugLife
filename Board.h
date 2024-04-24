//
// Created by benmc on 24/04/2024.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream> // Get time as a string
#include <windows.h> // Sleep delay
#include <algorithm> // Remove vector by value

#include "Bug.cpp"
#include "Crawler.cpp"
#include "Hopper.cpp"
#include "Creeper.h"

#ifndef BUGLIFE_BOARD_H
#define BUGLIFE_BOARD_H


class Board {
private:
    // REMOVE VECTOR INPUTS FROM ALL METHODS
    vector<Bug*> bugs;

    string readNextToken();

    // For reading bugs from file.
    // Readin is what's left to read
    // Token is the chunk that's read
    struct {
        string readin;
        string token;
    } tokenData;

    static string pair_to_string(pair<int,int>);
    vector<Bug*> getBugsInCell(pair<int,int>);

public:
    // REMOVE VECTOR INPUTS FROM ALL METHODS
    void initBugsFromFile(ifstream&); // ADJUST TO ONLY SET ATTRIBUTE
    void displayAll(bool = false);
    Bug *const findBugById(); // ADJUST TO NOT RETURN POINTER
    void tapBoard();
    void displayAllPathHistory();
    void displayAllCells();
    void runSimulation();
    void exit();
};

#endif //BUGLIFE_BOARD_H