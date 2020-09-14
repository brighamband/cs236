#include <iostream>
#include <fstream>
#include <string>
#include "Token.h"
using namespace std;

int main(int argc, char *argv[])
{

    string filename = argv[1];
    cout << "filename: " << filename << endl;
    ifstream in(argv[1]);

    string firstVal = "dd";
    string secondVal = "";
    string thirdVal = "";
    string fourthVal = "";

    in >> firstVal;
    cout << "firstVal: " << firstVal << endl;
    in >> secondVal;
    cout << "secondVal: " << secondVal << endl;
    in >> thirdVal;
    cout << "thirdVal: " << thirdVal << endl;
    in >> fourthVal;
    cout << "fourthVal: " << fourthVal << endl;

    // string inputString = "";
    // while (in)
    // {
    //     in >>
    // }

    // Token testToken("testing", "test", 1);
    Token testToken(COMMA, "test", 1);
    cout << testToken.toString();

    // if (!in)
    // {
    //     cerr << "Reached end of file." << endl;
    // }

    return 0;
}