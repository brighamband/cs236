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
    int getSize() const {
        return names.size();
    }
    std::string getName(size_t index) const {
        return names.at(index);
    }
    std::string toString() const {
        std::string headerStr = "";
        for (size_t i = 0; i < names.size(); i++) {
            if (i > 0) {
                headerStr += ", ";
            }
            headerStr += names.at(i);
        }
        return headerStr;
    }
};

#endif