#ifndef TUPLE_H
#define TUPLE_H

#include <string>
#include <vector>
using namespace std;

class Tuple {
   private:
    string<vector> valuesVctr;

   public:
    // Tuple(string paramVal) {
    //     value = paramVal;
    // }
    bool operator<(const Tuple& other) const {
        // compare this Tuple to other Tuple
    }
    // void setValue(string paramVal) {
    //     value = paramVal;
    // }
    // string toString() const {
    //     return value;
    // }
};

#endif