#include "dgraph.h"
#include "constants.h"

#include <utility>

DGraph::DGraph() {}

void DGraph::addChild(int parent, int child) {
    if (this->nodes.find(parent) == this->nodes.end()) {
        std::set<int> children;
        this->nodes.insert(std::pair<int, std::set<int>> (parent, children));
    }
    this->nodes[parent].insert(child);
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

int DGraph::numNodes() {
    return getNodes().size();
}

int DGraph::_dfs(int p, std::vector<int> &v, std::vector<int> &s) {
    if (v[p] == 0) {
        v[p] = 1;
        s[p] = 1;

        auto it = this->nodes[p].begin();
        for (; it != this->nodes[p].end(); ++it) {
            if (!v[*it] && _dfs(*it, v, s)) {
                return 1;
            } else if (s[*it] == 1) {
                return 1;
            }
        }
    }
    s[p] = 0;
    return 0;
}

int DGraph::dfs() {
    this->num_nodes = this->numNodes();
    if (this->num_nodes == 0) {
        return 0;
    }
    std::vector<int> visited(this->num_nodes, 0);
    std::vector<int> stack(this->num_nodes, 0);
    return _dfs(0, visited, stack);
}

int DGraph::_isFullyVisited(std::vector<int> &visited) {
    for (int node = 0; node < this->num_nodes; node++) {
        if (visited[node] == 0) {
            return NOT_FULLY_VISITED;
        }
    }
    return FULLY_VISITED;
}

int DGraph::isFullyVisited() {
    this->num_nodes = this->numNodes();
    if (this->num_nodes == 0) {
        return FULLY_VISITED;
    }
    std::vector<int> visited(this->num_nodes, 0);
    std::vector<int> stack(this->num_nodes, 0);
    _dfs(0, visited, stack);
    return _isFullyVisited(visited);
}

int DGraph::isCyclic() {
    return (dfs() == 1) ? CYCLIC : NOT_CYCLIC;
}

/*
void DGraph::print_DGraph() {
    std::unordered_map<int,std::set<int>>::iterator it_map = this->nodes.begin();
    for (;it_map != this->nodes.end(); ++it_map ) {
        std::cout << "NODE " << it_map->first << ": ";
        for (auto it = it_map->second.begin(); it != it_map->second.end(); ++it){
            std::cout << *it <<"-";
        }
        std::cout << "\n";
    }
}
*/

DGraph::~DGraph() {}
