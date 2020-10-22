#ifndef TUPLE_H
#define TUPLE_H

#include <string>
#include <vector>

class Tuple {
   private:
    std::vector<std::string> values;

   public:
    // Tuple(string paramVal) {
    //     value = paramVal;
    // }
    bool operator<(const Tuple other) const {
        return values < other.values;  // compare this Tuple to other Tuple
    }
    std::string toString() const {
        std::string tupleStr = "";
        for (int i = 0; i < values.size(); i++) {
            tupleStr += "-" + values.at(i);
        }
        return tupleStr;
    }
};

#endif