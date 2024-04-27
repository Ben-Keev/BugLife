//
// Created by benmc on 27/04/2024.
//

#ifndef BUGLIFE_SUPER_H
#define BUGLIFE_SUPER_H

#include "Bug.h"

class Super : public Bug {
public:
    string toString() override;
    void move() override;
    string getType() override;

    Super(int id, pair<int, int> position, Direction direction, int size)
            : Bug(id, position, direction, size) {
        this->sfmlColor = sf::Color::Yellow;
    };

    void controlMovement (sf::Event event);

    void adjustX(int);
    void adjustY(int);

    int getX();
    int getY();
};

#endif //BUGLIFE_SUPER_H