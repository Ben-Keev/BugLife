//
// Created by benmc on 26/03/2024.
//

#ifndef BUGLIFE_HOPPER_H
#define BUGLIFE_HOPPER_H

#include "Bug.h"

class Hopper : public Bug {
protected:
    int hop_length;
public:
    string toString() override;
    int getHopLength() const;

    void move() override;

    // https://stackoverflow.com/questions/120876/what-are-the-rules-for-calling-the-base-class-constructor
    Hopper(int id, pair<int, int> position, Direction direction, int size, int hop_length)
            : Bug(id, position, direction, size) {
        this->hop_length = hop_length;
    };
};


#endif //BUGLIFE_HOPPER_H
