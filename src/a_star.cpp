#include <iostream>
#include <vector>
#include <set>
#include "mazemap.h"
#include "graph.h"

//change 0 to STARTING_NODE later?

int main(){

    MazeMap lab("maze.txt");
    MazeGraph grph = lab.ToMazeGraph();
    grph.Print();
    
    std::set<int> visited_nodes; //indicies of already visited maze nodes.
    std::set<int> unvisited_nodes; //indicies of unvisited maze nodes (nodes neighbouring to the current node).
    unvisited_nodes.insert(0);
    std::vector<int> g_score; //g(x) score which is distance (amount of edges (in this case without edges' weights)) between
    //nodes from the start up to the point n (where n can be a "start" node as well). (function can 
    //othwerwise be described as: "how many moves in order to get to the node n from the starting node").
    g_score.push_back(0); //g_score[0] = 0 (which is logical). //it should much rather be key-value pair instead - Do this later.

    int x = 0; //describe this later: node with the lowest f(x) (heuristics) score (?)
    //can rename it as current_node or something like "currently checked node"...

    //not forget about goal/objective node.

    int tentative_g_score = 0; //tentative's (currently checked/tried) path's g_score.

    //!currently writing the algorithm's logic

    while(!unvisited_nodes.empty()){

        //x = find node with the lowest f(x).

        //if(x == goal) reconstruct_path();

        for(int node_index : grph.GetAdjacentNodeIndicies(x))//adds neighbouring nodes of current node to unvisted_nodes set.
            unvisited_nodes.insert(node_index);

        unvisited_nodes.erase(x);
        visited_nodes.insert(x);

        for(int unvisited_node : unvisited_nodes){

            if(visited_nodes.find(unvisited_node) != unvisited_nodes.end())
                continue;
            
            //tentative_g_score =
        }
    }

    //was used for testing:
    /*std::vector<int> indicies;

    indicies = grph.GetAdjacentNodeIndicies(0);
    
    for(auto node : indicies){
        std::cout << "node index: " << node << ' ' << grph.GetGraphNode(node)->x << ' ' << grph.GetGraphNode(node)->y << '\n';
    }*/

    return 0;
}