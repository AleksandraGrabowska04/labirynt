#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <climits>
#include <algorithm>
#include "../mazemap.h"
#include "../graph.h"
#include "algorithms.h"



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
    
    //order of nodes is reversed because of adding (pushing back) elements onto a/the "stack" (map)
    std::vector<int> ordered_path; //properly ordered path.
    int current_node = goal_node_index; //a currently checked node index.
    ordered_path.push_back(current_node);

    while(came_from[current_node] != -1){

        current_node = came_from[current_node]; //assigns index of node from the previous step of "the cheapest" path into the current_node.
        ordered_path.push_back(current_node); //adds index of the current node to the end of the path vector.

    }

    //properly ordering the full node labyrinth solution path (reconstructing the proper path).
    std::reverse(ordered_path.begin(), ordered_path.end());

    return ordered_path;

}

int heuristic_estimation(int x, MazeGraph& graph, int goal_node){ //heuristic estimation of distance from x node to the goal node.

    int heuristic_distance = //heuristically estimated distance.
    (graph.GetGraphNode(goal_node)->x - graph.GetGraphNode(x)->x)
    + (graph.GetGraphNode(goal_node)->y - graph.GetGraphNode(x)->y);

    return heuristic_distance;
}

std::vector<int> Algorithms::a_star(MazeGraph& graph, int startNode, int endNode, std::vector<int>& visitOrder){
    
    std::set<int> discovered_nodes; //indicies of discovered (and currently or soon-to-be checked) maze nodes. (in some documentations named as: openset).
    std::set<int> completed_nodes; //indicies of nodes which have been checked throughtfully (in every way we can go from that node). (in some documentations named as: closedset).
    std::set<int> adjacent_nodes; //indicies of adjacent maze nodes (nodes neighbouring to the currently checked node).
    discovered_nodes.insert(startNode);

    std::map<int, int> g_score; //g(x) score which is distance (amount of edges (in this case without edges' weights)) between
    //nodes from the start up to the point n (where n can be a "start" node as well). (function can 
    //othwerwise be described as: "how many moves in order to get to the node n from the starting node").
    //first value is node index, second value is g_score (g(x)).
    g_score[startNode] = 0; //g_score (distance) for 0 (starting point) is 0 (which is logical).
    std::map<int, int> h_score; //describe this later (heuristics score (h(x))).
    h_score[startNode] = heuristic_estimation(0, graph, endNode); //check later again
    std::map<int, int> f_score; //f_score = g_score + h_score (by formula: f(x) = g(x) + h(x)).
    f_score[startNode] = g_score[startNode] + h_score[startNode];

    int x = startNode; //currently checked node.

    std::map<int, int> came_from; //came_from map is information about "last step" of the cheapest path (according to f(x)).
    //i.e: what was the index of the last node before the currently chosen node (also distinguished by index).
    came_from[startNode] = -1;

    int tentative_g_score = 0; //tentative's (currently checked/tried) path's g_score.
    bool is_tentative_better;

    while(!discovered_nodes.empty()){

        x = lowest_f_score(f_score, discovered_nodes); //find node with the lowest f(x).
        visitOrder.push_back(x);

        if(x == endNode){
            return reconstruct_path(came_from, endNode, graph);
        }

        adjacent_nodes.clear();

        for(int node_index : graph.GetAdjacentNodeIndicies(x))//adds neighbouring nodes of current node to unvisted_nodes set.
            adjacent_nodes.insert(node_index);

        discovered_nodes.erase(x);
        completed_nodes.insert(x);

        for(int adjacent_node : adjacent_nodes){

            if(completed_nodes.find(adjacent_node) != completed_nodes.end()) //if "adjacent_node is already (is found) in completed_nodes".
                continue;
            
            tentative_g_score = g_score[x] + 1; //1 is distance between the nodes.
            is_tentative_better = false;

            if(discovered_nodes.find(adjacent_node) == discovered_nodes.end()){//if "adjacent node isn't in discovered nodes yet".
                discovered_nodes.insert(adjacent_node); //insert the node to the discovered nodes.
                h_score[adjacent_node] = heuristic_estimation(adjacent_node, graph, endNode); //heuristic estimation of distance from current node to the goal node.
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