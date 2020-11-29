#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <stack>
#include <vector>

class Graph {
   private:
    std::map<int, Node> nodes;
    std::stack<int> topologicalSort;
    std::vector<std::set<int>> sCComponents;

   public:
    void dFS(Node n) {}
    void dFSForest() {}
    void addEdge(int from, int to) {}
};

#endif
