//
// Created by benmc on 27/04/2024.
//

#include "Super.h"

void Super::move() {} // The movement is player controlled. Here to be consistent with the rest of the bugs.

// Utilising code from Moodle sample https://github.com/delboy8080/SFML_Sample2
void Super::controlMovement(sf::Event event) {
    // 40 units makes
    if (event.key.code == sf::Keyboard::Up) {
        if (this->position.second > 0)
            this->position.second -= 1;
    }
    if (event.key.code == sf::Keyboard::Down) {
        if (this->position.second < 9)
            this->position.second += 1;
    }
    if (event.key.code == sf::Keyboard::Left) {
        if (this->position.first > 0)
            this->position.first -= 1;
    }
    if (event.key.code == sf::Keyboard::Right) {
        if (this->position.first < 9)
            this->position.first += 1;
    }
}
int Super::getX() {return this->position.first;}
int Super::getY() {return this->position.second;}

void Super::adjustX(int offset) {this->position.first += offset;}
void Super::adjustY(int offset) {this->position.second += offset;}

string Super::getType() {
    return "Super";
}

string Super::toString() {
    // https://www.geeksforgeeks.org/pair-in-cpp-stl/
    string coordinates = "(" + to_string(this->position.first) + "," + to_string(this->position.second) + ")";
    string direction = direction_to_string(this->direction);
    return to_string(this->id) + "\t" + getType() + "\t" + coordinates + "\t\t" + direction + "\t\t" + to_string(this->size);
}