#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <climits>
#include "../mazemap.h"
#include "../graph.h"
#include "algorithms.h"


//change 0 to STARTING_NODE later?

//later: divide some additional parts of the code into the functions (like getting heuristic (expected from node x to goal node distance) x node score) - I usually move the main algorithm to the separate function after it works completely.

int lowest_f_score(std::map<int, int>& f_score, std::set<int>& discovered_nodes){
//finds the lowest f_score from all nodes in the "discovered nodes" set.
    int lowest_f_score = INT_MAX;
    int lowest_score_node; //lowest f_score node index (index of node with the lowest f_score value assigned to it).
    for(int node : discovered_nodes){
        if(f_score[node] < lowest_f_score){
            lowest_f_score = f_score[node];
            lowest_score_node = node;
        }
    }
    return lowest_score_node;
}

std::vector<int> reconstruct_path(std::map<int, int>& came_from, int goal_node_index, MazeGraph& graph){

    std::vector<int> reversed_node_path; //order is reversed because of adding (pushing back) elements onto a/the "stack" (vector) - maybe solve this better later.
    std::vector<int> ordered_path; //properly ordered path.
    reversed_node_path.push_back(goal_node_index);
    int current_node = goal_node_index; //a currently checked node index.

    while(came_from[current_node] != -1){

        current_node = came_from[current_node]; //assigns index of node from the previous step of "the cheapest" path into the current_node.
        reversed_node_path.push_back(current_node); //adds index of the current node to the end of the path vector.

    }

    /*for(int i = path.size()-1; i > -1; i--){
        std::cout << path[i].x << ' ' << path[i].y << '\n';
    }*/

    //properly ordering the full node labyrinth solution path (reconstructing the proper path).
    for(int i = reversed_node_path.size()-1; i > -1; i--){
        ordered_path.push_back(reversed_node_path[i]);
    }

    return ordered_path;

}

int heuristic_estimation(int x, MazeGraph& graph, MazeMap& lab){ //heuristic estimation of distance from x node to the goal node.

    int heuristic_distance = //heuristically estimated distance.
    (lab.GetMazeHeight() - 2) - graph.GetGraphNode(x)->x
    + (lab.GetMazeWidth() - 2) - graph.GetGraphNode(x)->y;

    return heuristic_distance;

    //solve this better later. Instead of setting up coords, kinda like "magic numbers", because we only literally *know* where that (goal point) is,
    //instead do one of these:
    //a. at least do some macros for GOAL_NODE and/or obtaining it's value
    //b. write separate function for this
    //c. write method for it (like: getGoalNode) inside "graph.cpp" (The MazeGraph's class/data structure file) or some similar solution.
}

