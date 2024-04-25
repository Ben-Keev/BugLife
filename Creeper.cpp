//
// Created by benmc on 22/04/2024.
//

#include "Creeper.h"

void Creeper::move() {
    pair<int, int> newPosition = position;

    // Create a new position pair according to movement pattern
    switch(this->directionX) {
        case Direction::WEST:
            newPosition.first -= 1;
            break;
        case Direction::EAST:
            newPosition.first += 1;
            break;
        case Direction::NORTH:
        case Direction::SOUTH:
            // Default to west
            directionX = Direction::WEST;
    }

    switch(this->directionY) {
        case Direction::NORTH:
            newPosition.second -= 1;
            break;
        case Direction::SOUTH:
            newPosition.second += 1;
            break;
        case Direction::EAST: // Shouldn't be east or west. Pick a new direction and re-iterate.
        case Direction::WEST:
            // Default to South
            directionY = Direction::SOUTH;
            break;
    }

    // If the position has changed or the way is not block
    if(!(newPosition.first == position.first && newPosition.second == position.second) && !isWayBlocked(newPosition)) {
        path.push_back(position); // Record History
        this->position = newPosition;
    } else { // The way was blocked or the position was not fully unique from the previous

        // Go the opposite direction
        switch(this->directionX) {
            case Direction::WEST:
                directionX = Direction::EAST;
                break;
            case Direction::EAST:
                directionX = Direction::WEST;
                break;
        }

        // Go the opposite direction
        switch (this->directionY) {
            case Direction::NORTH:
                directionY = Direction::SOUTH;
                break;
            case Direction::SOUTH:
                directionY = Direction::NORTH;
                break;
        }

        move();
    }
}

string Creeper::getType() {
    return "Creeper";
}

string Creeper::toString() {
    // https://www.geeksforgeeks.org/pair-in-cpp-stl/
    string coordinates = "(" + to_string(this->position.first) + "," + to_string(this->position.second) + ")";
    string directionStringX = direction_to_string(this->directionX);
    string directionStringY = direction_to_string(this->directionY);
    return to_string(this->id) + "\t" + getType() + "\t" + coordinates + "\t\t" + directionStringX + ", " + directionStringY + "\t" + to_string(this->size);
}
