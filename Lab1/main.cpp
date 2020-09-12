#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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