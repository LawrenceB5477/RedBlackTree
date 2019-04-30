#include <iostream>
#include "Node.h"
#include "RedBlackTree.h"
#include <vector>

using std::cout;
using std::endl;
using std::getline;
using std::vector;
using std::string;

vector<string> *split(string str) {
    auto vec = new vector<string>;
    size_t pos = 0;
    while ((pos = str.find(' ')) != string::npos) {
        vec->push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
    }
    vec->push_back(str);
    return vec;
}

void errorMsg() {
    cout << "The input you entered is invalid. Try again." << endl;
}

void insertNode(string str, RedBlackTree &rb) {
    try {
        int input = std::stoi(str);
        cout << "Attempting to insert: " << input << endl << endl;
        rb.insert(input);
        cout << rb << endl;
    } catch (std::invalid_argument &e) {
        errorMsg();
    }
}

void removeNode(string str, RedBlackTree &rb) {
    try {
        int input = std::stoi(str);
        cout << "Attempting to remove: " << input << endl << endl;
        rb.remove(input);
        cout << rb << endl;
    } catch (std::invalid_argument &e) {
        errorMsg();
    }
}

int main() {
    cout << "Welcome to the red black tree simulator. Type 'E' to exit. " << endl;
    cout << "To insert a node, use 'i <integer>'" << endl;
    cout << "To remove a node, use 'r <integer>'" << endl << endl;

    RedBlackTree rb;

    while (true) {
        string input;
        cout << "Enter a command: ";
        getline(std::cin, input);
        auto tokens = split(input);

        if (tokens->at(0) == "e" || tokens->at(0) == "E") {
            break;
        } else {
            string command = tokens->at(0);
            if (command == "i" || command == "I") {
                insertNode(tokens->at(1), rb);
            } else if (command == "r" || command == "R") {
                removeNode(tokens->at(1), rb);
            } else {
                errorMsg();
            }
        }

        delete tokens;
    }
    cout << "Exiting... " << endl;
    return 0;
}