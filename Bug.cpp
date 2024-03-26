//
// Created by benmc on 26/03/2024.
//

#include "Bug.h"

bool Bug::isWayBlocked() {return false;};

int Bug::getId() const {return this->id;};

const pair<int,int>& Bug::getPosition() const {return this->position;};

Direction Bug::getDirection() const {return this->direction;};

int Bug::getSize() const {return this->size;};

bool Bug::isAlive() const {return this->alive;};

const list<pair<int, int>>& Bug::getPath() const {return this->path;}

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