#include "dgraph.h"
#include <utility>

enum TypeInstructions { NOT_CYCLIC = 0, CYCLIC = 1, UNSTACKED = 2};

DGraph::DGraph() {}

int DGraph::addChild(int parent, int child) {
    if (this->nodes.find(parent) == this->nodes.end()) {
        std::set<int> children;
        this->nodes.insert(std::pair<int, std::set<int>> (parent, children));
    }
    this->nodes[parent].insert(child);
    return 0;
}


std::set<int> DGraph::getNodes() {
    std::set<int> nodes;
    std::unordered_map<int, std::set<int>>::iterator it_map;
    it_map = this->nodes.begin();
    for (; it_map != this->nodes.end(); ++it_map) {
        nodes.insert(it_map->first);
        auto it = it_map->second.begin();
        for (; it != it_map->second.end(); ++it) {
            nodes.insert(*it);
        }
    }
    return nodes;
}


int DGraph::cantNodes() {
    return getNodes().size();
}

int DGraph::_isCyclicDfs(int p, std::vector<int>* v, std::vector<int>* s) {
    if ((*v)[p] == 0) {
        (*v)[p] = 1;
        (*s)[p] = 1;

        auto it = this->nodes[p].begin();
        for (; it != this->nodes[p].end(); ++it) {
            if (!(*v)[*it] && _isCyclicDfs(*it, v, s)) {
                return 1;
            } else if ((*s)[*it] == 1) {
                return 1;
            }
        }
    }
    (*s)[p] = 0;
    return 0;
}

int DGraph::isCyclicDfs(int s) {
    this->cant_nodes = this->cantNodes();
    std::vector<int> visited;
    std::vector<int> stack;

    for (int i = 0; i < this->cant_nodes; i++) {
        visited.push_back(0);
        stack.push_back(0);
    }

    int res = this->_isCyclicDfs(0, &visited, &stack);

    if (res == 1) {
        return CYCLIC;
    }

    for (int node = 0; node < this->cant_nodes; node++) {
        if (visited[node] == 0) {
            return UNSTACKED;
        }
    }
    return NOT_CYCLIC;
}

/*
void DGraph::print_DGraph() {
    std::unordered_map<int,set<int>>::iterator it_map = this->nodes.begin();
    for (;it_map != this->nodes.end(); ++it_map ) {
        std::cout << "NODE " << it_map->first << ": ";
        for (auto it = it_map->second.begin(); it != it_map->second.end(); ++it){
            cout << *it <<"-";
        }
        cout << "\n";
    }
}
*/

DGraph::~DGraph() {}
