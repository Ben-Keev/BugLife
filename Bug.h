//
// Created by benmc on 26/03/2024.
//

#ifndef BUGLIFE_BUG_H
#define BUGLIFE_BUG_H

#include <list>

using namespace std;

enum class Direction {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
};

class Bug {
protected:
    int id;
    pair<int, int> position;
    Direction direction;
    int size;
    bool alive;
    list<pair<int, int>> path;

public:
    virtual string toString() = 0;
    virtual void move() = 0;
    bool isWayBlocked();

    int getId() const;
    const pair<int, int>& getPosition() const;
    Direction getDirection() const;
    int getSize() const;
    bool isAlive() const;
    const list<pair<int,int>>& getPath() const;
    const string direction_to_string(Direction) const;

    Bug(int id, std::pair<int, int> position, Direction direction, int size) {
        this->id = id;
        this->position = position;
        this->direction = direction;
        this->size = size;
    };
};


#endif //BUGLIFE_BUG_H