std::vector<int> Algorithms::a_star(MazeMap& lab, MazeGraph& graph, int startNode, int endNode, std::vector<int>& visitOrder){

    //MazeMap lab("../maze.txt"); //Labyrinth's map (and data structure containing it).
    //MazeGraph graph = lab.ToMazeGraph(); //graph representation of the map.
    //graph.Print();
    
    //visitOrder or nodeVisitOrder //used for the main.cpp part of the program (used to return path of indexes of visited nodes).
    std::set<int> discovered_nodes; //indicies of discovered (and currently or soon-to-be checked) maze nodes. (in some documentations named as: openset).
    std::set<int> completed_nodes; //indicies of nodes which have been checked throughtfully (in every way we can go from that node). (in some documentations named as: closedset).
    std::set<int> adjacent_nodes; //indicies of adjacent maze nodes (nodes neighbouring to the currently checked node).
    discovered_nodes.insert(0);
    std::map<int, int> g_score; //g(x) score which is distance (amount of edges (in this case without edges' weights)) between
    //nodes from the start up to the point n (where n can be a "start" node as well). (function can 
    //othwerwise be described as: "how many moves in order to get to the node n from the starting node").
    //first value is node index, second value is g_score (g(x)).
    g_score[0] = 0; //g_score (distance) for 0 (starting point) is 0 (which is logical).
    std::map<int, int> h_score; //describe this later (heuristics score (h(x))).
    h_score[0] = heuristic_estimation(0, graph, lab); //check later again
    std::map<int, int> f_score; //f(x) = g(x) + h(x) (f_score = g_score + h_score).
    f_score[0] = g_score[0] + h_score[0];
    //                                      AMOUNT_OF_ROWS        AMOUNT_OF_COLUMNS
    int goal_node = graph.GetIndexFromCoords(lab.GetMazeHeight()-2, lab.GetMazeWidth()-2); //goal's node index
    //std::cout << lab.GetMazeHeight() << ' ' << lab.GetMazeWidth() << '\n';
    //return 1;

    int x = 0; //describe this later: node with the lowest f(x) (heuristics) score (?)
    //can rename it as current_node or something like "currently checked node"...
    std::map<int, int> came_from; //came_from map is information about "last step" of the cheapest path (according to f(x)).
    //theoreeeeeticaaaally, could have used std::stack for that - maybe do that later.
    //i.e: what was the index of the last node before the currently chosen node (also distinguished by index).
    came_from[0] = -1;

    //not forget about goal/objective node.

    int tentative_g_score = 0; //tentative's (currently checked/tried) path's g_score.
    bool is_tentative_better;

    //!currently writing the algorithm's logic

    while(!discovered_nodes.empty()){

        x = lowest_f_score(f_score, discovered_nodes); //find node with the lowest f(x).
        visitOrder.push_back(x);

        if(x == goal_node)
            return reconstruct_path(came_from, goal_node, graph);

        //adjacent_nodes.clear();
        // Fixed!!! (the problem was here)
        //Fixed the full solution path display but ruined the visit order vector data - will change/fix this later.

        for(int node_index : graph.GetAdjacentNodeIndicies(x))//adds neighbouring nodes of current node to unvisted_nodes set.
            adjacent_nodes.insert(node_index);

        discovered_nodes.erase(x);
        completed_nodes.insert(x);

        //std::cout << "current x: " << graph.GetGraphNode(x)->x << ' ' << graph.GetGraphNode(x)->y << " \n";

        for(int adjacent_node : adjacent_nodes){ //don't blend the unvisited nodes with adjacent nodes!!! Because node can be adjacent to other node that has been discovered already

            if(completed_nodes.find(adjacent_node) != completed_nodes.end()) //if "adjacent_node is already (is found) in completed_nodes".
                continue;
            
            tentative_g_score = g_score[x] + 1; //1 is distance between the nodes.
            is_tentative_better = false;

            if(discovered_nodes.find(adjacent_node) == discovered_nodes.end()){//if "adjacent node isn't in discovered nodes yet".
                discovered_nodes.insert(adjacent_node); //insert the node to the discovered nodes.
                h_score[adjacent_node] = heuristic_estimation(adjacent_node, graph, lab); //heuristic estimation of distance from current node to the goal node.
                is_tentative_better = true;
            }
            else if(tentative_g_score < g_score[adjacent_node]){//if "distance of currently considered route (from start to currently inspected adjacent_node) is shorter than the already known one".
                is_tentative_better = true;
            }

            if(is_tentative_better){
                came_from[adjacent_node] = x;
                g_score[adjacent_node] = tentative_g_score;
                f_score[adjacent_node] = g_score[adjacent_node] + h_score[adjacent_node];
            }

            //std::cout << "adjacent_node: " << adjacent_node << " \n";

            //it does make sense now that I think about it, because it checks all possibilities for currently considered node (node x) and *only then* adds it to closedset/completed_nodes
        }
    }

    //was used for testing:
    /*std::vector<int> indicies;

    indicies = graph.GetAdjacentNodeIndicies(0);
    
    for(auto node : indicies){
        std::cout << "node index: " << node << ' ' << graph.GetGraphNode(node)->x << ' ' << graph.GetGraphNode(node)->y << '\n';
    }*/
   return (std::vector<int>)NULL;
   //maybe do something like try-catch instead of this later.
}