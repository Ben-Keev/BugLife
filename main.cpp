#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream> // Get time as a string
#include <windows.h> // Sleep delay
#include <algorithm> // Remove vector by value

#include "Bug.cpp"
#include "Crawler.cpp"
#include "Hopper.cpp"
#include "Creeper.h"

vector<Bug*> initBugsFromFile(ifstream&);
void displayAll(vector<Bug*>&, bool = false);
string readNext();
Bug* findBug(vector<Bug*>&);
void tapBoard(vector<Bug*>&);
void displayAllPathHistory(vector<Bug*>&);
string pair_to_string(pair<int,int>);
void displayAllCells(vector<Bug*>&);
vector<Bug*> getBugsInCell(vector<Bug*>&, pair<int,int>);
void runSimulation(vector<Bug*>&);
void exit(vector<Bug*>&);

int main() {
    // Initialise random seed https://en.cppreference.com/w/cpp/numeric/random/srand
    srand(time(0));

    // Multi-Line String https://stackoverflow.com/a/1135862
    const char *menu =
            "1. Initialise Bug Board (Load Data From File)\n"
            "2. Display All Bugs\n"
            "3. Find a Bug by ID\n"
            "4. Tap the Bug Board\n"
            "5. Display Life History of All Bugs\n"
            "6. Display All; Cells\n"
            "7. Run Simulation\n"
            "8. Exit\n";

    bool running = true;
    int input = 0;
    vector<Bug*> bugs;

    while(running) {
        cout << menu << endl;
        cout << "Choose an option: ";
        cin >> input;
        cout << endl;

        switch (input) {
            // Use curly brackets to avoid errors https://stackoverflow.com/a/34830061
            case 1: { // Initialise Board
                ifstream fin("bugs.txt");
                bugs = initBugsFromFile(fin);
                break;
            }

            case 2: { // Display all bugs
                displayAll(bugs);
                break;
            }

            case 3: { // Find a bug
                findBug(bugs);
                break;
            }

            case 4: { // Tap the board
                tapBoard(bugs);
                break;
            }

            case 5: {
                displayAllPathHistory(bugs);
                break;
            }

            case 6: {
                displayAllCells(bugs);
                break;
            }

            case 7: {
                runSimulation(bugs);
                break;
            }

            case 8: {
                exit(bugs);
                running = false;
                break;
            }

            default: {
                cout << "Invalid input. Try again" << endl;
            }
        }
    }

    return 0;
};

struct {
    string readin;
    string token;
} tokenData;

vector<Bug*> initBugsFromFile(ifstream& fin) {
    vector<Bug*> bugs;
    Bug* bug_ptr;

    // Reading data from file
    string readin;

    // Check Stream is valid
    if(fin) {

        // while not at end of file
        while(!fin.eof()) {

            getline(fin, tokenData.readin);
            string type = readNext();
            int id = stoi(readNext());

            int x = stoi(readNext());
            int y = stoi(readNext());
            pair<int, int> position = pair(x, y);

            Direction direction = static_cast<Direction>(stoi(readNext()));
            int size = stoi(readNext());

            if(type == "C") {
                bug_ptr = new Crawler(id, position, direction, size);

            } else if(type == "H") {
                int hop_length = stoi(readNext());
                bug_ptr = new Hopper(id, position, direction, size, hop_length);
            } else if(type == "Cr") {
                // Creeper is entered in the format.
                // Type;ID;X;Y;DirectionX;Size;DirectionY
                // Direction X should be 1 or 3, Direction Y should be 2 or 4
                Direction directionY = static_cast<Direction>(stoi(readNext()));
                bug_ptr = new Creeper(id, position, direction, directionY, size);
            }

            bugs.push_back(bug_ptr);
        };
    };

    return bugs;
};

