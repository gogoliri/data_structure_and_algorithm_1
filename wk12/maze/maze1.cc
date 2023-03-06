#include <iterator>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <iostream>
#include "maze.hh"

using namespace std;

// Remember to implement your own container here or in another cc file to store the nodes in the maze
// If you define it elsewhere, remember to make sure it's accessible by this file as well.

/**
 * @brief Create a Node object
 * 
 * @param loc  The location of the node
 * @return Node*  A pointer to the node that is created. If the node already exists, return a pointer to the existing node
 */
std::map<std::pair<int, int>, Node*> node_container;
Node* createNode  (std::pair<int, int> loc, std::map<std::string, Node*> paths) {
    auto p = node_container.find(loc);
    if(p != node_container.end()){
        return p->second;
    }
    Node* new_node = new Node;
    new_node->coord = loc;
    new_node->paths = paths;
    node_container[loc]= new_node;
    return new_node;
}
