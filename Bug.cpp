//
// Created by benmc on 26/03/2024.
//

#include "Bug.h"

bool Bug::isWayBlocked(pair<int,int> newPosition) {
    if((newPosition.first >= 0 && newPosition.first <= 9) && (newPosition.second >= 0 && newPosition.second <= 9)) {
        return false;
    } else {
        return true;
    }
};

int Bug::eat(const vector<Bug*>& bugsInCell) {
    if(!this->isAlive()) { return -1; } // Dead bugs cannot eat

    // Challenge every bug in the cell
    for (Bug* other : bugsInCell) {
        if(other != this && other->isAlive()) { // Don't eat yourself
                other->die();
                this->size += other->getSize();
        } // If other is a greater size it will be eaten by other's eat().
    }

    return 0;
}

// Make the bug invisible in SFML, remove it from a valid position, and set alive to false
void Bug::die() {
    this->alive = false;
    this->sfmlColor = sf::Color::Transparent;
}

int Bug::getId() const {return this->id;};

const pair<int,int>& Bug::getPosition() const {return this->position;};

Direction Bug::getDirection() const {return this->direction;};

int Bug::getSize() const {return this->size;};

bool Bug::isAlive() const {return this->alive;};

sf::Color Bug::getSfmlColor() const {return this->sfmlColor;}

const list<pair<int, int>>& Bug::getPath() const {return this->path;}

// Pick a new direction at random
Direction Bug::pickNewDirection() {
    // https://stackoverflow.com/questions/2999012/generating-random-enums
    return static_cast<Direction>((rand()%4)+1);
}

// https://mariusbancila.ro/blog/2023/08/17/how-to-convert-an-enum-to-string-in-cpp/
const string Bug::direction_to_string(Direction d) const {
    switch (d) {
        case Direction::NORTH: return "north";
        case Direction::EAST: return "east";
        case Direction::SOUTH: return "south";
        case Direction::WEST: return "west";
    }
    return "";
};