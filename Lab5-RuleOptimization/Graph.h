#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <stack>
#include <vector>

#include "Node.h"

class Graph {
   private:
    std::map<int, Node> nodes;
    std::stack<int> topologicalSort;
    std::vector<std::set<int>> sCCs;

   public:
    Graph() {}
    void addNodes(int numNodes) {
        for (int i = 0; i < numNodes; i++) {
            addNode();
        }
    }
    void addNode() {
        Node newNode;
        nodes.insert(std::make_pair(nodes.size(), newNode));    // key: id (ascending from 0), value: Node
        nodes[nodes.size() - 1].setId(nodes.size() - 1);    // set Node id equal to key
    }
    bool isMapNodeSelfDependent(int nodeId) {
        return nodes[nodeId].getIsSelfDependent();
    }
    void addEdge(int from, int to) {
        nodes[from].addAdjacentNode(to);
    }
    void getPostorderDFS(Node& n) {
        n.setBeenVisited(true);
        for (auto adjacentNode : n.getAdjacentNodes()) {
            if (nodes.at(adjacentNode).getBeenVisited() == false) {
                getPostorderDFS(nodes.at(adjacentNode));
            }
        }
        topologicalSort.push(n.getId());
    }
    std::stack<int> getPostorderDFSForest() {
        for (auto& node: nodes) {
            if (node.second.getBeenVisited() == false) {
                getPostorderDFS(node.second);
            }
        }
        return topologicalSort;
    }
    std::set<int> findSCCsDFS(Node& n) {
        n.setBeenVisited(true);
        std::set<int> tempSSC;
        for (auto adjacentNode : n.getAdjacentNodes()) {
            if (nodes.at(adjacentNode).getBeenVisited() == false) {
                std::set<int> tempPartialSSC = findSCCsDFS(nodes.at(adjacentNode));
                tempSSC.insert(tempPartialSSC.begin(), tempPartialSSC.end());
            }
            if (nodes.at(adjacentNode).getId() == n.getId()) {
                n.setIsSelfDependent(true);
            }
        }
        tempSSC.insert(n.getId());
        return tempSSC;
    }
    std::vector<std::set<int>> findSCCsDFSForest(std::stack<int> postorder) {
        while (!postorder.empty()) {
            int startingNode = postorder.top();
            postorder.pop();
            if (nodes.at(startingNode).getBeenVisited() == false) {
                sCCs.push_back(findSCCsDFS(nodes.at(startingNode)));
            }
        }
        return sCCs;
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
