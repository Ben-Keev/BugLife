//
// Created by benmc on 24/04/2024.
//

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
            } else if(type == "S") {
                bug_ptr = new Super(id, position, direction, size);
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

Bug *const Board::findBugById(int id) {
    for(Bug* bug : bugs) {
        if(bug->getId() == id) {
            cout << bug->toString() << endl;
            return bug;
        }
    }

    return nullptr;
}

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

        // Get the largest bug in a cell and call eat from it.
        getLargestBugInCell(bug->getPosition())
        ->eat(getBugsInCell(bug->getPosition()));
    }

    displayAll(true);

    cout << endl;
}

Bug* Board::getLargestBugInCell(pair<int, int> position) {
    vector<Bug*> targetBugs = getBugsInCell(position);
    Bug* biggestBug = targetBugs.front(); // Pick an arbitrary bug

    //https://www.geeksforgeeks.org/cpp-program-to-find-largest-among-three-numbers/
    for(Bug* bug: targetBugs) {
        if(bug != biggestBug) { // No point in comparing the biggest bug to itself
            if(biggestBug->getSize() < bug->getSize())
                biggestBug = bug;
            else if (biggestBug->getSize() == bug->getSize()) // A random bug will be chosen between the two
                biggestBug = (rand()%2 == 2) ? biggestBug : bug;
        }
    }

    return biggestBug;
}

// Output stream may be swapped to file output for exit()
// set to cout by default
void Board::displayAllPathHistory(ostream& stream) {
    for(Bug* bug: bugs) {
        stream << bug->getType() << " ID " << to_string(bug->getId()) << " ALIVE: " << bug->isAlive() << endl;
        for (pair<int,int> position: bug->getPath()) {
            stream << pair_to_string(position) << endl;
        }
        stream << endl;
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

// Run with SFML graphics
void Board::runSimulation(thread t) {
    // Runs identically, only now the thread executes SFML.
    runSimulation();
}

void Board::runSimulation() {
    int turns = 0;

    // Duplicate the vector
    vector<Bug*> livingBugs = bugs;

    while (livingBugs.size() > 1) { // There is more than one living bug
        turns++;
        cout << "Turn " << turns << endl << "=================" << endl;
        tapBoard();

        // Clear the old positions from the grid
        sfmlClearGrid();

        for(Bug* bug: livingBugs) {
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
    // Get time as a string.
    std::stringstream ss;

    //https://cplusplus.com/reference/iomanip/put_time/?kw=put_time
    using chrono::system_clock;
    std::time_t tt = system_clock::to_time_t (system_clock::now());

    struct std::tm * ptm = localtime(&tt);

    // Place time into string
    ss << put_time(ptm, "%b-%d_%H-%M");

    // Convert string stream into string and add to filename
    ofstream fout("bugs_life_history_" + ss.str() + ".txt");

    // Record path history to file
    displayAllPathHistory(fout);

    fout.close();
}

// Static method to convert pair to string
string Board::pair_to_string(pair<int,int> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
};

void Board::sfmlInitialiseGrid() {
    const int size = 40;

    // Cells on an 9 x 9 grid
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            // Create a rectangle shape cell. X and Y are set to 5. Maybe referring to size?
            sf::RectangleShape cell(sf::Vector2f(size, size));

            // After creating the cell set it there
            cell.setPosition(x * size, y * size);

            // If I want to make the grid visible I can try this..
            // The green cubes 4 times larger than our grid.
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);

            // Cells are added to the vector
            sfmlSquares.push_back(cell);
        }
    }
}

void Board::sfmlDrawGrid() {
    // Opens a window, setting the width and the height.
    sf::RenderWindow window(sf::VideoMode(400, 400), "BugLife");

    auto* super = dynamic_cast<Super*>(findBugById(999));
    sfmlInitialiseGrid();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if X is pressed
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased) {
                // 40 units makes
                if (event.key.code == sf::Keyboard::Up) {
                    if (super->getY() > 0)
                        super->adjustY(-1);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    if (super->getY() < 9)
                        super->adjustY(1);
                }
                if (event.key.code == sf::Keyboard::Left) {
                    if (super->getX() > 0)
                        super->adjustX(-1);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    if (super->getX() < 9)
                        super->adjustX(1);
                }
            }

            sfmlClearGrid();
        }

        // This will draw the graphics.
        window.clear(sf::Color::White);
        for (sf::RectangleShape sh: sfmlSquares) {
            window.draw(sh);
        }
        window.display();

        sfmlDrawBugs(bugs);
    }
}

// Show bugs on the grid
void Board::sfmlDrawBugs(vector<Bug*>& targetBugs) {
    // Check each bug's position.
    for (Bug *bug: targetBugs) {
        if(bug->isAlive()) { // Save time by skipping dead bugs
            pair<int, int> p = bug->getPosition();

            // Check every square on the grid
            // Each square is 40 units apart.
            // So a bug at (1, 1) will be a square at (40, 40)
            for (sf::RectangleShape &sq: sfmlSquares) {
                if (p.first * 40 == sq.getPosition().x
                    && p.second * 40 == sq.getPosition().y) {
                    sq.setFillColor(bug->getSfmlColor());
                }
                //cout << "(" << p.first * 40 << ", " << p.second * 40 <<
                //     ") And square is " << "(" << sq.getPosition().x << ", " << sq.getPosition().y << endl;
            }
        }
    }
}

void Board::sfmlClearGrid() {
    // Check every square on the grid
    for (sf::RectangleShape &sq: sfmlSquares) {
        // If there is no bug on the cell, make it transparent
        if(getBugsInCell(make_pair(sq.getPosition().x, sq.getPosition().y)).empty())
        sq.setFillColor(sf::Color::Transparent);
    }
}