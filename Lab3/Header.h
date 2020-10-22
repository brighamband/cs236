#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>

class Header {
   private:
    std::vector<std::string> names;

   public:
    Header() {}
    Header(std::vector<std::string> n) {
        names = n;
    }
    std::string toString() const {  // FOR DEBUGGING ONLY - USE RELATION TOSTRING IN ACTUAL OUTPUT
        std::string headerStr = "";
        for (int i = 0; i < names.size(); i++) {
            headerStr += "-" + names.at(i);
        }
        return headerStr;
    }
};

#endif