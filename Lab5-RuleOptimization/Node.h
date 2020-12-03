#ifndef NODE_H
#define NODE_H

#include <set>

class Node {
   private:
    int id;
    std::set<int> adjacentNodes;
    bool beenVisited = false;
    bool isSelfDependent = false;

   public:
    Node() {}
    void setId(int identifier) {
        id = identifier;
    }
    int getId() const {
        return id;
    }
    void addAdjacentNode(int newNode) {
        adjacentNodes.insert(newNode);
    }
    std::set<int> getAdjacentNodes() const {
        return adjacentNodes;
    }
    void setBeenVisited(bool b) {
        beenVisited = b;
    }
    bool getBeenVisited() const {
        return beenVisited;
    }
    std::string toString() {
        std::string nodeStr = "R" + to_string(id) + ":";
        for (std::set<int>::iterator iter = adjacentNodes.begin(); iter != adjacentNodes.end(); iter++) {
            if (iter != adjacentNodes.begin()) {
                nodeStr += ",";
            }
            nodeStr += "R" + to_string(*iter);
        }
        return nodeStr;
    }
};

#endif
