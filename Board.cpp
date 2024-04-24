//
// Created by benmc on 24/04/2024.
//

#include <iomanip>
#include "Board.h"

void Board::initBugsFromFile(ifstream& fin) {
    Bug* bug_ptr;

    // Reading data from file
    string readin;

    // Check Stream is valid
    if(fin) {

        // while not at end of file
        while(!fin.eof()) {

            getline(fin, tokenData.readin);
            string type = readNextToken();
            int id = stoi(readNextToken());

            int x = stoi(readNextToken());
            int y = stoi(readNextToken());
            pair<int, int> position = pair(x, y);

            Direction direction = static_cast<Direction>(stoi(readNextToken()));
            int size = stoi(readNextToken());

            if(type == "C") {
                bug_ptr = new Crawler(id, position, direction, size);

            } else if(type == "H") {
                int hop_length = stoi(readNextToken());
                bug_ptr = new Hopper(id, position, direction, size, hop_length);
            } else if(type == "Cr") {
                // Creeper is entered in the format.
                // Type;ID;X;Y;DirectionX;Size;DirectionY
                // Direction X should be 1 or 3, Direction Y should be 2 or 4
                Direction directionY = static_cast<Direction>(stoi(readNextToken()));
                bug_ptr = new Creeper(id, position, direction, directionY, size);
            }

            bugs.push_back(bug_ptr);
        }
    }
}

string Board::readNextToken() {
    tokenData.token = tokenData.readin.substr(0, tokenData.readin.find(";"));
    //cout << "token: " << tokenData.token << endl;
    tokenData.readin = tokenData.readin.substr(tokenData.readin.find(";")+1);
    //cout << "readin: " << tokenData.readin << endl;

    return tokenData.token;
}

void Board::displayAll(bool mustBeAlive) { // Default parameter  to include or exclude living bugs
    cout << "ID\t" << "Type\t" << "Position\t" << "Direction\t" << "Size\t" << "HopLength" << endl;

    for(auto & bug : bugs) {
        if(mustBeAlive) {
            if (!bug->isAlive()) // Skip Dead bugs
                continue;
        }
        cout << bug->toString() << endl;
    }

    cout << endl;
}

// Can't return a bug... It's an abstract type.
// TODO Stop this from returning a pointer somehow.
Bug *const Board::findBugById() {
    string input;
    int id;

    cout << "Input an ID: ";
    cin >> input;

    id = stoi(input);

    for(Bug* bug : bugs) {
        if(bug->getId() == id) {
            cout << bug->toString() << endl;
            return bug;
        }
    }

    // Not Found
    cout << "Bug not found" << endl;
    cout << endl;

    return nullptr;
}

void Board::tapBoard() {
    for(Bug* bug: bugs) {
        bug->move();
        bug->eat(getBugsInCell(bug->getPosition()));
    }

    displayAll(true);

    cout << endl;
}

void Board::displayAllPathHistory() {
    for(Bug* bug: bugs) {
        cout << bug->getType() << " ID " << to_string(bug->getId()) << " ALIVE: " << bug->isAlive() << endl;
        for (pair<int,int> position: bug->getPath()) {
            cout << pair_to_string(position) << endl;
        }
        cout << endl;
    }
}

void Board::displayAllCells() {
    vector<Bug*> bugsInCell;

    pair<int,int> cell;
    for(int x = 0; x < 10; x++) {
        for(int y = 0; y < 10; y++) {
            cell.first = x; cell.second = y;
            cout << pair_to_string(cell) << ": ";

            // Assign bugsInCell each iteration. check if it's empty
            if((bugsInCell = getBugsInCell(cell)).empty()) {
                cout << "Empty" << endl;
            } else {
                for (Bug* bug: bugsInCell) {
                    cout << bug->getType() << " ID " << bug->getId() << " | ";
                }
                cout << endl;
            }
        }
    }
}

vector<Bug*> Board::getBugsInCell(pair<int, int> cell) {
    vector<Bug*> bugsInCell;

    for(Bug* bug: bugs) {
        if(bug->getPosition() == cell) { // Only alive bugs occupy a cell.
            bugsInCell.push_back(bug);
        }
    }

    return bugsInCell;
}

void Board::runSimulation() {
    int turns = 0;

    // Duplicate the vector
    vector<Bug*> livingBugs = bugs;

    while (livingBugs.size() > 1) { // There is more than one living bug
        turns++;
        cout << "Turn " << turns << endl << "=================" << endl;
        tapBoard();
        for(Bug* bug: bugs) {
            if(!bug->isAlive()) {
                // Remove from vector by value https://stackoverflow.com/a/3385251
                livingBugs.erase(remove(livingBugs.begin(), livingBugs.end(), bug), livingBugs.end());
            }
        }

        // Use Sleep from windows.h https://stackoverflow.com/a/10807745
        Sleep(1000);
    }

    exit();
}

void Board::exit() {
    // TODO SOURCE THIS
    // current date/time based on current system
    time_t now = time(0);

    https://stackoverflow.com/a/997531
    // Get time as a string.
    std::stringstream ss;

    //https://cplusplus.com/reference/iomanip/put_time/?kw=put_time
    using chrono::system_clock;
    std::time_t tt = system_clock::to_time_t (system_clock::now());

    struct std::tm * ptm = localtime(&tt);

    // Place time into string
    ss << put_time(ptm, "%D_%R");

    // Convert string stream into string and add to filename
    ofstream fout("bugs_life_history_" + ss.str());

    for(Bug* bug: bugs) {
        fout << "BUG ID " << to_string(bug->getId()) << endl;
        for (pair<int,int> position: bug->getPath()) {
            fout << pair_to_string(position) << endl;
        }
        fout << endl;
    }

}

// Static method to convert pair to string
string Board::pair_to_string(pair<int,int> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
};