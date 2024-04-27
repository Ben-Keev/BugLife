//
// Created by benmc on 26/03/2024.
//

#ifndef BUGLIFE_CRAWLER_H
#define BUGLIFE_CRAWLER_H

#include "Bug.h"

class Crawler : public Bug {
public:
    string toString() override;
    void move() override;
    string getType() override;

    Crawler(int id, pair<int, int> position, Direction direction, int size)
    : Bug(id, position, direction, size) {
        this->sfmlColor = sf::Color::Green;
    };
};

#endif //BUGLIFE_CRAWLER_H
