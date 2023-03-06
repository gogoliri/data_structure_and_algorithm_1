#include <iterator>
#include <vector>
#include <algorithm>
#include <set>
#include "maze.hh"
#include <queue>
using namespace std;

// Remember to implement your own container here or in another cc file to store the nodes in the maze
// If you define it elsewhere, remember to make sure it's accessible by this file as well.


/**
 * @brief Find the shortest path from startNode to endNode using Djikstra's algorithm, where all path distances are 1
 * @param startNode  The node to start the search from
 * @param endNode  The node to end the search at
 * @param path  The path from startNode to endNode. If no path is found or if startNode is the same as endNode, 
 * path should be empty. The path should be in the order of the nodes visited, starting with startNode and ending with endNode
 * @return bool True if a path was found, false otherwise
 */

bool findShortestPath(Node &startNode, Node &endNode, std::vector<std::pair<int, int>>& path) {
    if(&startNode == &endNode){return true;}

    std::map<Node*, Node*> child_parent; 
    queue<Node*> Q; 
    std::set<Node*> visited; 
    
    // Initialize for source node
    child_parent[&startNode] = nullptr;
    visited.insert(&startNode);
    Q.push(&startNode);
    
    Node* current_node = nullptr;
    while (Q.size() != 0){
        current_node = Q.front();
        Q.pop();
        if(current_node == &endNode){break;}
        
        for(auto adj: current_node->paths)
        {   
            
            auto next = adj.second;
            if(next != nullptr){
                if(visited.find(next) == visited.end())
                {
                    visited.insert(next);
                    child_parent[next] = current_node;
                    Q.push(next);
                }
            }
        }
    }
    if(current_node != &endNode){return false;}
    while(current_node != nullptr)
    {
        path.push_back(current_node->coord);
        current_node = child_parent[current_node];
    }

    std::reverse(path.begin(), path.end());
    
    if(path.empty()){return false;}
    return true;
    // End of student code
}
