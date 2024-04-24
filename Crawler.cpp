//
// Created by benmc on 26/03/2024.
//

#include "Crawler.h"

void Crawler::move() {
    pair<int, int> newPosition = position;

    // Create a new position pair according to movement pattern
    switch(this->direction) {
        case Direction::NORTH:
            newPosition.second -= 1;
            break;
        case Direction::EAST:
            newPosition.first += 1;
            break;
        case Direction::SOUTH:
            newPosition.second += 1;
            break;
        case Direction::WEST:
            newPosition.first -= 1;
            break;
    }

    if(!isWayBlocked(newPosition)) {
        path.push_back(position); // Record History
        this->position = newPosition;
    } else { // The way was blocked, try to move again
        this->direction = pickNewDirection();
        move();
    }
}

string Crawler::toString() {
    // https://www.geeksforgeeks.org/pair-in-cpp-stl/
    string coordinates = "(" + to_string(this->position.first) + "," + to_string(this->position.second) + ")";
    string direction = direction_to_string(this->direction);
    return to_string(this->id) + "\t" + getType() + "\t" + coordinates + "\t\t" + direction + "\t\t" + to_string(this->size);
}

string Crawler::getType() { return "Crawler"; }