string readNext() {
    tokenData.token = tokenData.readin.substr(0, tokenData.readin.find(";"));
    //cout << "token: " << tokenData.token << endl;
    tokenData.readin = tokenData.readin.substr(tokenData.readin.find(";")+1);
    //cout << "readin: " << tokenData.readin << endl;

    return tokenData.token;
};

void displayAll(vector<Bug*>& bugs, bool mustBeAlive) { // Default parameter  to include or exclude living bugs
    cout << "ID\t" << "Type\t" << "Position\t" << "Direction\t" << "Size\t" << "HopLength" << endl;

    for(auto & bug : bugs) {
        if(mustBeAlive) {
            if (!bug->isAlive()) // Skip Dead bugs
            continue;
        }
        cout << bug->toString() << endl;
    };

    cout << endl;
};

Bug* findBug(vector<Bug*>& bugs) {
    string input;
    int id;

    cout << "Input an ID: ";
    cin >> input;

    id = stoi(input);

    for(Bug* bug : bugs) {
        if(bug->getId() == id) {
            cout << bug->toString() << endl;
            return bug;
        };
    };

    // Not Found
    cout << "Bug not found" << endl;
    cout << endl;

    return nullptr;
};

void tapBoard(vector<Bug*>& bugs) {
    for(Bug* bug: bugs) {
        bug->move();
        bug->eat(getBugsInCell(bugs, bug->getPosition()));
    };

    displayAll(bugs, true);

    cout << endl;
};

void displayAllPathHistory(vector<Bug*>& bugs) {
    for(Bug* bug: bugs) {
        cout << bug->getType() << " ID " << to_string(bug->getId()) << " ALIVE: " << bug->isAlive() << endl;
        for (pair<int,int> position: bug->getPath()) {
            cout << pair_to_string(position) << endl;
        }
        cout << endl;
    };

};

void displayAllCells(vector<Bug*>& bugs) {
    vector<Bug*> bugsInCell;

    pair<int,int> cell;
    for(int x = 0; x < 10; x++) {
        for(int y = 0; y < 10; y++) {
            cell.first = x; cell.second = y;
            cout << pair_to_string(cell) << ": ";

            // Assign bugsInCell each iteration. check if it's empty
            if((bugsInCell = getBugsInCell(bugs, cell)).empty()) {
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

vector<Bug*> getBugsInCell(vector<Bug*>& bugs, pair<int, int> cell) {
    vector<Bug*> bugsInCell;

    for(Bug* bug: bugs) {
        if(bug->getPosition() == cell) { // Only alive bugs occupy a cell.
            bugsInCell.push_back(bug);
        }
    }

    return bugsInCell;
}

void exit(vector<Bug*>& bugs) {
    // TODO SOURCE THIS
    // current date/time based on current system
    time_t now = time(0);

    https://stackoverflow.com/a/997531
    // Get time as a string.
    std::stringstream ss;
    ss << now;
    std::string ts = ss.str();

    ofstream fout("bugs_life_history_");

    for(Bug* bug: bugs) {
        cout << "BUG ID " << to_string(bug->getId()) << endl;
        for (pair<int,int> position: bug->getPath()) {
            cout << pair_to_string(position) << endl;
        }
        cout << endl;
    }
}

void runSimulation(vector<Bug*>& bugs) {
    int turns = 0;

    // Duplicate the vector
    vector<Bug*> livingBugs = bugs;

    while (livingBugs.size() > 1) { // There is more than one living bug
        turns++;
        cout << "Turn " << turns << endl << "=================" << endl;
        tapBoard(bugs);
        for(Bug* bug: bugs) {
            if(!bug->isAlive()) {
                // Remove from vector by value https://stackoverflow.com/a/3385251
                livingBugs.erase(remove(livingBugs.begin(), livingBugs.end(), bug), livingBugs.end());
            }
        }

        // Use Sleep from windows.h https://stackoverflow.com/a/10807745
        Sleep(1000);
    }

    exit(bugs);
}

string pair_to_string(pair<int,int> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
};