//
// Created by benmc on 26/03/2024.
//

#include "Hopper.h"

void Hopper::move() {

}

int Hopper::getHopLength() const {return this->hop_length;};

string Hopper::toString() {
    string coordinates = "(" + to_string(this->position.first) + "," + to_string(this->position.second) + ")";
    string direction = direction_to_string(this->direction);
    return to_string(this->id) + "\t" + "Hopper" + "\t" + coordinates + "\t\t" + direction + "\t\t" + to_string(this->hop_length) + "\t" + to_string(this->alive);
}