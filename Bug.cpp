//
// Created by benmc on 26/03/2024.
//

#include "Bug.h"

bool Bug::isWayBlocked(pair<int,int> newPosition) {
    if((newPosition.first > -1 && newPosition.first < 10) && (newPosition.second > -1 && newPosition.second < 10)) {
        return false;
    } else {
        return true;
    }
};

int Bug::getId() const {return this->id;};

const pair<int,int>& Bug::getPosition() const {return this->position;};

Direction Bug::getDirection() const {return this->direction;};

int Bug::getSize() const {return this->size;};

bool Bug::isAlive() const {return this->alive;};

const list<pair<int, int>>& Bug::getPath() const {return this->path;}

// Pick a new direction at random
void Bug::pickNewDirection() {
    // https://stackoverflow.com/questions/2999012/generating-random-enums
    auto randomDirection = static_cast<Direction>((rand()%4)+1);

    this->direction = randomDirection;
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