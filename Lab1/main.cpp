#include <fstream>
#include <iostream>
#include <string>

#include "Lexer.h"
#include "Token.h"
using namespace std;

int main(int argc, char *argv[]) {
    // Error checking for opening input file

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

    while (!in.eof()) {
        getline(in, line);
        inputString += line + "\n";
    }

    // cout << "inputString: " << inputString << endl;

    // Token testToken(END_OF_FILE, "test", 1);
    // cout << testToken.toString();

    lexer.run(inputString);
    cout << lexer.toString();

    return 0;
}