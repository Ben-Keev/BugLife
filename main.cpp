#include <iostream>
#include <vector>
#include <fstream>

#include "Bug.cpp"
#include "Crawler.cpp"
#include "Hopper.cpp"

vector<Bug*> initBugsFromFile(ifstream&);
void displayAll(vector<Bug*>&);
string readNext();
Bug* findBug(vector<Bug*>&);
void tapBoard(vector<Bug*>&);
void displayAllPathHistory(vector<Bug*>&);
string pair_to_string(pair<int,int>);

int main() {
    // Initialise random seed https://en.cppreference.com/w/cpp/numeric/random/srand
    srand(time(0));

    ifstream fin("bugs.txt");
    vector<Bug*> vect = initBugsFromFile(fin);

    displayAll(vect);

    for(int i=0; i < 8; i++) {
        tapBoard(vect);
    }

    displayAllPathHistory(vect);

    displayAll(vect);
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
            };

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

void displayAll(vector<Bug*>& bugs) {
    cout << "ID\t" << "Type\t" << "Position\t" << "Direction\t" << "Size\t" << "HopLength" << endl;

    for(auto & bug : bugs) {
        cout << bug->toString() << endl;
    };
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
    return nullptr;
};

void tapBoard(vector<Bug*>& bugs) {
    for(Bug* bug: bugs) {
        bug->move();
    };
};

void displayAllPathHistory(vector<Bug*>& bugs) {
    for(Bug* bug: bugs) {
        cout << "BUG ID " << to_string(bug->getId()) << endl;
        for (pair<int,int> position: bug->getPath()) {
            cout << pair_to_string(position) << endl;
        }
        cout << endl;
    };

};

string pair_to_string(pair<int,int> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}