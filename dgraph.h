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
        int addChild(int parent, int child);
        int isCyclicDfs(int s);
        // void print_DGraph();
        int cantNodes();
        ~DGraph();
 private:
        std::set<int> getNodes();
        int _isCyclicDfs(int p, std::vector<int>* v, std::vector<int>* s);
        std::unordered_map<int, std::set<int>> nodes;
        int cant_nodes = 0;
};

#endif  // DGRAPH_H_
