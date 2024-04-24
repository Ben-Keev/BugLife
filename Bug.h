//
// Created by benmc on 26/03/2024.
//

#ifndef BUGLIFE_BUG_H
#define BUGLIFE_BUG_H

#include <list>
#include <vector>

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
    bool alive = true;
    list<pair<int, int>> path;

public:
    virtual string toString() = 0;
    virtual string getType() = 0; // return the type of the bug as a string
    virtual void move() = 0;
    bool isWayBlocked(pair<int,int>);

    int getId() const;
    const pair<int, int>& getPosition() const;
    Direction getDirection() const;
    int getSize() const;
    bool isAlive() const;
    const list<pair<int,int>>& getPath() const;
    const string direction_to_string(Direction) const;
    string pair_to_string(pair<int,int>) const;
    Direction pickNewDirection();
    int eat(const vector<Bug*>&);

    Bug(int id, std::pair<int, int> position, Direction direction, int size) {
        this->id = id;
        this->position = position;
        this->direction = direction;
        this->size = size;
    };
};


#endif //BUGLIFE_BUG_H
