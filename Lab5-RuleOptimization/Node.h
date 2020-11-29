#ifndef NODE_H
#define NODE_H

#include <set>

class Node {
   private:
    int id;
    std::set<int> adjacent;
    bool beenVisited = false;
    bool isSelfDependent = false;

//   public:
};

#endif
