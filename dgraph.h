#ifndef DGRAPH_H_
#define DGRAPH_H_

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <unordered_map>
#include <vector>

class DGraph {
 public:
        DGraph();
        void addChild(int parent, int child);
        int isCyclic();
        int isFullyVisited();
        int dfs();
        //void print_DGraph();
        int numNodes();
        ~DGraph();
 private:
        std::set<int> getNodes();
        int _dfs(int p, std::vector<int> &v, std::vector<int> &s);
        int _isFullyVisited(std::vector<int> &visited);
        std::unordered_map<int, std::set<int>> nodes;
        int num_nodes = 0;
};

#endif    // DGRAPH_H_
