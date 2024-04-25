//
// Created by benmc on 22/04/2024.
//

#ifndef BUGLIFE_CREEPER_H
#define BUGLIFE_CREEPER_H

#include "Bug.h"

class Creeper : public Bug {

protected:
    Direction directionX;
    Direction directionY;

public:
    string toString() override;
    void move() override;
    string getType() override;

    Creeper(int id, pair<int, int> position, Direction directionX, Direction directionY, int size)
            : Bug(id, position, direction, size) {
        this->directionX = directionX;
        this->directionY = directionY;
    };
};

#endif //BUGLIFE_CREEPER_H
