//
// Created by benmc on 24/04/2024.
//



#ifndef BUGLIFE_BOARD_H
#define BUGLIFE_BOARD_H

#include "Hopper.h"
#include "Crawler.h"
#include "Creeper.h"
#include "Super.h"

class Board {
private:
    // REMOVE VECTOR INPUTS FROM ALL METHODS
    vector<Bug*> bugs;

    vector<sf::RectangleShape> sfmlSquares;
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
    void displayAllPathHistory(ostream& = cout);
    void displayAllCells();
    void exit();

    void sfmlInitialiseGrid();
    void sfmlDrawGrid();
    void sfmlDrawBugs(vector<Bug*>&);
    void sfmlClearGrid();
    void runSimulation(thread);
    void runSimulation();

    void tapBoard();
    Bug *getLargestBugInCell(pair<int, int> position);

    void playerMovement(Bug *super);

    Bug *const findBugById(int id);
};

#endif //BUGLIFE_BOARD_H