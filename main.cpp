#include <iostream>
#include <vector>
#include <fstream>

#include "Bug.cpp"
#include "Crawler.cpp"
#include "Hopper.cpp"

vector<Bug*> initBugsFromFile(ifstream&);
void displayAll(vector<Bug*>&);
string readNext();

int main() {
    std::cout << "Hello, World!" << std::endl;
    ifstream fin("bugs.txt");
    vector<Bug*> vect = initBugsFromFile(fin);
    displayAll(vect);
    return 0;
}

struct {
    int delimiter_i;
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
            }

            bugs.push_back(bug_ptr);
        }
    }

    return bugs;
};

string readNext() {
    tokenData.token = tokenData.readin.substr(0, tokenData.readin.find(";"));
    //cout << "token: " << tokenData.token << endl;
    tokenData.readin = tokenData.readin.substr(tokenData.readin.find(";")+1);
    //cout << "readin: " << tokenData.readin << endl;

    return tokenData.token;
}

void displayAll(vector<Bug*>& bugs) {
    cout << "ID\t" << "Type\t" << "Position\t" << "Direction\t" << "Size\t" << "HopLength" << endl;

    for(auto & bug : bugs) {
        cout << bug->toString() << endl;
    }
};