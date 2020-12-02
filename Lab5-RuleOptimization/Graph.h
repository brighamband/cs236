#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <stack>
#include <vector>

#include "Node.h"

// Nodes - do you need an id if you have the key int?
// How do i construct the dependency graph w/o doing dfs?  Do i do that in the interpreter?

class Graph {
   private:
    std::map<int, Node> nodes;
    std::stack<int> topologicalSort;
    std::vector<std::set<int>> sCCs;

   public:
    Graph() {}
    Graph(int numNodes) {
        for (int i = 0; i < numNodes; i++) {
            addNode();
        }
    }
    void addNode() {
        Node newNode;
        nodes.insert(std::make_pair(nodes.size(), newNode));    // key: id (ascending from 0), value: Node
        nodes[nodes.size() - 1].setId(nodes.size() - 1);    // set Node id equal to key
    }
    void addEdge(int from, int to) {
        nodes[from].addAdjacentNode(to);
    }
    void dFS(Node n) {}
    // find the post-order
    void dFSForestPostorder() {
        //        for(auto node: reverse_graph){
        //            if(node.second.visited == false)
        //                dfs(node.first);
        //        }
    }
    // find the SCCs - which were visited
    void dFSForestSCCs() {
        //        for (int i = 0; i < ; ++i) {
        //            dFS()
        //        }
    }
    std::string toString() {
        std::string graphStr = "Dependency Graph\n";
        for (auto& [key, value] : nodes) {
//            graphStr += "key:" + to_string(key) + "\n";
            graphStr += value.toString() + "\n";
        }
        return graphStr;
    }
};

#endif
