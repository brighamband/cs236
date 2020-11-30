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
    std::vector<std::set<int>> sCCs;

   public:
    Graph() {}
    void addNode(Node newNode) {
        nodes.insert(std::make_pair(nodes.size(), newNode));
    }
    void dFS(Node n) {}
    // find the post-order
    void dFSForestPostorder() {
        // TODO - Implement pseudocode
    }
    // find the SCCs - which were visited
    void dFSForestSCCs() {
        //        for (int i = 0; i < ; ++i) {
        //            dFS()
        //        }
    }
    void addEdge(int from, int to) {
    }
    std::string toString() {
        std::string graphStr = "Dependency Graph\n";
        for (auto& [key, value] : nodes) {
            graphStr += value.toString() + "\n";
        }
        return graphStr;
    }
};

#endif
