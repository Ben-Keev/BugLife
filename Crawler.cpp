//
// Created by benmc on 26/03/2024.
//

#include "Crawler.h"

void Crawler::move() {}

string Crawler::toString() {
    // https://www.geeksforgeeks.org/pair-in-cpp-stl/
    string coordinates = "(" + to_string(this->position.first) + "," + to_string(this->position.second) + ")";
    string direction = direction_to_string(this->direction);
    return to_string(this->id) + "\t" + "Crawler" + "\t" + coordinates + "\t\t" + direction + "\t\t" + to_string(this->alive);
}