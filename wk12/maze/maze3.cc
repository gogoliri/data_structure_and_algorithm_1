#include <iterator>
#include <vector>
#include <algorithm>
#include "maze.hh"

using namespace std;

// Remember to implement your own container here or in another cc file to store the nodes in the maze
// If you define it elsewhere, remember to make sure it's accessible by this file as well.


/**
 * @brief Connect two adjacent nodes together. If the nodes are not adjacent, do nothing
 * 
 * @param fromNode  The node to connect from
 * @param toNode  The node to connect to
 */
void connectNodes(Node& node1, Node& node2) {
    auto xy1 = node1.coord;
    auto xy2 = node2.coord;

    if(xy1.first == xy2.first and (xy1.second - xy2.second == 1)){
        node1.paths[BELOW] = &node2;
        node2.paths[ABOVE] = &node1;
     }else if(xy1.first == xy2.first and (xy1.second - xy2.second == -1)){
        
        node1.paths[ABOVE] = &node2;
        node2.paths[BELOW] = &node1;
     }else if(xy1.second == xy2.second and (xy1.first - xy2.first == 1)){
        
        node1.paths[LEFT] = &node2;
        node2.paths[RIGHT] = &node1;
     }else if(xy1.second == xy2.second and (xy1.first - xy2.first == -1)){
        
        node1.paths[RIGHT] = &node2;
        node2.paths[LEFT] = &node1;
     }
    

}
