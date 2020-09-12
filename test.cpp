#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
COMMAND #1       g++ -Wall -Werror -std=c++17 -g *.cpp -o out
Compile file with max error checking, create out executable

COMMAND #2 :     ./out input.txt  (or name of input file)
Run executable and pass in the file as input
*/

int main(int argc, char *argv[])
{

    string filename = argv[1];
    cout << "filename: " << filename << endl;
    ifstream in(argv[1]);

    string firstVal = "";
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
    if (!in)
    {
        cerr << "Reached end of file." << endl;
    }

    return 0;
}