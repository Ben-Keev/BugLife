//
// Created by benmc on 26/03/2024.
//

#include "Hopper.h"

void Hopper::move() {
    pair<int, int> newPosition = position;

    // Create a new position pair
    switch(this->direction) {
        case Direction::NORTH:
            newPosition.second = calculateHop(newPosition.second);
            break;
        case Direction::EAST:
            newPosition.first = calculateHop(newPosition.first);
            break;
        case Direction::SOUTH:
            newPosition.second = calculateHop(newPosition.second);
            break;
        case Direction::WEST:
            newPosition.first = calculateHop(newPosition.first);
            break;
    }

    if(!onEdge(this->position)) {
        path.push_back(position); // Record History
        this->position = newPosition;
        //cout << "Hopper Movement: " << direction_to_string(this->direction) << endl;
        //cout << "(" << newPosition.first << ", " << newPosition.second << ")" << endl;

    } else { // Trying to jump in a position while on edge, pick a new direction and move
        this->direction = pickNewDirection();
        move();
    }
}

int Hopper::calculateHop(int value) {
    int newValue = value;

    // The value is subtracted
    if(this->direction == Direction::WEST || this->direction == Direction::NORTH) {
        if(value - hop_length < -1) {
            newValue = 0;

        } else {
            newValue -= hop_length;
        }
    } else { // The value is added
        if(value + hop_length > 10) {
            newValue = 9;
        } else {
            newValue += hop_length;
        }
    }

    return newValue;
}


bool Hopper::onEdge(pair<int, int> position) {
    if ( // Check all conditions
            (this->direction == Direction::NORTH && position.second == 0) ||
            (this->direction == Direction::EAST && position.first == 9) ||
            (this->direction == Direction::WEST && position.first == 0) ||
            (this->direction == Direction::SOUTH && position.second == 9)
    )   {
        return true;
    }

    return false;
}

int Hopper::getHopLength() const {return this->hop_length;};

string Hopper::toString() {
    string coordinates = "(" + to_string(this->position.first) + "," + to_string(this->position.second) + ")";
    string direction = direction_to_string(this->direction);
    return to_string(this->id) + "\t" + getType() + "\t" + coordinates + "\t\t" + direction + "\t\t" + to_string(this->size) + "\t" + to_string(this->hop_length);
}

string Hopper::getType() { return "Hopper"; }