#ifndef TUPLE_H
#define TUPLE_H

#include <string>
#include <vector>

class Tuple {
   private:
    std::vector<std::string> values;

   public:
    Tuple() {}
    Tuple(std::vector<std::string> v) {
        values = v;
    }
    bool operator<(const Tuple& other) const {
        return values < other.values;
    }
    std::string getValue(size_t index) const {
        return values.at(index);
    }
    std::string toString() const {
        std::string tupleStr = "";
        for (size_t i = 0; i < values.size(); i++) {
            if (i > 0) {
                tupleStr += ", ";
            }
            tupleStr += values.at(i);
        }
        return tupleStr;
    }
};

#endif