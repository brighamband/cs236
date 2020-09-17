#include <fstream>
#include <iostream>
#include <string>

#include "Lexer.h"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Please provide the name of input file.";
        return 1;
    }

    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 1;
    }

    string line = "";
    string inputString = "";
    Lexer lexer;

    while (getline(in, line)) {
        inputString += line + "\n";
    }

    lexer.run(inputString);
    cout << lexer.toString();

    return 0;
}