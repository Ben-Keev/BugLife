#include "Board.h"

int main() {
    // Initialise random seed https://en.cppreference.com/w/cpp/numeric/random/srand
    srand(time(0));

    Board* board = new Board();

    // Multi-Line String https://stackoverflow.com/a/1135862
    const char *menu =
            "1. Initialise Bug Board (Load Data From File)\n"
            "2. Display All Bugs\n"
            "3. Find a Bug by ID\n"
            "4. Tap the Bug Board\n"
            "5. Display Life History of All Bugs\n"
            "6. Display All Cells\n"
            "7. Run Simulation\n"
            "8. Exit\n"
            "9. Run Simulation with SFML";

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
                board->initBugsFromFile(fin);
                break;
            }

            case 2: { // Display all bugs
                board->displayAll();
                break;
            }

            case 3: { // Find a bug
                board->findBugById();
                break;
            }

            case 4: { // Tap the board
                board->tapBoard();
                break;
            }

            case 5: {
                board->displayAllPathHistory();
                break;
            }

            case 6: {
                board->displayAllCells();
                break;
            }

            case 7: {
                board->runSimulation();
                break;
            }

            case 8: {
                board->exit();
                running = false;
                break;
            }

            case 9: {
                board->runSimulation(std::thread(&Board::sfmlDrawGrid, board));
                break;
            }

            default: {
                cout << "Invalid input. Try again" << endl;
            }
        }
    }

    return 0;
};