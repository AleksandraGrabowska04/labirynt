#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "../mazemap.h"
#include "../graph.h"

//change 0 to STARTING_NODE later?

//later: divide some additional parts of the code into the functions (like getting heuristic (expected from node x to goal node distance) x node score) - I usually move the main algorithm to the separate function after it works completely.

int main(){

    MazeMap lab("maze.txt");
    MazeGraph grph = lab.ToMazeGraph();
    grph.Print();
    
    std::set<int> visited_nodes; //indicies of already visited maze nodes.
    std::set<int> unvisited_nodes; //indicies of unvisited maze nodes (nodes neighbouring to the current node).
    std::set<int> adjacent_nodes; // (completely replace unvisited_nodes vector with use of it?)
    //moze dac tu jeszcze cos w stylu complete_nodes ???
    unvisited_nodes.insert(0);
    adjacent_nodes.insert(0);
    std::map<int, int> g_score; //g(x) score which is distance (amount of edges (in this case without edges' weights)) between
    //nodes from the start up to the point n (where n can be a "start" node as well). (function can 
    //othwerwise be described as: "how many moves in order to get to the node n from the starting node").
    //first value is node index, second value is g_score (g(x)).
    g_score.insert(0, 0); //g_score (distance) for 0 (starting point) is 0 (which is logical).
    std::map<int, int> h_score; //describe this later (heuristics score (h(x))).
    h_score.insert(0, lab.GetMazeWidth()+lab.GetMazeHeight());

    int x = 0; //describe this later: node with the lowest f(x) (heuristics) score (?)
    //can rename it as current_node or something like "currently checked node"...

    //not forget about goal/objective node.

    int tentative_g_score = 0; //tentative's (currently checked/tried) path's g_score.
    bool is_tentative_better;

    //!currently writing the algorithm's logic

    while(!unvisited_nodes.empty()){

        //x = find node with the lowest f(x).

        //if(x == goal) reconstruct_path();

        for(int node_index : grph.GetAdjacentNodeIndicies(x))//adds neighbouring nodes of current node to unvisted_nodes set.
            adjacent_nodes.insert(node_index);

        adjacent_nodes.erase(x);
        visited_nodes.insert(x);

        for(int adjacent_node : adjacent_nodes){ //don't blend the unvisited nodes with adjacent nodes!!! Because node can be adjacent to other node that has been visited already

            if(visited_nodes.find(adjacent_node) != visited_nodes.end())
                continue;
            
            tentative_g_score = g_score[x] + 1;
            is_tentative_better = false;

            if(visited_nodes.find(adjacent_node) != visited_nodes.end()){}

            //h_score = get heuristics score.
            //is_tentative_better = true; ?

            else if(tentative_g_score < g_score[adjacent_node]){}

            //it does make sense now that I think about it, because it checks all possibilities for currently considered node (node x) and *only then* adds it to closedset/visited_nodes

            if(is_tentative_better){}
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